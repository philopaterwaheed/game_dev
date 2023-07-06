#include <vector> 
#include "colli.hpp"
#include "map.hpp"
#include <utility>
#include "music.hpp"
Manager manager ;

auto & player {manager.addEntity()};
SDL_Rect start_point {0,0,0,0},player_real{0,0,0,0};
auto & end_point{manager.addEntity()};  
auto & enemy_1 (manager.addEntity());
auto & tile0 (manager.addEntity());
Mix_Music *gMusic = NULL;
SDL_Texture* texc; 
Map * map = nullptr;
SDL_Rect src,drc  , Game:: Camera { 0,0,600,320 }, Game:: camera { 0,0,600,320 };
SDL_Event Game :: event; 
std ::vector<colliderComp*> Game::colliders;// colidable objects  
bool Game :: hit_ground =0  ; 
         
 void Game :: init(const char* title , int x_p , int y_p , int width , int hight , bool full_screen ){
        int flags = 0;
            if (full_screen)    
                flags = SDL_WINDOW_FULLSCREEN; 

        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0){ // init sdl 
                std:: cout << "Error: SDL failed to initialize\nSDL Error: \n "<< SDL_GetError();
               // return 1;
            }
            else { 
                std:: cout << "SDL inited "; 
                window = SDL_CreateWindow( title ,  x_p ,  y_p , width ,  hight ,  flags);
                    if (window)
                        std:: cout << " window created "; 
                renderer = SDL_CreateRenderer(window, -1,0);    
                    if (renderer) {
                    isRunning =  true;
                    SDL_SetRenderDrawColor(renderer,32, 43, 195,80);
                    std:: cout << "renderer created " ; 

                    }
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                }
                else {
                        // gMusic = Music_Dj::load_music ("assets/main_music.mp3") ;
                        // Mix_PlayMusic(gMusic,-1);
                }                  
            }
        
        
        

        map = new Map();
        //  player.addcomp <posComp> (260,260,32,32,2);
         player.addcomp <posComp> (050,050,32,32,3);
         player_real.x = player.getComp<posComp>().axes.x;
         player.addcomp <spritComp> ("assets/player_anims.png",1,0);
         player.addcomp<phyComp>();
         player.addcomp <colliderComp> ("player");
         player.addcomp<kbcomp> ();
         player.addGroup(group_players);
         enemy_1.addcomp <posComp> (650,650,32,32,2);
         enemy_1.addcomp <spritComp> ("assets/Urhan.png",0,1);
         enemy_1.addcomp <colliderComp> ("enemy");
         enemy_1.addcomp<kbcomp> ();
         enemy_1.addGroup(group_enemies);

         player.addGroup(group_enemies);
         tile0.addcomp <tileComp> (0,0,0,150,1,1,5) ;
         tile0.addcomp <colliderComp> ("wall");
         tile0.addGroup(group_map);
}        
void Game:: handle_eve (){
        // handle events  of the keyboard 
        isRunning = true ;
      while (SDL_PollEvent(&event))
       {
        
        
          if (event.type == SDL_QUIT) 
                isRunning = false;
     
       if (Game::event.type == SDL_KEYDOWN){
                        switch ( Game::event.key.keysym.sym )
                        {
                        case SDLK_w: // up
                               player.getComp<kbcomp>().pos->velocity.y = -1 ; // here is - just because the origin in on the top left ; 
                                // player.getComp<kbcomp>().sprite->play("walk");
                                
                                break;
                         case SDLK_a: // left
                                // player.getComp<kbcomp>().sprite->play("walk");
                                player.getComp<kbcomp>().sprite->spriteflip = SDL_FLIP_HORIZONTAL;
                                player.getComp<kbcomp>().pos->velocity.x = -1 ;
                                // player.getComp<kbcomp>().sprite->play("walk");
                                
                                break;
                        case SDLK_d: // right
                              player.getComp<kbcomp>().pos->velocity.x =1 ;
                        //       player.getComp<kbcomp>().sprite->play("walk");/
                                break;
                        case SDLK_s: // down
                             player.getComp<kbcomp>().pos->velocity.y = 1 ;
                        //      player.getComp<kbcomp>().sprite->play("walk");
                                break;
                        case SDLK_LCTRL :
                                player.getComp<kbcomp>().sprite->play("crouch");
                                break;
                        case SDLK_SPACE:
                                if (player.getComp<phyComp>().grounded)
                                player.getComp<phyComp>().jump();
                                break;
                        case SDLK_ESCAPE :
                                isRunning=0;
                        default:
                                break;
                     } 
                if (player.getComp<kbcomp>().pos->velocity.x != 0 ) {
                        player.getComp<kbcomp>().sprite->play("walk");
                }
                    
                     }
        else if (Game::event.type == SDL_KEYUP){
                
        switch (Game :: event.key.keysym.sym)
        
        {  
                
                case SDLK_w :
                       player.getComp<kbcomp>(). pos -> velocity.y =  0;
                        
                        break;
      
                case SDLK_a:
                      player.getComp<kbcomp>(). pos->velocity.x = 0 ;
                //       player.getComp<kbcomp>().sprite->play("idle");
                       player.getComp<kbcomp>().sprite->spriteflip = SDL_FLIP_NONE;
                     
                                break;
                case SDLK_d:
                       player.getComp<kbcomp>(). pos->velocity.x = 0;
                //        player.getComp<kbcomp>().sprite->play("idle");
                                break;
                        
                case SDLK_s :
                        player.getComp<kbcomp>().pos->velocity.y = 0 ;
                        // player.getComp<kbcomp>().sprite->play("idle");
                                break;
                default:
                                break;      
        }
            if (player.getComp<kbcomp>().pos->velocity.x == 0) {
                        player.getComp<kbcomp>().sprite->play("idle");
                }
           }
     
       }
}
void Game :: update (){
        manager.update(); // updates all enttieis that has update function
        Camera.x = static_cast<int>(player.getComp<posComp>().axes.x /*  +  (player.getComp<posComp>().width*player.getComp<posComp>().scale/ 2 )  */ -( 1200 / 2));
	Camera.y = static_cast<int>(player.getComp<posComp>().axes.y  +  /* (player.getComp<posComp>().height*player.getComp<posComp>().scale/ 2 )  */- 640 / 2); 
        // start_point.getComp<posComp>().axes.x = static_cast<int>(player.getComp<posComp>().axes.x /*  +  (player.getComp<posComp>().width*player.getComp<posComp>().scale/ 2 )  */ -( 1200 / 2));
        // std :: cout <<     player.getComp<posComp>().safe_pos.x <<" <x y>"<<player.getComp<posComp>().safe_pos.y;       
        // if (start_point.getComp<posComp>().axes.x=603)
        // start_point.getComp<posComp>().axes.x = static_cast<int>(player.getComp<posComp>().axes.x /*  +  (player.getComp<posComp>().width*player.getComp<posComp>().scale/ 2 )  */ -( 1200 / 2));
	if (static_cast<int>(player.getComp<posComp>().safe_pos.x)-start_point.x < 600)
        //  start_point.getComp<posComp>().axes.x=600;
                Camera.x = 0;
        
         if (static_cast<int>(player.getComp<posComp>().safe_pos.y)-start_point.y < 320)
		Camera.y = 0;
	// if (Camera.x > Camera.w)
	// 	Camera.x = Camera.w;
	// if (Camera.y > Camera.h)
	// 	Camera.y = Camera.h;

        for (auto cc : colliders)
                {
                        colli::AABB ( player.getComp<colliderComp>() , *cc ) ;

                }
        hit_ground = 0 ; 
       SDL_SetRenderDrawColor(renderer,32, 43, 195,80);
    } 
auto& tiles(manager.getGroup(group_map));
auto& players(manager.getGroup(group_players));
auto& enemies(manager.getGroup(group_enemies));
void Game:: render (){
        SDL_RenderClear(renderer);
        //this is where to add stuff to renderer
        // to print on the background 
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &Camera);
        for (auto& p : players)
                p->draw();
        for (auto& t : tiles )
                t->draw();
                // std :: cout << tiles.size(); 
        for (auto& e : enemies)
                e->draw();

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
