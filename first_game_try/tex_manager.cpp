
#include"game_class.hpp"
#include "tex_manager.h"
SDL_Texture* TextureManger ::   loadTexture(std:: string filename ){
                IMG_Init(IMG_INIT_PNG);
                SDL_Surface *  sdsa;
                 std::cout<< sdsa;
                 SDL_Renderer * rendererer ;
                SDL_Surface * tempsur = sdsa;
                tempsur = IMG_Load(filename.c_str() ) ;
                SDL_Texture* tex = SDL_CreateTextureFromSurface ( Game::renderer  , tempsur );
                std::cout<<"got the texture";
                if (!tempsur)
                    std::cout<<"image not loaded" << IMG_GetError();
                SDL_FreeSurface (tempsur);
                return tex; 

            }
            void TextureManger :: render_tex (SDL_Texture* tex , SDL_Rect  & src, SDL_Rect  & dst , SDL_RendererFlip flip ){
                     SDL_RenderCopyEx ( Game ::renderer, tex ,  &src , &dst , NULL , NULL , flip);

            } 