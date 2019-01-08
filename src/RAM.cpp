#include <stdint.h>
#include <stdio.h>
#include <vector>

#include "PIA.h"
#include "RAM.h"

RAM::RAM(std::vector<uint8_t> rom, PIA*& pia)
{
	std::vector<uint8_t> sliced(0xF000, 0x00);

	sliced.insert(
		sliced.end(),
		std::make_move_iterator(rom.begin()),
		std::make_move_iterator(rom.end())
	);

	this->map = sliced;
	this->pia = pia;
}

uint8_t RAM::get(uint16_t address)
{
	switch (address) {
		#include "RAM_read.inc.cpp"
	}
    return this->map[address];
}

void RAM::set(uint16_t address, uint8_t value)
{
	switch (address) {
		#include "RAM_write.inc.cpp"
	}
    this->map[address] = value;
}
