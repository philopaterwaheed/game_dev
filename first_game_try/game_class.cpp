
#include <vector> 
#include "comps.h"
Manager manager ;
auto & player (manager.addEntity()); 
SDL_Texture* texc; 
SDL_Rect src,drc ; 
SDL_Event Game :: event; 
 // create an object to handle events 
 
         
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
                    SDL_SetRenderDrawColor(renderer,32, 43, 195,80);
                    std:: cout << "renderer created " ;  
                    }
                 
                  
            }
        
        
        

       
       
         player.addcomp <posComp> ( 400,400);
         player.addcomp <spritComp> ("assets/Daryah.png");
         player.addcomp<kbcomp> ();

}
void Game:: handle_eve (){
        
        isRunning = true ;
       while (SDL_PollEvent(&event))
       {
        
        
          if (event.type == SDL_QUIT) 
                isRunning = false;
     
       if ( Game::event.type == SDL_KEYDOWN){
        //std :: cout  << " event " << Game::event.type << " key " << Game::event.key.keysym.sym ;
                        switch ( Game::event.key.keysym.sym )
                        {
                        case SDLK_w:
                               player.getComp<kbcomp>().pos->velocity.y -=1 ; // here is - just because the origin in on the top left ; 
                                break;
                         case SDLK_a:
                               player.getComp<kbcomp>().pos->velocity.x -=1 ;
                                break;
                        case SDLK_d:
                              player.getComp<kbcomp>().pos->velocity.x +=1 ;
                                break;
                        case SDLK_s:
                             player.getComp<kbcomp>().pos->velocity.y += 1 ;
                                break;
                        
                        default:
                                break;
                     } 
                     }
        if (Game::event.type == SDL_KEYUP){
                std :: cout << "pllaa" ;
                switch (Game :: event.key.keysym.sym)
        
        {  
                
                case SDLK_w :
                       player.getComp<kbcomp>(). pos -> velocity.y =  0;
                        break;
      
                case SDLK_a:
                      player.getComp<kbcomp>(). pos->velocity.x = 0 ; 
                                break;
                case SDLK_d:
                       player.getComp<kbcomp>(). pos->velocity.x - 0;
                                break;
                case SDLK_s :
                        player.getComp<kbcomp>().pos->velocity.y = 0 ;
                                break;
                default:
                                break;      
        }
           }
     
       }
}
void Game :: update (){

               
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
