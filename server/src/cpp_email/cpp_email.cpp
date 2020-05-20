
#include "cpp_email.h"

void Email::prepare() {
	std::ofstream myfile;
	myfile.open("email.txt");
	myfile << address << "\n";
	myfile << subject << "\n";
	myfile << body << "\n";

}

void Email::send() {
	char filename[] = "emailsender.py";
	FILE* fp;

	Py_Initialize();

	fp = _Py_fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);

	Py_Finalize();
}
