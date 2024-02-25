#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>
#include <string.h>
#include <fstream>

struct chip8 {
    uint8_t memory[4096];
    uint16_t pc;
    uint8_t v[16];  
    uint16_t i;
    uint8_t st;
    uint8_t dt;
    uint16_t stack[16];
    uint8_t sp;
} ;

void loadRom(chip8* chip8) {
    std::ifstream rom("C:/Users/Sergio/source/repos/chip8/chip8/roms/tetris.ch8", std::ios::binary);

    if (!rom.good()) {
        std::cout << "Cannot open ROM file!" << std::endl;
    }
    rom.seekg(0, std::ios::end);
    size_t romSize = rom.tellg();
    rom.seekg(0, std::ios::beg);
    rom.read((char*)chip8->memory + 512, romSize);
    rom.close();

    //std::cout << (int)chip8->memory[0x200] << std::endl;
    //std::cout << (int)chip8->memory[512 + 492] << std::endl;
}


int main()
{
    chip8 chip8;
    loadRom(&chip8);

    return 0;
}





