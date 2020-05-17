#pragma once

#include <iostream>

#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")

#include <string>
#include <fstream>

class Email {
	std::string address;
	std::string subject;
	std::string body;

public:
	Email(std::string addr, std::string sub, std::string bd) :address(addr), subject(sub), body(bd) {}
	void prepare();
	void send();

};