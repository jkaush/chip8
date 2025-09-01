#ifndef PLATFORM_PLATFORM_H__
#define PLATFORM_PLATFORM_H__

#include <stdbool.h>
#include <stdint.h>

struct platform_t;

struct platform_t* create_platform(const char* title, int emu_w, int emu_h, int window_scale);
void destroy_platform(struct platform_t* platform);
bool process_events(struct platform_t* platform);
void update_screen(struct platform_t* platform, const uint8_t display[64][32]);

#endif // PLATFORM_PLATFORM_H__
