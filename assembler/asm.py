#!/usr/bin/env python3
from typing import List, Dict
import sys

def get_lines(file_name: str) -> List[str]:
    lines: List[str] = []
    with open(file_name, 'r') as f:
        lines = f.readlines()
    return lines

def preprocess(lines: List[str]) -> List[str]:
    new_lines: List[str] = []
    positions: Dict[str, int] = []
    for line in lines:
        new_lines.append(line.strip())
    for i, l in enumerate(new_lines):
        if l[0] == '#':
            positions[l[1:]] = i
        if l[0] == '':
            new_lines.pop(i)
        if 'call' in l:
            l = 'call ' + positions[l[6:]]
        elif 'jmp' in l:
            l = 'jmp ' + positions[l[5:]]
        elif 'biz' in l:
            l = 'biz ' + positions[l[5:]]
    return new_lines

def assemble(lines: List[str]) -> str:
    end_result: str = ''
    for i, line in enumerate(lines):
        inst, *args = line.split()
        args = ''.join(args).split(',')
        if inst == 'ret':
            end_result += '1000'
        elif inst == 'sub':
            x = args[0][1]
            y = args[1][1]
            end_result += '1' + x + y + '0'
        elif inst == 'subr':
            x = args[0][1]
            y = args[1][1]
            end_result += '1' + x + y + '1'
        elif inst == 'add':
            x = args[0][1]
            y = args[1][1]
            end_result += '1' + x + y + '2'
        elif inst == 'call':
            nnn = args[0]
            end_result += '2' + nnn
        elif inst == 'jmp':
            nnn = args[0]
            end_result += '3' + nnn
        elif inst == 'ld':
            if args[0][0] == 'r':
                if args[1][0] == 'r':
                    x = args[0][1]
                    y = args[1][1]
                    end_result += '4' + x + y + '0'
                elif args[1] == '%i':
                    x = args[0][1]
                    end_result += '6' + x + '00'
                elif args[1] == 'i':
                    x = args[0][1]
                    end_result += '8' + x + '01'
                else:
                    x = args[0][1]
                    end_result += '5' + x + args[1]
            elif args[0][0] == 'i':
                if args[1][0] == 'r':
                    x = args[1][1]
                    end_result += '8' + x + '00'
                else:
                    end_result += '7' + args[1]
        elif inst == 'biz':
            nnn = args[0]
            end_result += '9' + nnn
        elif inst == 'push':
            if args[0][0] == 'r':
                x = args[0][1]
                end_result += 'A' + x + '00'
            else:
                nnn = args[0]
                end_result += 'B' + nnn
        elif inst == 'pop':
            end_result += 'C001'
        elif inst == 'putc':
            x = args[0][1]
            end_result += 'D' + x + '00'
        elif inst == 'getc':
            x = args[0][1]
            end_result += 'D' + x + '01'
        else:
            print(f'ERROR: unknown instruction on line {i}')
            sys.exit()
    return end_result

        

def write_out(data: str, file_name: str):
    with open(file_name, "wb+") as f:
        print(data)
        f.write(bytes.fromhex(data))

if __name__ == '__main__':
    fname = sys.argv[1]
    content = get_lines(fname)
    write_out(assemble(preprocess(content)), fname)

