#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>
#include <string.h>
#include <fstream>

#define MEMSIZE 4096
#define STACKSIZE 16

struct chip8 {
    uint8_t memory[4096];
    uint16_t stack[16];
    uint8_t v[16];  
    uint16_t pc;
    uint16_t i;
    uint8_t st;
    uint8_t dt;
    uint8_t sp;
} ;

static void initMachine(chip8* machine) {
    machine->pc = 0x200;
    machine->i = machine->st = machine->dt = machine->sp = 0;
    memset(machine->memory, 0, MEMSIZE);
    memset(machine->stack, 0, 32);
    memset(machine->v, 0, 16);
}

static void loadRom(chip8* machine) {
    std::ifstream rom("C:/Users/Sergio/source/repos/chip8/chip8/roms/tetris.ch8", std::ios::binary);

    if (!rom.good()) {
        std::cout << "Cannot open ROM file!" << std::endl;
    }

    rom.seekg(0, std::ios::end);
    size_t romSize = rom.tellg();
    rom.seekg(0, std::ios::beg);
    rom.read( (char*) machine->memory + 512, romSize );
    rom.close();
}

int main()
{
    chip8 chip;
    initMachine(&chip);
    loadRom(&chip);

    uint16_t opcode;
    while (true) {

        // FETCH
        opcode = (chip.memory[chip.pc] << 8) | (chip.memory[chip.pc + 1]);
        chip.pc = (chip.pc += 2) & 0xFFF;

        if (chip.pc == MEMSIZE)
            break;

        // DECODE AND EXECUTE
        uint16_t nnn = opcode & 0x0FFF;  // least significant 12 bits
        uint16_t n = opcode & 0x000F;  // least significant nibble
        uint16_t x = ( opcode & 0x0F00 ) >> 8;  // least significant nibble from upper byte
        uint16_t y = ( opcode & 0x00F0 ) >> 4;  // most significant nibble from lower byte
        uint16_t kk = opcode & 0x00FF;  // least significant byte
        uint16_t msn = opcode >> 12;  // most significant nibble
        
        switch (msn) {
            case 0:
                if (kk == 0xE0)
                    printf("CLS");
                else if (kk == 0xEE)
                    printf("RET");
                else 
                    printf("SYS %x", nnn);
                break;
            case 1:
                printf("JP %x\n", nnn);
                chip.pc = nnn;
                break;
            case 2:
                printf("CALL %x\n", nnn);
                break;
            case 3:
                printf("SE V%x, %x\n", x, kk);
                if (chip.v[x] == kk)
                    chip.pc = (chip.pc + 2) & 0xFFF;
                break;
            case 4:
                printf("SNE V%x, %x\n", x, kk);
                if (chip.v[x] != kk)
                    chip.pc = (chip.pc + 2) & 0xFFF;
                break;
            case 5:
                printf("SE V%x, V%x\n", x, y);
                if (chip.v[x] == chip.v[y])
                    chip.pc = (chip.pc + 2) & 0xFFF;
                break;
            case 6:
                printf("LD V%x, %x\n", x, kk);
                chip.v[x] = kk;
                break;
            case 7:
                printf("ADD V%x, %x\n", x, kk);
                chip.v[x] = (chip.v[x] + kk) & 0xFF;
                break;
            case 8:
                switch (n) {
                    case 0:
                        printf("LD V%x, V%x\n", x, y);
                        chip.v[x] = chip.v[y];
                        break;
                    case 1:
                        printf("OR V%x, V%x\n", x, y);
                        chip.v[x] |= chip.v[y];
                        break;
                    case 2:
                        printf("AND V%x, V%x\n", x, y);
                        chip.v[x] &= chip.v[y];
                        break;
                    case 3:
                        printf("XOR V%x, V%x\n", x, y);
                        chip.v[x] ^= chip.v[y];
                        break;
                    case 4:
                        printf("ADD V%x, V%x\n", x, y);
                        chip.v[0xF] = ( chip.v[x] > chip.v[x] + chip.v[y] );
                        chip.v[x] += chip.v[y];                       
                        break;
                    case 5:
                        printf("SUB V%x, V%x\n", x, y);
                        chip.v[0xF] = (chip.v[x] > chip.v[y]);
                        chip.v[x] -= chip.v[y];
                        break;
                    case 6:
                        printf("SHR V%x {, V%x}\n", x, y);
                        chip.v[0xF] = (chip.v[x] & 1);
                        chip.v[x] >>= 1;
                        break;
                    case 7:
                        printf("SUBN V%x, V%x\n", x, y);
                        chip.v[0xF] = ( chip.v[y] > chip.v[x] );
                        chip.v[x] = ( chip.v[y] - chip.v[x] );
                        break;
                    case 0xE:
                        printf("SHL V%x {, V%x}\n", x, y);
                        chip.v[0xF] = ( chip.v[x] & 0x80 != 0 );
                        chip.v[x] <<= 1;
                        break;
                }
                break;
            case 9:
                printf("SNE V%x, V%x\n", x, y);
                if (chip.v[x] != chip.v[y])
                    chip.pc = (chip.pc + 2) & 0xFFF;
                break;
            case 0xA:
                printf("LD I, %x\n", nnn);
                chip.i = nnn;
                break;
            case 0xB:
                printf("JP V0, %x\n", nnn);
                chip.pc = chip.v[0] + nnn;
                break;
            case 0xc:
                printf("RND V%x, %x\n", x, kk);
                break;
            case 0xd:
                printf("DRW V%x, V%x, %x\n", x, y, n);
                break;
            case 0xe:
                switch (kk) {
                    case 0x9e:
                        printf("SKP V%x\n", x);
                        break;
                    case 0xa1:
                        printf("SKNP V%x\n", x);
                        break;
                }
                break;
            case 0xf:
                switch (kk) {
                    case 0x07:
                        printf("LD V%x, %x\n", x, chip.dt);
                        chip.v[x] = chip.dt;
                        break;
                    case 0x0A:
                        printf("LD V%x, K\n", x);
                        break;
                    case 0x15:
                        printf("LD %x, V%x\n", chip.dt, x);
                        chip.dt = chip.v[x];
                        break;
                    case 0x18:
                        printf("LD ST, V%x\n", x);
                        chip.st = chip.v[x];
                        break;
                    case 0x1E:
                        printf("ADD I %x, V%x\n", chip.i, x);
                        chip.i += chip.v[x];
                        break;
                    case 0x29:
                        printf("LD F, V%x\n", x);
                        break;
                    case 0x33:
                        printf("LD B, V%x\n", x);
                        break;
                    case 0x55:
                        printf("LD [I], V%x\n", x);
                        break;
                    case 0x65:
                        printf("LD V%x, [I]\n", x);
                        break;
                }
                break;
            default:
                printf("OPCODE NOT IMPLEMENTED!\n");
                break;
        }
    }

    return 0;
}





