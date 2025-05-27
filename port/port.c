#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#define __PORT_C__
#include "common.h"
#include "digisnd.h"
#include "hocus.h"
#include "design.h"
#include "gr.h"

#define SPECIAL_KEY (1 << 31)

void hocus_main(int argc, unsigned char **argv);

extern unsigned char *textscreen;
extern unsigned char *vgabase;
extern int *colortextbase;

byte AdLibPresent;
byte SoundBlasterPresent;

static SDL_Window *window;
static SDL_Surface *surface[VGA_PAGE_COUNT];
static SDL_Palette *sdl_palette;
static SDL_Renderer *renderer;
static TTF_Font *fps_font;
static int last_key;
static bool alt_key;
static bool ctrl_key;
static bool shift_key;
static bool designer;

int main(int argc, char *argv[])
{
    int i;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        SDL_Log("Failed to initialize SDL video");
        return EXIT_FAILURE;
    }

    if (TTF_Init() < 0)
    {
        SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    fps_font = TTF_OpenFont("FreeSans.ttf", 64);
    if (!fps_font)
    {
        SDL_Log("Failed to load font: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_CreateWindowAndRenderer("hocus", SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, 0, &window, &renderer);
    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_HideCursor();

    sdl_palette = SDL_CreatePalette(0x100);
    for (i = 0; i < sdl_palette->ncolors; i++)
    {
        sdl_palette->colors[i].r = 0;
        sdl_palette->colors[i].g = 0;
        sdl_palette->colors[i].b = 0;
    }
    if (!sdl_palette)
    {
        SDL_Log("Failed to allocate palette");
        return EXIT_FAILURE;
    }

    for (i = 0; i < VGA_PAGE_COUNT; i++)
    {
        surface[i] = SDL_CreateSurface(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_PIXELFORMAT_INDEX8);
        if (!surface[i])
        {
            SDL_Log("Failed to allocate surface %d", i);
            return EXIT_FAILURE;
        }
        if (!SDL_SetSurfacePalette(surface[i], sdl_palette))
        {
            SDL_Log("Failed to set palette");
            return EXIT_FAILURE;
        }
        SDL_SetSurfaceBlendMode(surface[i], SDL_BLENDMODE_NONE);
        assert(SDL_MUSTLOCK(surface[i]) == 0);
    }

    assert(sizeof(config_t) == 956);
    assert(sizeof(grphdr_t) == 4);
    assert(sizeof(lvlinfo_t) == 8);
    assert(sizeof(PCXHEAD) == 128);
    assert(sizeof(inf_t) == 1686);
    assert(sizeof(trigger_t) == 32);
    assert(sizeof(tag_t) == 24);
    assert(sizeof(trip_t) == 12);
    assert(sizeof(switch_t) == 22);
    assert(sizeof(warp_t) == 4);
    assert(sizeof(sprite_t) == 220);
    assert(sizeof(wiznote_t) == 504);

    last_key = 0;
    alt_key = false;
    vgabase = NULL;
    textscreen = NULL;
    colortextbase = NULL;

    designer = true;
    if (designer)
    {
        SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_DISABLED);
        new_program();
        clear_palette();
        restore_palette_fragment(7, 0, 0);
        restore_palette_fragment(8, 0x80, 0);
        level = 0;
        game = 0;
        design();
    }
    else
    {
        SDL_SetRenderVSync(renderer, 2);
        hocus_main(argc, (unsigned char **)argv);
    }

    // TODO: Cleanup all ressources?
    return 0;
}

unsigned char *get_surface_pixel(int i)
{
    return (unsigned char *)surface[i]->pixels;
}

void update_palette(unsigned char *rgb, unsigned char pel_start, int pel_count)
{
    int i;
    assert(pel_start == 0);
    assert(pel_count == sdl_palette->ncolors);
    for (i = 0; i < pel_count; i++)
    {
        sdl_palette->colors[i].r = MIN(*rgb * 4, 255);
        rgb++;
        sdl_palette->colors[i].g = MIN(*rgb * 4, 255);
        rgb++;
        sdl_palette->colors[i].b = MIN(*rgb * 4, 255);
        rgb++;
    }
}

void swap_buffer()
{
    static int previous_tick = 0;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface[vpg]);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    SDL_RenderTexture(renderer, texture, NULL, NULL);

    int tick = SDL_GetTicks();
    char buffer[32];
    sprintf(buffer, "%dms", (tick - previous_tick));
    previous_tick = tick;

    SDL_Color fps_color = {0, 255, 0, 255};
    SDL_Surface *fps_surface = TTF_RenderText_Solid(fps_font, buffer, 0, fps_color);
    SDL_FRect fps_rect = {0, 0, fps_surface->w / 3, fps_surface->h / 3};
    SDL_Texture *fps_texture = SDL_CreateTextureFromSurface(renderer, fps_surface);
    SDL_SetTextureScaleMode(fps_texture, SDL_SCALEMODE_LINEAR);
    if (!designer)
        SDL_RenderTexture(renderer, fps_texture, NULL, &fps_rect);

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(fps_texture);
}

