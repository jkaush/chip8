#include "core/chip8.h"
#include "platform/platform.h"
#include <SDL3/SDL.h>
#include <stdio.h>

int main()
{
    struct chip8_t chip8;
    chip8_initialize(&chip8);
    const char* rom_path = "roms/ibm.ch8";
    if (!chip8_load_rom(&chip8, rom_path)) {
        return 1;
    }

    printf("Loaded ROM: %s\n", rom_path);

    // struct platform_t* platform = create_platform("CHIP-8 Emulator", CHIP8_WIDTH, CHIP8_HEIGHT, 10);
    // if (!platform) {
    //     printf("Failed to create platform\n");
    //     return 1;
    // }

    // // Draw a line
    // for (int i = 0; i < CHIP8_WIDTH; i++) {
    //     chip8.screen[i][15] = 1;
    // }

    // bool running = true;
    // while (running) {
    //     running = process_events(platform);
    //     update_screen(platform, chip8.screen);
    //     SDL_Delay(16);
    // }

    // destroy_platform(platform);
    return 0;
}

