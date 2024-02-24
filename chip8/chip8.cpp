#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>


struct {
    uint8_t memory[4096];
    uint16_t pc;
    uint8_t v[16];  
    uint16_t i;
    uint8_t st;
    uint8_t dt;
    uint16_t stack[16];
    uint8_t sp;
} chip8;

void printMemory() {
    int size = sizeof(chip8.memory) / sizeof(uint8_t);
    for (int i = 1; i <= size; i++) {
        std::cout << i << ": " << chip8.memory[i] << std::endl;
    }
}

int main()
{
    al_init();

    // FONT DEFINITION
    chip8.memory[0x50] = 0xF0, chip8.memory[0x51] = 0x90, chip8.memory[0x52] = 0x90, chip8.memory[0x53] = 0x90, chip8.memory[0x54] = 0xF0; // 0
    chip8.memory[0x55] = 0x20, chip8.memory[0x56] = 0x60, chip8.memory[0x57] = 0x20, chip8.memory[0x58] = 0x20, chip8.memory[0x59] = 0x70; // 1
    chip8.memory[0x5A] = 0xF0, chip8.memory[0x5B] = 0x10, chip8.memory[0x5C] = 0xF0, chip8.memory[0x5D] = 0x80, chip8.memory[0x5E] = 0xF0; // 2
    chip8.memory[0x5F] = 0xF0, chip8.memory[0x60] = 0x10, chip8.memory[0x61] = 0xF0, chip8.memory[0x62] = 0x10, chip8.memory[0x63] = 0xF0; // 3
    chip8.memory[0x64] = 0x90, chip8.memory[0x65] = 0x90, chip8.memory[0x66] = 0xF0, chip8.memory[0x67] = 0x10, chip8.memory[0x68] = 0x10; // 4
    chip8.memory[0x69] = 0xF0, chip8.memory[0x6A] = 0x80, chip8.memory[0x6B] = 0xF0, chip8.memory[0x6C] = 0x10, chip8.memory[0x6D] = 0xF0; // 5
    chip8.memory[0x6E] = 0xF0, chip8.memory[0x6F] = 0x80, chip8.memory[0x70] = 0xF0, chip8.memory[0x71] = 0x90, chip8.memory[0x72] = 0xF0; // 6
    chip8.memory[0x73] = 0xF0, chip8.memory[0x74] = 0x10, chip8.memory[0x75] = 0x20, chip8.memory[0x76] = 0x40, chip8.memory[0x77] = 0x40; // 7
    chip8.memory[0x78] = 0xF0, chip8.memory[0x79] = 0x90, chip8.memory[0x7A] = 0xF0, chip8.memory[0x7B] = 0x90, chip8.memory[0x7C] = 0xF0; // 8
    chip8.memory[0x7D] = 0xF0, chip8.memory[0x7E] = 0x90, chip8.memory[0x7F] = 0xF0, chip8.memory[0x80] = 0x10, chip8.memory[0x81] = 0xF0; // 9
    chip8.memory[0x82] = 0xF0, chip8.memory[0x83] = 0x90, chip8.memory[0x84] = 0xF0, chip8.memory[0x85] = 0x90, chip8.memory[0x86] = 0x90; // A
    chip8.memory[0x87] = 0xE0, chip8.memory[0x88] = 0x90, chip8.memory[0x89] = 0xE0, chip8.memory[0x8A] = 0x90, chip8.memory[0x8B] = 0xE0; // B
    chip8.memory[0x8C] = 0xF0, chip8.memory[0x8D] = 0x80, chip8.memory[0x8E] = 0x80, chip8.memory[0x8F] = 0x80, chip8.memory[0x90] = 0xF0; // C
    chip8.memory[0x91] = 0xE0, chip8.memory[0x92] = 0x90, chip8.memory[0x93] = 0x90, chip8.memory[0x94] = 0x90, chip8.memory[0x95] = 0xE0; // D
    chip8.memory[0x96] = 0xF0, chip8.memory[0x97] = 0x80, chip8.memory[0x98] = 0xF0, chip8.memory[0x99] = 0x80, chip8.memory[0x9A] = 0xF0; // E
    chip8.memory[0x9B] = 0xF0, chip8.memory[0x9C] = 0x80, chip8.memory[0x9D] = 0xF0, chip8.memory[0x9E] = 0x80, chip8.memory[0x9F] = 0x80; // F

    printMemory();
    ALLEGRO_DISPLAY* disp = al_create_display(64, 32);
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_resize_display(disp, 640, 480);
    while (1)  // MAIN LOOP
    {

        // FETCH

        // DECODE

        // EXECUTE
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
        al_flip_display();
    }

    al_destroy_font(font);
    al_destroy_display(disp);

    return 0;
}
