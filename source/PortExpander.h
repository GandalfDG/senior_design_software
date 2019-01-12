/*
 * PortExpander.h
 *
 *  Created on: Jan 11, 2019
 *      Author: Jack
 */

#ifndef PORTEXPANDER_H_
#define PORTEXPANDER_H_

#include "MK64F12.h"
#include "peripherals.h"

class PortExpander {
public:
	void begin(uint8_t addr);
	void begin(void);

	void pinMode(uint8_t p, uint8_t d);
	void digitalWrite(uint8_t p, uint8_t d);
	void pullUp(uint8_t p, uint8_t d);
	uint8_t digitalRead(uint8_t p);

	void writeGPIOAB(uint16_t);
	uint16_t readGPIOAB();

private:
	I2C_Type* peripheral_base = USER_I2C_PERIPHERAL;
	uint8_t i2caddr;
	i2c_master_transfer_t xfer_struct;

	status_t writeSingleByte(uint8_t address, uint8_t data);
	status_t writeSequentialBytes(uint8_t start_address,
			uint8_t* data, size_t data_size);

	uint8_t readSingleByte(uint8_t address);
};

#define MCP23017_ADDRESS 0x20

// registers
#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14


#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15

#define INPUT 1
#define HIGH 1

#endif /* PORTEXPANDER_H_ */
