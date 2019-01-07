/*
 * UserInterface.cpp
 *
 *  Created on: Jan 6, 2019
 *      Author: Jack
 */

#include <UserInterface.h>

User_Interface::User_Interface() {
	// TODO Auto-generated constructor stub

}

User_Interface::~User_Interface() {
	// TODO Auto-generated destructor stub
}

void User_Interface::init(uint8_t fourbitmode, uint8_t rs, uint8_t rw,
		uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
}

void User_Interface::begin(uint8_t cols, uint8_t rows, uint8_t charsize) {
}

void User_Interface::clear() {
}

void User_Interface::home() {
}

void User_Interface::noDisplay() {
}

void User_Interface::display() {
}

void User_Interface::noBlink() {
}

void User_Interface::blink() {
}

void User_Interface::noCursor() {
}

void User_Interface::cursor() {
}

void User_Interface::scrollDisplayLeft() {
}

void User_Interface::scrollDisplayRight() {
}

void User_Interface::leftToRight() {
}

void User_Interface::rightToLeft() {
}

void User_Interface::autoscroll() {
}

void User_Interface::noAutoscroll() {
}

void User_Interface::setBacklight(uint8_t status) {
}

void User_Interface::createChar(uint8_t unsignedChar, uint8_t[]) {
}

void User_Interface::setCursor(uint8_t unsignedChar, uint8_t unsignedChar1) {
}

size_t User_Interface::write(uint8_t unsignedChar) {
}

void User_Interface::command(uint8_t unsignedChar) {
}

uint8_t User_Interface::readButtons() {
}

void User_Interface::send(uint8_t unsignedChar, uint8_t unsignedChar1) {
}

void User_Interface::write4bits(uint8_t unsignedChar) {
}

void User_Interface::write8bits(uint8_t unsignedChar) {
}

void User_Interface::pulseEnable() {
}

void User_Interface::_digitalWrite(uint8_t unsignedChar,
		uint8_t unsignedChar1) {
}

void User_Interface::_pinMode(uint8_t unsignedChar, uint8_t unsignedChar1) {
}