void gotoxy(int x, int y)
{
}

void setmem(void *target, unsigned long len, char val)
{
    memset(target, val, len);
}

int getclock()
{
    // TODO: correct divisor or SDL_AddTimer
    // https://expiredpopsicle.com/articles/2017-04-13-DOS_Timer_Stuff/2017-04-13-DOS_Timer_Stuff.html
    return SDL_GetTicks() / 1.0;
}

unsigned char inportb(unsigned int port)
{
    return 0;
}

unsigned char outportb(unsigned int port, unsigned char value)
{
    return 0;
}

void setvect(int intnum, void (*handler)(void))
{
}

intfunc getvect(int interrupt arg0)
{
    return NULL;
}

void MCPY(unsigned char *dst, unsigned char *src, int size)
{
    memcpy(dst, src, size);
}

void SET320X200(void)
{
}

int int86(int inter_no, union REGS *input_regs, union REGS *output_regs)
{
    return 0;
}

void sound(int arg0)
{
}

void nosound(void)
{
}

char *SB_Startup(char *blasterEnvVar)
{
    return NULL;
}

void SB_Shutdown(void)
{
}

void SB_PlayVOC(byte huge *data, bool includesHeader)
{
}

bool SB_VOCPlaying(void)
{
    return false;
}

int rand16(void)
{
    return rand() & 0x7FFF;
}

