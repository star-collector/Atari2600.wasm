#include <cstring>
#include <stdexcept>
#include <stdint.h>
#include <stdio.h>
#include <vector>

#include "CPU.hpp"
#include "RAM.hpp"

CPU::CPU(RAM* memory)
{
	this->memory = memory;

	this->resetVector();
}

int CPU::getFlag(char&& flag)
{
    int offset = 0x00;

    switch(flag) {
        case 'N':
            offset = 0x07;
            break;
        case 'V':
            offset = 0x06;
            break;
        case 'B':
            offset = 0x04;
            break;
        case 'D':
            offset = 0x03;
            break;
        case 'I':
            offset = 0x02;
            break;
        case 'Z':
            offset = 0x01;
            break;
        case 'C':
            offset = 0x00;
            break;
        default:
            throw std::invalid_argument("getFlag: Unknown flag!");
            break;
    }

    return (this->P & (1 << offset)) > 0 ? 1 : 0;
}

void CPU::lock()
{
    this->active = false;
}

void CPU::resetVector()
{
	uint8_t low = this->memory->get(0xFFFC);
	uint8_t high = this->memory->get(0xFFFD);
	this->PC = ((high & 0xFF) << 0x08) | (low & 0xFF);
}

void CPU::pulse()
{
    if (!this->active) {
        return;
    }
    if (!this->cycle) {
        if (DEBUG) {
            printf("OPCODE: 0x%02X; ADRESS: 0x%04X;\n", this->memory->get(this->PC), this->PC);
        }

        switch (this->memory->get(this->PC)) {
            #include "CPU.inc.cpp"
        }

        this->PC++;
    }

    this->cycle--;
}

void CPU::setFlag(char&& flag, int value)
{
    int offset = 0x00;

    switch(flag) {
        case 'N':
            offset = 0x07;
            break;
        case 'V':
            offset = 0x06;
            break;
        case 'B':
            offset = 0x04;
            break;
        case 'D':
            offset = 0x03;
            break;
        case 'I':
            offset = 0x02;
            break;
        case 'Z':
            offset = 0x01;
            break;
        case 'C':
            offset = 0x00;
            break;
        default:
            throw std::invalid_argument("setFlag: Unknown flag!");
            break;
    }

    this->P = (value ? this->P | (1 << offset) : this->P & ~(1 << offset));
}

void CPU::setCycle(int cycle)
{
    this->cycle = cycle;
}

void CPU::setCycle(int cycle, uint16_t address, uint16_t addressWithOffset)
{
    this->cycle = cycle + (address >> 0x08 % 0xFF != addressWithOffset >> 0x08 % 0xFF);
}

void CPU::unlock()
{
    this->active = true;
}

uint16_t CPU::ADDRAbsolute()
{
    uint8_t low = this->memory->get(++this->PC);
    uint8_t high = this->memory->get(++this->PC);

    return ((high & 0xFF) << 0x08) | (low & 0xFF);
}

uint16_t CPU::ADDRAbsoluteX()
{
    return (ADDRAbsolute() + this->X) & 0xFFFF;
}

uint16_t CPU::ADDRImmediate()
{
    return ++this->PC;
}

uint16_t CPU::ADDRZeropage()
{
    return this->memory->get(++this->PC);
}

uint16_t CPU::ADDRZeropageX()
{
	return (ADDRZeropage() + this->X) & 0xFF;
}

void CPU::BIT(uint16_t address)
{
    uint8_t value = this->memory->get(address);

    this->setFlag('Z', (this->A & value) == 0);
    this->setFlag('N', (value & 0x80) == 0x80);
    this->setFlag('V', (value & 0x40) == 0x40);
}

void CPU::CJMP(char&& flag, bool&& value)
{
    if(this->getFlag(std::move(flag)) == value) {
        this->PC++;
        setCycle(2);
		return;
    };

    int8_t num = this->memory->get(ADDRImmediate());

    this->PC += num;

    setCycle(3, this->PC - num, this->PC);
}

void CPU::CMP(uint16_t address)
{
    uint8_t value = this->memory->get(address);

    setFlag('Z', this->A == value);

    setFlag('N', (int8_t)value < 0);

    setFlag('C', this->A - value >= 0);
}

void CPU::DEX()
{
	this->X = (this->X - 1) & 0xFF;

	this->setFlag('Z', this->X == 0);
	this->setFlag('N', this->X < 0);
}

void CPU::DEY()
{
	this->Y = (this->Y - 1) & 0xFF;

	this->setFlag('Z', this->X == 0);
	this->setFlag('N', this->X < 0);
}

void CPU::INC(uint16_t address)
{
    uint8_t result = this->memory->get(address) + 1;

    this->memory->set(address, result);

    this->setFlag('Z', result == 0);
    this->setFlag('N', result < 0);
}

void CPU::INX()
{
	this->X = (this->X + 1) & 0xFF;

	this->setFlag('Z', this->X == 0);
	this->setFlag('N', this->X < 0);
}

void CPU::JMP(uint16_t address)
{
    this->PC = address - 1;
}

void CPU::JSR(uint16_t address)
{
    this->PUSH(this->PC >> 8);
    this->PUSH(this->PC);
    this->PC = address - 1;
}

void CPU::LDA(uint16_t address)
{
    int8_t value = this->memory->get(address);

    this->A = value;

    this->setFlag('Z', value == 0);
    this->setFlag('N', value < 0);
}

void CPU::LDX(uint16_t address)
{
    int8_t value = this->memory->get(address);

    this->X = value;

    this->setFlag('Z', value == 0);
    this->setFlag('N', value < 0);
}

void CPU::LDY(uint16_t address)
{
    int8_t value = this->memory->get(address);

    this->Y = value;

    this->setFlag('Z', value == 0);
    this->setFlag('N', value < 0);
}

uint8_t CPU::POP()
{
	this->S = (this->S + 1) & 0xFF;

	return this->memory->get(this->S);
}

void CPU::PUSH(uint8_t value)
{
    this->memory->set(this->S, value);

    this->S = (this->S - 1) & 0xFF;
}

void CPU::ROL(uint16_t address)
{
    uint8_t value = this->memory->get(address);
    int carry = ((value & 0x80) > 0 ? 1 : 0);

    value = value << 1 | carry;

    this->memory->set(address, value);

    this->setFlag('Z', value == 0);
    this->setFlag('Z', value < 0);
    this->setFlag('C', carry);

}
void CPU::RTS()
{
	this->PC = this->POP();
	this->PC += this->POP() << 8;
}

void CPU::STA(uint16_t address)
{
    this->memory->set(address, this->A);
}

void CPU::STY(uint16_t address)
{
    this->memory->set(address, this->Y);
}

void CPU::STX(uint16_t address)
{
	this->memory->set(address, this->X);
}

void CPU::TXS()
{
    this->S = this->X;
}
