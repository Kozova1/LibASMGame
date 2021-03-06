#include "./cpu.hpp"
#include <iostream>
#include <stdio.h>
#include <fstream>

class MyCpu : public Cpu {
	public:
	MyCpu();
	virtual void putchar(char) override;
	virtual uint8_t getchar() override;
};

void MyCpu::putchar(char c) {
	std::cout << c;
}

uint8_t MyCpu::getchar() {
	char c;
	std::cin >> c;
	return (uint8_t) c;
}

MyCpu::MyCpu() : Cpu() {
	this->init();
}

int main() {
	MyCpu mcp = *(new MyCpu());
	std::ifstream infile("./testasm", std::ifstream::in | std::ifstream::binary);
	uint8_t buf[MEM_SIZE - 512 - 256];
	infile.seekg(0, std::ios::end);
	size_t length = infile.tellg();
	infile.seekg(0, std::ios::beg);
	if (length > sizeof(buf)) length = sizeof(buf);
	infile.read((char *) buf, length);

	mcp.init();
	mcp.load_program(buf);
	mcp.run();
	std::cout << '\n';

	return 0;
}
