#include "ent.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "game_class.hpp"
#include "vector_2d.h"
#include "anime.hpp"
#include <map>
// ! replace !
// to add an entity create a manager object with ---> auto & !object name !  (manager.addEntity());
// to add a comp to the entity ----> !objectname !. addcomp <!Comp name > ( ); this happens to the manager obj
// to call a comp instas    !mangar object name !.getComp<!Comp name!>().variable or function ()  
// to use an attribute of a comp from another comp  make a pointer then ! the pointer = &entity->getComp<2ndComp>();!
class posComp : public comp{
  // a class to handle the position of the entity 
public :
        vector_2d axes ,velocity{0,0} , safe_pos,middel  ;
        
        int height =32 ; // hight of the sprite  
        int width = 32 ; // width ~~ ~~  ~~
        int scale = 1 ; // multiplyed with those ^^
        int speed =3 ; // speed of moving 
        int xpos , ypos ;
    int x () {return xpos; } 
    int y () {return ypos; }
        posComp ()      {  axes.zero(); /* start at position 0 */ }
        posComp (float x , float y )
                {
                        axes.x = x ; axes.y =y ; 
                        safe_pos.x = x ; safe_pos.y= y; 
                }
        posComp (float x , float y , int h , int w  , float sc)
   
                {
                        axes.x = x ; axes.y =y ; height = h ; width = w ; scale = sc ;
                        safe_pos.x = x ; safe_pos.y= y; 
                }
 void init () override 
 {
        velocity.zero();
 }
 void update() override 
 {
        axes.x += (int)(velocity.x * speed) ;
        axes.y += (int)(velocity.y * speed ) ;
        safe_pos.x += (int)(velocity.x * speed) ;
        safe_pos.y += (int)(velocity.y * speed ) ;
        middel.x=static_cast<int>(axes.x+width*scale/2);
        middel.y=static_cast<int>(axes.y+height*scale/2);
        axes.x =static_cast<int> (axes.x  - Game::Camera.x) ;
        axes.y =static_cast<int> (axes.y  - Game::Camera.y) ;
 }
};
class spritComp : public comp{
// a class to handle the sprite sheet of the entity         
private :
        posComp * pos ;
         bool animeated =0 ;
         int frames  ; 
         int a_speed  = 100 ; // the speed of the animation    
public:
        bool relative  ; // to be drawn in the respect to the camira
        SDL_RendererFlip spriteflip  = SDL_FLIP_NONE ;//; // for handling flipping 
        int animeindix = 0 ; 
        std :: map <const char* , anime > animations; // the animations variances 
        SDL_Rect srcRect , destRect ;
        SDL_Texture *texture ;
        spritComp () = default ; // sets the constructor to defualt (empty) 
        spritComp (const char* filename )        
            {   
                 texture = TextureManger::loadTexture (filename) ;
            }
        spritComp (const char* path , bool animeated , bool relative = 0 )
                {
                        this -> animeated =  animeated  ; 
                        anime idle {0,3,a_speed} ; // the numbers acording to the sprite you have 
                        anime walk {1,8,a_speed} ;
                        anime crouch {2,2,a_speed} ;
                        animations.emplace ("idle", idle);
                        animations.emplace ("walk", walk);
                        animations.emplace ("crouch", crouch);
                        texture = TextureManger::loadTexture (path) ;
                        play("idle");
                        this->relative = relative;
                }
        void init() override{ 
        pos = &entity->getComp<posComp>();
                         srcRect.h = 32 ;
                         srcRect.w =32 ; 
                         srcRect.x =0 ;
                         srcRect.y =0 ; 
                        // the sizes you want to take from image
       // pos->xpos++;
    }
    void update() override{
        
        if (animeated)
                {
                        srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / a_speed /*the delay */) % frames) ;
                }
                srcRect.y = animeindix * pos->height ;
                         destRect.h = (srcRect.h  * pos->scale ); 
                         destRect.w=  (srcRect.w  * pos->scale) ;
                         destRect.x =static_cast<int> (pos->axes.x); 
                         destRect.y =static_cast<int> (pos->axes.y );

        if (relative) {


        }
    }   
    void draw() override { // for all sprite drawing 
      
        TextureManger :: render_tex( texture , srcRect ,  destRect , spriteflip );
      
    }
    void play (const char* a_name )
        {
                frames = animations [a_name].frames;
                animeindix = animations [a_name].index;
        }


};
/* keyboard handle */
class kbcomp  : public comp {
             
public : 
        posComp * pos ;
        spritComp *sprite ;   
        
