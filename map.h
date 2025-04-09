#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "BaseObject.h"
#include "CommonFunc.h"
#include <fstream>

#define MAX_TILE 20

class TileMat : public BaseObject
{
public:
    TileMat() {;}
    ~TileMat() {;}
};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char* name);
    void LoadTile(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map_;};
    void setMap(Map& map_data) {game_map_ = map_data;};

private:
    Map game_map_;  // luu trang thai, vi tri, chi so cua o can hien thi
    TileMat tile_mat[MAX_TILE];
    const char* file_name_;
};

#endif // MAP_H_INCLUDED
