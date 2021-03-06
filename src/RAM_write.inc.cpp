// VSYNC
case 0x00: {
    this->tia->setVsync(value & 0x02);
	break;
}
// WSYNC
case 0x02: {
    this->cpu->lock();
    break;
}
// TIM1T
case 0x294: {
	this->pia->setCycle(1);
	this->map[0x285] = this->map[0x285] & 0x7F;
	break;
}
// TIM8T
case 0x295: {
	this->pia->setCycle(8);
	this->map[0x285] = this->map[0x285] & 0x7F;
	break;
}
// TIM64T
case 0x296: {
	this->pia->setCycle(64);
	this->map[0x285] = this->map[0x285] & 0x7F;
	break;
}
// TIM1024T
case 0x297: {
	this->pia->setCycle(1024);
	this->map[0x285] = this->map[0x285] & 0x7F;
	break;
}

