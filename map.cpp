#include "map.h"

void GameMap::LoadMap(char* name)
{
    std::ifstream Input_file (name, std::ios::binary | std::ios::in);
    if(!(Input_file.is_open())) return;

    game_map_.max_x_ = 0;
    game_map_.max_y_ = 0;

    for(int i= 0; i<MAX_MAP_Y;i++)
    {
        for(int j=0;j<MAX_MAP_X;j++)
        {
            Input_file >> game_map_.tile[i][j];
            int val = game_map_.tile[i][j];
            if(val > 0)
            {
                if(j>game_map_.max_x_)
                {
                    game_map_.max_x_ = j;
                }
                if(i>game_map_.max_y_)
                {
                    game_map_.max_y_ = i;
                }
            }
        }
    }

    game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;

    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;

    game_map_.file_name_ = name;
    Input_file.close();
}

void GameMap::LoadTile(SDL_Renderer* screen)
{
    char file_img[20];

    for(int i=0;i<MAX_TILE;i++)
    {
        sprintf_s (file_img, "map/%d.png", i);

        std::ifstream InputImg (file_img,std::ios::binary | std::ios::in);
        if(!(InputImg.is_open())){
            continue;
        }
        InputImg.close();

        tile_mat[i].LoadImg(file_img, screen);   // neu co cac tam anh o tren thi cac bien doi tuong hinh anh nay se load len
    }
}

void GameMap::DrawMap(SDL_Renderer* screen)
{

    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;


    //can chinh man hinh neu bi thua/ thieu

    x1 = (game_map_.start_x_ % TILE_SIZE) * (-1);
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);


    y1 = (game_map_.start_y_ % TILE_SIZE) * (-1);
    y2 = y1 + SCREEN_HEIGHT + ((y1 == 0) ? 0 : TILE_SIZE);

    int map_x = game_map_.start_x_ / TILE_SIZE;
    int map_y = game_map_.start_y_ / TILE_SIZE;

    for(int i = y1; i<y2; i+= TILE_SIZE)
    {
        map_x = game_map_.start_x_/TILE_SIZE;
        for(int j = x1; j<x2;j+=TILE_SIZE)
        {
            int val = game_map_.tile[map_y][map_x];
            if(val>0)
            {
                tile_mat[val].SetRect(j,i);
                tile_mat[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}
