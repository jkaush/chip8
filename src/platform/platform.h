#ifndef PLATFORM_PLATFORM_H__
#define PLATFORM_PLATFORM_H__

#include "core/chip8.h"
#include <stdbool.h>
#include <stdint.h>

struct platform_t;

struct platform_t* create_platform(const char* title, int emu_w, int emu_h, int window_scale);
void destroy_platform(struct platform_t* platform);
bool process_events(struct platform_t* platform);
void update_screen(struct platform_t* platform, const uint32_t gfxbuffer[GFX_WIDTH * GFX_HEIGHT]);

#endif // PLATFORM_PLATFORM_H__
