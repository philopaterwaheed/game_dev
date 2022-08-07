#include "game_obj.h"
#include"game_class.hpp"
#include <vector> 

Manager manager ;
auto & player (manager.addEntity());
game_obj * m_p = nullptr;
game_obj * e_1= nullptr; 
SDL_Texture* texc; 
SDL_Rect src,drc ; 

 std ::  vector   <game_obj*> mini_enemies ; 
   game_obj obj[] = {game_obj(game_obj("assets/wetty.png",32,46,1))};         
 void Game :: init(const char* title , int x_p , int y_p , int width , int hight , bool full_screen ){
        int flags = 0;
            if (full_screen)    
                flags = SDL_WINDOW_FULLSCREEN; 

        if(SDL_Init(SDL_INIT_VIDEO) < 0){ // init sdl 
                std:: cout << "Error: SDL failed to initialize\nSDL Error: \n "<< SDL_GetError();
               // return 1;
            }
            else { 
                std:: cout << "SDL inited "; 
                window = SDL_CreateWindow( title ,  x_p ,  y_p ,  width ,  hight ,  flags);
                    if (window)
                        std:: cout << " window created "; 
                renderer = SDL_CreateRenderer(window, -1,0);    
                    if (renderer) {
                    isRunning =  true;
                    SDL_SetRenderDrawColor(renderer,32, 160, 195,80);
                    std:: cout << "renderer created " ;  
                    }
                 for ( int i =0 ; i <10  ; i++ )
                    mini_enemies.push_back(new game_obj("assets/wetty.png",32,46,1));
            }
        
        
        

        e_1= new game_obj ("assets/lvl1_e.png",0,436,1);
         m_p = new game_obj("assets/main_char.png" , 0,436,1);
       
         player.addcomp <posComp> ( 400,100);
         player.addcomp <spritComp> ("assets/daryah.png");

}
void Game:: handle_eve (){
        SDL_Event event;  // creat an object to handle events 
        isRunning = true ;
       while (SDL_PollEvent(&event))
       {
        
        
          if (event.type == SDL_QUIT) 
                isRunning = false;
     
        
       } 
          
       
    } 
void Game :: update (){
        m_p->update();
        e_1->update();
                for (auto *e : mini_enemies)
                    e->update();
        manager.update();
       // std :: cout << player.getComp<posComp>().x() << "," << player.getComp<posComp>().y() <<std:: endl ; 
    } 
    void Game:: render (){
        SDL_RenderClear(renderer);
        //this is where to add stuff to renderer
        // to print on the background 
             

      //  m_p->render();
         manager.draw();
       // e_1->render();
        SDL_RenderCopy ( Game ::renderer,  player.getComp<spritComp>().texture ,  &player.getComp<spritComp>().srcRect, &player.getComp<spritComp>().destRect);
        SDL_RenderPresent(renderer);
             for (auto *e : mini_enemies )
                e->render();
    } 
     void Game :: clean () {// for memory
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    }
    bool Game:: running (){
        if (isRunning == false )
            return false ; 
        else 
            return true ; 
    }
