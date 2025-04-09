#include "Timer.h"
#include "CommonFunc.h"

Timer::Timer()
{
    start_tick = 0;
    pause_tick = 0;
    is_paused = false;
    is_started = false;
}

Timer::~Timer()
{

}

void Timer::start()
{
    is_started = true;
    is_paused = false;

    start_tick = SDL_GetTicks();
}

void Timer::stop()
{
    is_paused = false;
    is_started = false;
}

void Timer::paused()
{
    if(is_started)
    {
        is_paused = true;
        pause_tick = SDL_GetTicks() - start_tick;
    }
}

void Timer::unpaused()
{
    if(is_paused)
    {
        is_paused = false;
        start_tick = SDL_GetTicks();
        pause_tick = 0;
    }
}

int Timer::get_ticks()
{
    if(is_started)
    {
        if(is_paused) return pause_tick;

        else return SDL_GetTicks() - start_tick;
    }

    return 0;
}


