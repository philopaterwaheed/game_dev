
#include"game_class.hpp"
SDL_Texture* TextureManger ::   loadTexture(const char * filename ){
                SDL_Surface * tempsur = IMG_Load(filename ) ;
                SDL_Texture* tex = SDL_CreateTextureFromSurface ( Game::renderer , tempsur );
                SDL_FreeSurface (tempsur);
                return tex; 

            }
            void TextureManger :: render_tex (SDL_Texture* tex , SDL_Rect  & src, SDL_Rect  & dst ){
                     SDL_RenderCopy ( Game ::renderer, tex ,  &src , &dst);

            } 