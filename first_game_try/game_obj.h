#pragma once 
#include <SDL2/SDL.h>
#include"comps.h"
// keeping this while having an entity system for expermental tests 
class game_obj 
{
   
public:
game_obj()= default;
    game_obj(const char* filename  , int x , int y , bool enemy   );
    ~game_obj() {};
     void update();
     void render ();
    void e_push (); 
    void enemy_move ();
private:

 bool is_enemy = false ; 
int xpos , ypos ; 
SDL_Texture * tex = nullptr ;
SDL_Rect srcr , desr ;
int lunch ;
};
