#include "BaseObject.h"
#include "CommonFunc.h"
#include "Map.h"
#include "Player.h"
#include "Timer.h"
BaseObject g_background;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);

    if(ret<0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");    // chong rang cua khi ve anh

    g_window = SDL_CreateWindow("game cpp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1100, 600, SDL_WINDOW_SHOWN);

    if(g_window == NULL){
        return false;
    }
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL) return false;

            SDL_SetRenderDrawColor(g_screen,0,0,0,255);
            int imgFlags = IMG_INIT_PNG;
            if((IMG_Init(imgFlags) & imgFlags) != imgFlags)
            {
                return false;
            }
        return true;
    }


bool LoadBackground()
{
    bool ret = g_background.LoadImg("image//map.png", g_screen);
    return ret;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    Timer fps_timer;


    if(InitData() == false) return -1;

    if(LoadBackground() == false) return -1;

    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTile(g_screen);

    Player p_player;
    p_player.LoadImg("image//main.png",g_screen);
    p_player.set_clips();



    bool is_quit = false;
    while(!is_quit)
    {
        fps_timer.start();
        while(SDL_PollEvent(&g_event) != 0)
        {

            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandleInputAction(g_event,g_screen);
        }
      SDL_SetRenderDrawColor(g_screen, 0,0,0,255);
      SDL_RenderClear(g_screen);

      g_background.Render(g_screen, NULL);

      Map map_data = game_map.getMap();

      p_player.setMapXY(map_data.start_x_, map_data.start_y_);
      p_player.DoPlayer(map_data);
      p_player.show(g_screen);

      game_map.setMap(map_data);
      game_map.DrawMap(g_screen);

      SDL_RenderPresent(g_screen);

      int real_time = fps_timer.get_ticks();
      int time_one_frame = 1000 / FRAME_PER_SECOND;

      if(real_time < time_one_frame)
      {
          int delay_time = time_one_frame - real_time;
          if(delay_time >=0) SDL_Delay(delay_time);
      }
    }

    close();
    return 0;
}
