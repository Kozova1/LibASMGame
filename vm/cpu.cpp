#include "./cpu.hpp"

void Cpu::init() {
	this->i = 0;
	this->sp = 0;
	this->pc = 511 - 2;
}

void Cpu::load_program(uint8_t *program) {
	memcpy(this->memory + 511, program, 4096 - 512 - 256);
}

void Cpu::run() {
	while (this->memory[this->pc] < 0xff && this->memory[this->pc + 1] < 0xff) {
		this->pc += 2;
		this->process_instruction(this->read_word(this->pc));
	}
}

uint16_t Cpu::read_word(size_t pos) {
	return (memory[pos] << 8) | memory[pos + 1];
}

void Cpu::process_instruction(uint16_t ocode) {
	uint8_t x = (ocode & 0x0F00) >> 8;
	uint8_t y = (ocode & 0x00F0) >> 4;
	uint8_t n = ocode & 0x000F;
	uint8_t nn = ocode & 0x00FF;
	uint16_t nnn = ocode & 0x0FFF;
	uint8_t hn = (ocode & 0xF000) >> 12;
	uint8_t ln = n;
	switch ((int) hn) {
	case 0:
		this->r[x]++;
		break;
	case 1:
		if (nnn == 0x000) {
			this->pc = this->stack[this->sp];
			this->pc--;
		} else if (ln == 0x0) {
			this->r[x] -= this->r[y];
		} else if (ln == 0x1) {
			this->r[x] = this->r[y] - this->r[x];
		} else if (ln == 0x2) {
			this->r[x] += this->r[y];
		}
		break;
	case 2:
		this->sp++;
		this->stack[this->sp] = this->pc;
		this->pc = nnn;
		break;
	case 3:
		this->pc = nnn;
		break;
	case 4:
		this->r[x] = this->r[y];
		break;
	case 5:
		this->r[x] = nn;
		break;
	case 6:
		this->r[x] = this->memory[this->i];
		break;
	case 7:
		this->i = nnn;
		break;
	case 8:
		if (ln == 0x0) {
			this->i = this->r[x];
		} else if (ln == 0x1) {
			this->r[x] = this->i;
		}
		break;
	case 9:
		this->pc = (this->r[0xF] == 0 ? nnn : this->pc);
		break;
	case 0xA:
		this->sp++;
		this->stack[this->sp] = this->r[x];
		break;
	case 0xB:
		this->sp++;
		this->stack[this->sp] = nnn;
		break;
	case 0xC:
		if (ln == 0x1) {
			this->sp--;
		}
		break;
	case 0xD:
		if (ln == 0x0) {
			this->putchar((char) this->r[x]);
		} else if (ln == 0x1) {
			this->r[x] = this->getchar();
		} break;
	}
}

void Cpu::putchar(char c) {}
uint8_t Cpu::getchar() { return (uint8_t)'c'; /* Do not use this, override plz */}
