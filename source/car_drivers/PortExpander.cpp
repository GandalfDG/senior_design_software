/***************************************************
  This is a library for the MCP23017 i2c port expander
  These displays use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <car_drivers/PortExpander.h>

#define DEBUG_I2C

void PortExpander::begin(uint8_t addr) {
	if (addr > 7) {
		addr = 7;
	}

	i2caddr = addr;

	// set defaults
	writeSingleByte(MCP23017_IODIRA, 0xFF);
	writeSingleByte(MCP23017_IODIRB, 0xFF);
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
	uint8_t gpio = 0;
	uint8_t gpioaddr, olataddr;

	// only 16 bits!
	if (p > 15)
		return;

	if (p < 8) {
		olataddr = MCP23017_OLATA;
		gpioaddr = MCP23017_GPIOA;
	} else {
		olataddr = MCP23017_OLATB;
		gpioaddr = MCP23017_GPIOB;
		p -= 8;
	}

	// read the current FPIO output latches
	readSingleByte(olataddr);

	// set the pin and direction
	if (d == HIGH) {
		gpio |= 1 << p;
	} else {
		gpio &= ~(1 << p);
	}

	// write the new GPIO
	writeSingleByte(gpioaddr, gpio);
}

void PortExpander::pullUp(uint8_t p, uint8_t d) {
	uint8_t gppu;
	uint8_t gppuaddr;

	// only 16 bits!
	if (p > 15)
		return;

	if (p < 8)
		gppuaddr = MCP23017_GPPUA;
	else {
		gppuaddr = MCP23017_GPPUB;
		p -= 8;
	}

	// read the current pullup resistor set
	gppu = readSingleByte(gppuaddr);

	// set the pin and direction
	if (d == HIGH) {
		gppu |= 1 << p;
	} else {
		gppu &= ~(1 << p);
	}

	// write the new GPIO
	writeSingleByte(gppuaddr, gppu);
}

uint8_t PortExpander::digitalRead(uint8_t p) {
	uint8_t gpioaddr;

	// only 16 bits!
	if (p > 15)
		return 0;

	if (p < 8)
		gpioaddr = MCP23017_GPIOA;
	else {
		gpioaddr = MCP23017_GPIOB;
		p -= 8;
	}

	// read the current GPIO
	return (readSingleByte(gpioaddr) >> p) & 0x01;
}

void PortExpander::writeGPIOAB(uint16_t ba) {
	writeSingleByte(MCP23017_GPIOA, ba & 0xFF);
	writeSingleByte(MCP23017_GPIOB, ba >> 8);
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
	i2c_master_transfer_t xfer;

	xfer.flags = kI2C_TransferDefaultFlag;
	xfer.slaveAddress = (MCP23017_ADDRESS | i2caddr);
	xfer.direction = kI2C_Write;
	xfer.subaddress = address;
	xfer.subaddressSize = 1;
	xfer.data = &data;
	xfer.dataSize = 1;

	I2C_MasterTransferBlocking(peripheral_base, &xfer);
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
	uint8_t data;
	i2c_master_transfer_t xfer;

	xfer.flags = kI2C_TransferDefaultFlag;
	xfer.slaveAddress = (MCP23017_ADDRESS | i2caddr);
	xfer.direction = kI2C_Read;
	xfer.subaddress = address;
	xfer.subaddressSize = 1;
	xfer.data = &data;
	xfer.dataSize = 1;

	I2C_MasterTransferBlocking(peripheral_base, &xfer);

	return data;
}
