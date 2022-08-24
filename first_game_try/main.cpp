
#include "game_class.hpp"

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720
const int FPS =120;
const int FrameDelay = 1000/FPS;
 Uint32  FrameStart ;
 int FrameTime ; 
Game *game = nullptr; 
SDL_Renderer * Game:: renderer = nullptr;
int main(int argc, char** argv){
       game = new Game(); 
        game -> init("game", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,500,500,0/*FULL SCREEN */ );
        while (game -> running()){
            //std :: cout << "works" ;
            FrameStart =SDL_GetTicks(); 
           
            game -> update();
            game-> render();
            FrameTime =SDL_GetTicks() - FrameStart ;  
            if (FrameDelay>FrameTime)
                SDL_Delay(FrameDelay-FrameTime); 
            game-> handle_eve();
        }
    game->clean();
    
}

// g++   -lmingw32 -lSDL2main  -mwindows  -o main main.cpp -lSDL2 ; if ($?) { .\main }






