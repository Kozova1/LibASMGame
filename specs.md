| OPCODE | ASSEMBLY CODE | ACTION                          |
| ------ | ------------- | ------------------------------- |
| 0X00   | inc rx        | r[x]++;                         |
| 1000   | ret           | pc = stack[sp], sp--;           |
| 1XY0   | sub rx, ry    | r[x] = r[x] - r[y];             |
| 1XY1   | subr rx, ry   | r[x] = r[y] - r[x];             |
| 1XY2   | add rx, ry    | r[x] = r[x] + r[y];             |
| 2NNN   | call nnn      | sp++, stack[sp] = pc, pc = nnn; |
| 3NNN   | jmp nnn       | pc = nnn;                       |
| 4XY0   | ld rx, ry     | r[x] = r[y];                    |
| 5XNN   | ld rx, nn     | r[x] = nn;                      |
| 6X00   | ld rx, %i     | r[x] = mem[i];                  |
| 7NNN   | ld i, nnn     | i = nnn;                        |
| 8X00   | ld i, rx      | i = r[x];                       |
| 8X01   | ld rx, i      | r[x] = i;                       |
| 9NNN   | biz nnn       | pc = r[0xF] == 0 ? nnn : pc;    |
| AX00   | push rx       | sp++, stack[sp] = r[x];         |
| BNNN   | push nnn      | sp++, stack[sp] = nnn;          |
| C001   | pop           | sp--;                           |
| DX00   | putc rx       | putchar(r[x]);                  |
| DX01   | getc rx       | r[x] = getchar();               |

# All other instructions are yours to implement