int getch(void)
{
    int key = -1;
    SDL_Event event;

    if (!last_key)
    {
        if (designer)
            swap_buffer();

        while (1)
        {
            SDL_WaitEvent(&event);
            switch (event.type)
            {
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key)
                {
                case SDLK_LALT:
                    alt_key = true;
                    break;
                case SDLK_LCTRL:
                    ctrl_key = true;
                    break;
                case SDLK_LSHIFT:
                    shift_key = true;
                    break;
                default:
                    last_key = event.key.key;
                    return getch();
                }
                break;
            case SDL_EVENT_KEY_UP:
                switch (event.key.key)
                {
                case SDLK_LALT:
                    alt_key = false;
                    break;
                case SDLK_LCTRL:
                    ctrl_key = false;
                    break;
                case SDLK_LSHIFT:
                    shift_key = false;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
    }
    else if (last_key & SPECIAL_KEY)
    {
        last_key &= ~SPECIAL_KEY;
        if (alt_key)
        {
            switch (last_key)
            {
            case SDLK_W:
                key = KEY_ALT_W;
                break;
            case SDLK_E:
                key = KEY_ALT_E;
                break;
            case SDLK_R:
                key = KEY_ALT_R;
                break;
            case SDLK_T:
                key = KEY_ALT_T;
                break;
            case SDLK_U:
                key = KEY_ALT_U;
                break;
            case SDLK_S:
                key = KEY_ALT_S;
                break;
            case SDLK_Z:
                key = KEY_ALT_Z;
                break;
            case SDLK_B:
                key = KEY_ALT_B;
                break;
            case SDLK_M:
                key = KEY_ALT_M;
                break;
            default:
                break;
            }
        }
        else
        {
            switch (last_key)
            {
            case SDLK_F1:
                key = KEY_F1;
                break;
            case SDLK_F2:
                key = KEY_F2;
                break;
            case SDLK_F3:
                key = KEY_F3;
                break;
            case SDLK_F4:
                key = KEY_F4;
                break;
            case SDLK_F5:
                key = KEY_F5;
                break;
            case SDLK_F6:
                key = KEY_F6;
                break;
            case SDLK_F7:
                key = KEY_F7;
                break;
            case SDLK_F8:
                key = KEY_F8;
                break;
            case SDLK_F9:
                key = KEY_F9;
                break;
            case SDLK_F10:
                key = KEY_F10;
                break;
            case SDLK_HOME:
                key = KEY_HOME;
                break;
            case SDLK_UP:
                key = KEY_UP;
                break;
            case SDLK_PAGEUP:
                key = KEY_PGUP;
                break;
            case SDLK_LEFT:
                key = KEY_LEFT;
                break;
            case SDLK_RIGHT:
                key = KEY_RIGHT;
                break;
            case SDLK_END:
                key = KEY_END;
                break;
            case SDLK_DOWN:
                key = KEY_DOWN;
                break;
            case SDLK_PAGEDOWN:
                key = KEY_PGDN;
                break;
            case SDLK_INSERT:
                key = KEY_INSERT;
                break;
            case SDLK_DELETE:
                key = KEY_DELETE;
                break;
            default:
                break;
            }
        }
    }
    else if (alt_key || ctrl_key)
    {
        last_key |= SPECIAL_KEY;
        return 0;
    }
    else if (shift_key)
    {
        if ((last_key >= SDLK_A) && (last_key <= SDLK_Z))
        {
            key = last_key - 32;
        }
        else
        {
            last_key |= SPECIAL_KEY;
            return 0;
        }
    }
    else if (last_key & SDLK_SCANCODE_MASK)
    {
        switch (last_key)
        {
        case SDLK_KP_0:
            key = '0';
            break;
        case SDLK_KP_1:
            key = '1';
            break;
        case SDLK_KP_2:
            key = '2';
            break;
        case SDLK_KP_3:
            key = '3';
            break;
        case SDLK_KP_4:
            key = '4';
            break;
        case SDLK_KP_5:
            key = '5';
            break;
        case SDLK_KP_6:
            key = '6';
            break;
        case SDLK_KP_7:
            key = '7';
            break;
        case SDLK_KP_8:
            key = '8';
            break;
        case SDLK_KP_9:
            key = '9';
            break;
        default:
            last_key |= SPECIAL_KEY;
            return 0;
        }
    }
    else
    {
        key = last_key;
    }
    last_key = 0;
    return key;
}

int kbhit(void)
{
    SDL_Event event;

    if (last_key)
        return 1;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_KEY_DOWN:
            switch (event.key.key)
            {
            case SDLK_LALT:
                alt_key = true;
                break;
            case SDLK_LCTRL:
                ctrl_key = true;
                break;
            case SDLK_LSHIFT:
                shift_key = true;
                break;
            default:
                last_key = event.key.key;
                return 1;
            }
            break;
        case SDL_EVENT_KEY_UP:
            switch (event.key.key)
            {
            case SDLK_LALT:
                alt_key = false;
                break;
            case SDLK_LCTRL:
                ctrl_key = false;
                break;
            case SDLK_LSHIFT:
                shift_key = false;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
    return 0;
}

#ifndef _MSC_VER
char *itoa(int value, char *result, int base)
{
    static const char digit[] = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz";
    // check that the base is valid
    if (base < 2 || base > 36)
    {
        *result = '\0';
        return result;
    }
    char *ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;
    do
    {
        tmp_value = value;
        value /= base;
        *ptr++ = digit[35 + (tmp_value - value * base)];
    } while (value);
    // Apply negative sign
    if (tmp_value < 0)
        *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr)
    {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void strupr(char *p)
{
    while (*p)
    {
        *p = toupper(*p);
        p++;
    }
}
#endif