#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "BaseObject.h"
#include "CommonFunc.h"
#include <fstream>

#define GRAVITY_SPEED 1
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 3
#define JUMP_VAL 15


class Player : public BaseObject
{
public:
    Player();
    ~Player();

    enum WalkType{
        Walk_Right = 0,
        Walk_Left = 1,
        Jump_ = 2,
    };

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void show(SDL_Renderer* des);
    void Update_Img(SDL_Renderer* screen);
    void HandleInputAction(SDL_Event event, SDL_Renderer* screen);
    void set_clips();

    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);
    void setMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}
    void MoveMap(Map& map_data);

    private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[8];
    Input input_type;
    int frame_;
    int status;

    bool on_ground;

    int map_x_;
    int map_y_;

};



#endif // PLAYER_H_INCLUDED
