# intel8080emu

Simulates an Intel 8080 processor and provides an interactive debugging shell to inspect the cpu state and load and run programs.
Currently only a limited set of instructions and minimal debugging functionality is supported.

### Links
- http://dunfield.classiccmp.org/r/8080.txt
- https://pastraiser.com/cpu/i8080/i8080_opcodes.html
- http://www.emulator101.com/reference/8080-by-opcode.html
- https://altairclone.com/downloads/manuals/8080%20Programmers%20Manual.pdf

### TODO's:
- Implement reset of opcodes
- Display video memory onto screen
- Improve debugging shell
- Refactor shell commands into pattern
- Add more shell commands to modify cpu state (registers, memory, flags, rom loading)
- Debugging breakpoints (Use opcode 0x08 as break and fetch original instruction from cache)