        void init() override {
                pos = &entity->getComp<posComp>(); // gets a pointer to comp positim 
                sprite = &entity->getComp<spritComp>(); // a pointer to a sprite comp 
        }
        void  update () override { }
};
class phyComp : public comp
{
        public : 
        posComp * pos ;
        Uint32 last_time =0 ;
        Uint32 current_time =0;
        float delta_time ;
        bool grounded =0  ; 
        void init () override { 
                pos = &entity->getComp<posComp>() ;
               
        }
        void update() override 
        {
                current_time = SDL_GetTicks();
                delta_time = (current_time - last_time) / 1000.0f;
                std :: cout <<" " << grounded;
                if (!grounded&& delta_time >= .05 )
                { 
                        
                        pos->velocity.y = 1 ; 
                }
                else if (grounded)
                        {
                               pos->velocity.y = 0 ;  
                        }
        }
        void jump ()  { 
                last_time= SDL_GetTicks();
                this-> pos->velocity.y = -4 ;
                // this-> pos->safe_pos.y -= 15 ; 
                grounded = 0 ; 
        }

};
class  colliderComp : public comp {
public :
        SDL_Rect collider ,real_collider ; // a  rect to check  collision  
        SDL_Rect phy_collider ; // rayes to check colliding with the grouned 
        std :: string tag ; // 
        posComp * pos ;
        phyComp * phy ;
        spritComp * sprite;
                void init () override
                        {
                                if (!entity->hasComp<posComp>()) // if the object doesn't have a position 
                                     entity->addcomp<posComp>(0,0);
                                if (entity->hasComp<posComp>())
                                        phy = & entity->getComp<phyComp>();
                                 pos = & entity->getComp<posComp>();
                                 sprite= & entity->getComp<spritComp>();
                                 Game::colliders.push_back(this); // adds the entity to the clliders 
                        }
             
                void update () override
                        {
                        collider.x = static_cast<int>(pos->axes.x );//+ (pos->width * pos->scale * 0.175 );
                        collider.y = static_cast<int>(pos->axes.y );//+ (pos->height * pos->scale  *0.175 );
                        collider.w = static_cast<int>(pos->width * pos->scale   /* * 0.85 */  );
                        collider.h = static_cast<int>(pos->height * pos->scale   /* * 0.85   */);    
                        real_collider.x = static_cast<int>(pos->safe_pos.x );//+ (pos->width * pos->scale * 0.175 );
                        real_collider.y = static_cast<int>(pos->safe_pos.y );//+ (pos->height * pos->scale  *0.175 );
                        real_collider.w = static_cast<int>(pos->width * pos->scale   /* * 0.85 */  );
                        real_collider.h = static_cast<int>(pos->height * pos->scale   /* * 0.85   */);    
                        phy_collider ={collider.x,collider.y, collider.w, collider.h+5};

                        }
                void draw () override{
                                SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(Game::renderer, &collider);
                                SDL_RenderDrawRect(Game::renderer, &real_collider);
                                SDL_RenderDrawRect(Game::renderer, &phy_collider);
                                
                }
        colliderComp(){}
        colliderComp(std::string tag    ){
                this->tag =tag ; 

}
};
class tileComp : public comp {
public:
        posComp * pos ; 
        bool anime ;
        tileComp() =default;
        SDL_Rect tileRect ;
        SDL_Rect srcRect, destRect;
        SDL_Texture* tex ; 
        vector_2d position {} ; 
        int tileId ;
        bool path  ; 
        float scale ;
        int id ; 
        tileComp(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, int id)
                {

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;
		position.x = static_cast<float>(xpos);
		position.y = static_cast<float>(ypos);
		destRect.w = destRect.h = tsize * tscale;
                this->id =id ;
                }
        void init () override {
                entity->addcomp<posComp>(position.x, position.y, 32 , 32 , 1 ) ;
                
                pos = &entity->getComp<posComp>() ;
                // entity->addcomp<spritComp>("assets/spike.png") ;
                std :: cout << id  ;

                switch (id)
                        {
                                case 3 : 
                                        
                                         entity->addcomp<spritComp>("assets/floorr.png",0,1) ;
                                         entity -> addcomp<colliderComp>("spike");
                                        std :: cout << "loaded tex " << tex ;  
                                        break;
                                case 12: 
                                        entity->addcomp<spritComp>("assets/devil_m.png",0,1) ;
                                        entity -> addcomp<colliderComp>("spike");
                                        std :: cout << "getting map info" ; 
                                break ;
                                default :
                                break;
                                //       entity->addcomp<spritComp>("assets/devil_m.png",0,1) ;  
                        }
                }
        
        



};
