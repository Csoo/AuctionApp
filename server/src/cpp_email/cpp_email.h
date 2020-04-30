#include <iostream>
#include <python.h>
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