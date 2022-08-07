#include <SDL2/SDL.h>
class TextureManger 
{
    public:
            static SDL_Texture* loadTexture(const char * filename );

             static void render_tex ( SDL_Texture* tex , SDL_Rect  &src, SDL_Rect&  dst);

};