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
	writeSingleByte((MCP23017_ADDRESS | i2caddr), 0xFF);


//	xfer_struct.slaveAddress = (MCP23017_ADDRESS | i2caddr);
//	xfer_struct.direction = kI2C_Write;
//	xfer_struct.subaddress = MCP23017_IODIRA;
//	xfer_struct.subaddressSize = 1;
//	xfer_struct.data = &data;
//	xfer_struct.dataSize = 8U;
//	xfer_struct.flags = kI2C_TransferNoStopFlag;
//
//	status_t status = I2C_MasterTransferBlocking(USER_I2C_PERIPHERAL, &xfer_struct);
}

void PortExpander::begin(void) {
	begin(0);
}

void PortExpander::pinMode(uint8_t p, uint8_t d) {
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
}

status_t PortExpander::writeSingleByte(uint8_t address, uint8_t data) {
	status_t status = kStatus_Success;
	status = I2C_MasterStart(peripheral_base, address,
			kI2C_Write);
	if(!status) {
	status = I2C_MasterWriteBlocking(peripheral_base, &data, 1,
			kI2C_TransferNoStopFlag);
	}
	if(!status) {
		status = I2C_MasterStop(peripheral_base);
	}

	return status;
}
