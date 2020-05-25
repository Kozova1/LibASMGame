#!/usr/bin/env python3
from typing import List

def split_tokens(line: str) -> List[str]:
    tokens: List[str] = []
    for x in line.split():
        tokens.append(x)
    return tokens

def get_lines(file_name: str) -> List[str]:
    lines: List[str] = []
    with open(file_name, 'r') as f:
        lines = f.readlines()
    return lines

def assemble():
