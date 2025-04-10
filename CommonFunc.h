#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED

#include <iostream>

#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//man hinh
const int FRAME_PER_SECOND = 40; // trong 1 giay duoc bao nhieu frame
const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#define TILE_SIZE 64
#define BLANK_TILE 0
const int MAX_MAP_X = 400;
const int MAX_MAP_Y = 10;

typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};
typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};

#endif // COMMONFUNC_H_INCLUDED
