/*
 * PortExpander.cpp
 *
 *  Created on: Jan 11, 2019
 *      Author: Jack
 */

#include <PortExpander.h>

void PortExpander::begin(uint8_t addr) {
	if (addr > 7) {
		addr = 7;
	}

	i2caddr = addr;
	uint8_t data = 0xff;

	// set defaults
	writeSingleByte(MCP23017_IODIRA, 0xFF);
	writeSingleByte(MCP23017_IODIRB, 0xFF);

	uint8_t test = readSingleByte(MCP23017_IODIRA);
}

void PortExpander::begin(void) {
	begin(0);
}

void PortExpander::pinMode(uint8_t p, uint8_t d) {
	uint8_t iodir;
	uint8_t iodiraddr;

	// only 16 bits!
	if (p > 15)
		return;

	if (p < 8)
		iodiraddr = MCP23017_IODIRA;
	else {
		iodiraddr = MCP23017_IODIRB;
		p -= 8;
	}

	// read the current IODIR
	iodir = readSingleByte(iodiraddr);

	// set the pin and direction
	if (d == INPUT) {
		iodir |= 1 << p;
	} else {
		iodir &= ~(1 << p);
	}

	// write the new IODIR
	writeSingleByte(iodiraddr, iodir);
}

void PortExpander::digitalWrite(uint8_t p, uint8_t d) {
}

void PortExpander::pullUp(uint8_t p, uint8_t d) {
}

uint8_t PortExpander::digitalRead(uint8_t p) {
}

void PortExpander::writeGPIOAB(uint16_t unsignedShortInt) {
}

uint16_t PortExpander::readGPIOAB() {
	uint16_t ba = 0;
	uint8_t a;

	// read the current GPIO output latches
	a = readSingleByte(MCP23017_GPIOA);
	ba = readSingleByte(MCP23017_GPIOB);
	ba <<= 8;
	ba |= a;

	return ba;
}

status_t PortExpander::writeSingleByte(uint8_t address, uint8_t data) {
	status_t status = kStatus_Success;
	// send a start signal with the address of the port expander
	status = I2C_MasterStart(peripheral_base, (MCP23017_ADDRESS | i2caddr),
			kI2C_Write);

	// send the address of the register being written
	status = I2C_MasterWriteBlocking(peripheral_base, &address, 1,
			kI2C_TransferNoStopFlag);

	// send the data byte
	status = I2C_MasterWriteBlocking(peripheral_base, &data, 1,
			kI2C_TransferNoStopFlag);

	// end the connection
	status = I2C_MasterStop(peripheral_base);

	return status;
}

status_t PortExpander::writeSequentialBytes(uint8_t start_address,
		uint8_t* data, size_t data_size) {
	status_t status = kStatus_Success;
	// send a start signal with the address of the port expander
	status = I2C_MasterStart(peripheral_base, (MCP23017_ADDRESS | i2caddr),
			kI2C_Write);

	// send the address of the first register being written
	status = I2C_MasterWriteBlocking(peripheral_base, &start_address, 1,
			kI2C_TransferNoStopFlag);

	// send the data byte sequence
	status = I2C_MasterWriteBlocking(peripheral_base, data, data_size,
			kI2C_TransferNoStopFlag);

	// end the connection
	status = I2C_MasterStop(peripheral_base);

	return status;
}

uint8_t PortExpander::readSingleByte(uint8_t address) {
	status_t status = kStatus_Success;
	uint8_t data;
	// send a start signal with the address of the port expander
	status = I2C_MasterStart(peripheral_base, (MCP23017_ADDRESS | i2caddr),
			kI2C_Write);

	// send the address to read from
	status = I2C_MasterWriteBlocking(peripheral_base, &address, 1,
			kI2C_TransferNoStopFlag);

	// read from the given register address into the data buffer
	status = I2C_MasterReadBlocking(peripheral_base, &data, 1,
			kI2C_TransferNoStopFlag);

	// end the connection
	status = I2C_MasterStop(peripheral_base);

	return data;
}
