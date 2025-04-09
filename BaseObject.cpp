#include "BaseObject.h"
BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    Free();
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface != NULL)
    {
        newTexture = SDL_CreateTextureFromSurface(screen, loadSurface);
        if (newTexture != NULL)
        {
            rect_.w = loadSurface->w;
            rect_.h = loadSurface->h;
        }
        SDL_FreeSurface(loadSurface);
    }
    p_object_ = newTexture;
    return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip/* = NULL*/)
{

    SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopy(des, p_object_, clip, &renderQuad);
}
void BaseObject::Free()
{
    if(p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
