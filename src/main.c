#include "core/chip8.h"
#include <SDL3/SDL.h>
#include <stdio.h>

int main()
{
    struct chip8_t chip8;
    init_chip8(&chip8);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "CHIP-8 Emulator",
        640,
        320,
        0
    );
    if (!window) {
        printf("Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        64,
        32
    );
    if (!texture) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    for (int i = 0; i < CHIP8_WIDTH; i++) {
        chip8.screen[i][15] = 1;
    }

    bool running = true;
    while (running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        uint32_t pixels[CHIP8_WIDTH * CHIP8_HEIGHT];
        for (int y = 0; y < CHIP8_HEIGHT; y++) {
            for (int x = 0; x < CHIP8_WIDTH; x++) {
                uint32_t color = chip8.screen[x][y] ? 0xFFFFFFFF : 0x000000FF;
                pixels[y * CHIP8_WIDTH + x] = color;
            }
        }

        SDL_UpdateTexture(texture, NULL, pixels, CHIP8_WIDTH * sizeof(uint32_t));

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("SDL initialized successfully.\n");
    return 0;
}

