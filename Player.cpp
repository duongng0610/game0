#include "Player.h"
#include <iostream>

Player::Player()
{
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;

    x_val_ = 0;
    y_val_ = 0;

    width_frame = 0;
    height_frame = 0;

    status = -1;

    input_type.left_ = 0;
    input_type.right_ = 0;
    input_type.jump_ = 0;
    input_type.down_ = 0;

    on_ground = false;
    map_x_ = 0;
    map_y_ = 0;

}
Player::~Player()
{
Free();
}

bool Player::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path,screen);

    if(ret == true)
    {
        width_frame = rect_.w / 8;
        height_frame = rect_.h;
    }
    return ret;
}

void Player::set_clips()
{
    if(width_frame > 0 && height_frame > 0)
    {
         for (int i = 0; i < 8; i++)
        {
            frame_clip[i].x = width_frame* i;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}

void Player::show(SDL_Renderer* des)
{
    if(on_ground == true)
    {
         if(status == Walk_Left)   LoadImg("image//main_reverse.png",des);
         else  LoadImg("image//jump_left.png",des);

         if(status == Walk_Right) LoadImg("image/main.png",des);
         else LoadImg("image//jump_right.png",des);
    }

    if(input_type.left_ == 1 || input_type.right_ == 1 || input_type.jump_ == 1 || input_type.down_ == 1)
    {
        frame_++;
    }

    else frame_ = 0;

    if(frame_ >= 8)
    {
        frame_ = 0;
    }

    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;

    SDL_Rect* current_clip = &frame_clip[frame_];

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame, height_frame};

    SDL_RenderCopy(des,p_object_,current_clip, &renderQuad);

}

void Player::HandleInputAction(SDL_Event event,SDL_Renderer* screen)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_d:
            {
                status = Walk_Right;
                input_type.right_ = 1;
                input_type.left_ = 0;
                if(on_ground == true)  LoadImg("image//main.png",screen);
                else LoadImg("image//jump_right.png",screen);
            }
            break;
        case SDLK_a:
            {
                status = Walk_Left;
                input_type.left_ = 1;
                input_type.right_ = 0;
                if(on_ground == true)  LoadImg("image//main_reverse.png",screen);
                else LoadImg("image//jump_left.png",screen);
            }
            break;
        }
    }
    else if(event.type == SDL_KEYUP)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_d:
            {
                input_type.right_ = 0;
            }
            break;
        case SDLK_a:
            {
                input_type.left_ = 0;
            }
            break;
        }
    }

    if(event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.sym == SDLK_SPACE) input_type.jump_ = 1;
    }
}

void Player::DoPlayer(Map& map_data)
{
    x_val_ = 0;
    y_val_ +=  GRAVITY_SPEED;

    if(y_val_ >= MAX_FALL_SPEED)
    {
        y_val_  = MAX_FALL_SPEED;
    }

    if(input_type.left_ == 1)
    {

        x_val_ -= PLAYER_SPEED;
    }
    else if(input_type.right_ == 1)
    {
        x_val_ += PLAYER_SPEED;
    }
    CheckToMap(map_data);
    MoveMap(map_data);

    if(input_type.jump_ == 1)
    {
        if(on_ground == true)
        {
             y_val_ = -JUMP_VAL;
        }

        input_type.jump_ = 0;
    }
}

void Player::MoveMap(Map& map_data)
{
    map_data.start_x_ = x_pos_ - (SCREEN_WIDTH/2);
    if(map_data.start_x_ < 0) map_data.start_x_ = 0;
    else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_){
        map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
    }

    map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT/2);
    if(map_data.start_y_ < 0) map_data.start_y_ = 0;
    else if(map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_){
        map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
    }
}
void Player::CheckToMap(Map& map_data)
{
    on_ground = false;
    int x1 = 0, x2 = 0;

    int y1 = 0, y2 = 0;

    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;
    // check chieu ngang
    x1 = (x_pos_ + x_val_) / TILE_SIZE; // xac dinh o hien tai
    x2 = (x_pos_ + x_val_ + width_frame  - 1) / TILE_SIZE;  // -1 de check va cham

    y1 = (y_pos_ -1) / TILE_SIZE;
    y2 = (y_pos_ + height_min ) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val_ > 0)  // doi tuong dang di chuyen sang phai
        {
            if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                x_pos_ = x2 * TILE_SIZE - width_frame - 1;

                x_val_ = 0;
            }
        }
        else if(x_val_ <0)
        {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            {
                x_pos_ = (x1+2) * TILE_SIZE;
                x_val_ = 0;
            }
        }
    }

    // check chieu doc
    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame - 1) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(y_val_ > 0)
        {
            if(map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0)
            {
                y_pos_ = y2 * TILE_SIZE - height_frame - 1;

                y_val_ = 0; // nhan vat khong the di xuong duoc nua
                on_ground = true;
            }
        }
        else if(y_val_ < 0)
        {
            if(map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0)
            {
                y_pos_ = (y1+1) * TILE_SIZE;
                y_val_ = 0;  // khong cho phep vuot qua height map
            }
        }
    }
     x_pos_ += x_val_;
     y_pos_ += y_val_;

     if(x_pos_ < 0) x_pos_ = 0;   // khong cho lui nua
     else if(x_pos_ + width_frame > map_data.max_x_)
     {
         x_pos_ = map_data.max_x_ - width_frame -1;
     }
     if(y_pos_ <  0)
     {
         y_pos_ = 0;
     }
     else if(y_pos_ + height_frame >= map_data.max_y_)
     {
         y_pos_ = map_data.max_y_ - height_frame - 1;
         y_val_ = 0;
         on_ground = true;
     }

}

