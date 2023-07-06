#include <iostream>
#include <ctime> 
#include <SDL2/SDL.h>
#include <vector>
#include "./SDL2/SDL_image.h"
#include "./SDL2/SDL_mixer.h"
class colliderComp ;


class Game { 

public:
    Game(){}
    ~Game();
    void init(const char* title , int x_p , int y_p , int width , int hight , bool full_screen );

     
    void handle_eve ();
       
    void update ();
    void render ();
    void clean () ;
    bool running ();
    static SDL_Renderer *renderer;
    static SDL_Event event ;
    static std::vector<colliderComp*> colliders;// colidable objects  
    static bool hit_ground ; 
    static SDL_Rect Camera ;
    static SDL_Rect camera ; 
private :
bool isRunning=true; 
SDL_Window *window; 

SDL_Texture* m_pTexture;
SDL_Rect srcr , desr; 
int i=0 ;

};