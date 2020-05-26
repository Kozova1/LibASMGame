#ifndef CPU_HPP
#define CPU_HPP

#define MEM_SIZE 4096
#define STACK_SIZE 16

#include <string>
#include <cstdint>
#include <cstring>

class Cpu {
	public:
	uint8_t memory[MEM_SIZE];
	uint8_t r[16];
	uint16_t i;
	uint16_t pc;
	uint16_t sp;
	uint16_t stack[STACK_SIZE];
	void init();
	void load_program(uint8_t*);
	void run();
	virtual void putchar(char);
	virtual uint8_t getchar();
	private:
	uint16_t read_word(size_t);
	void process_instruction(uint16_t);
};

#endif
