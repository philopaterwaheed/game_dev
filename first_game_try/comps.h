#pragma once 
#include "ent.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "game_class.hpp"
#include "vector_2d.h"
// ! replace !
// to add an entity create a manager object with ---> auto & !object name !  (manager.addEntity());
// to add a comp to the entity ----> !objectname !. addcomp <!Comp name > ( ); this happens to the manager obj
// to call a comp instas    !mangar object name !.getComp<!Comp name!>().variable or function ()  
// to use an attribute of a comp from another comp  make a pointer then ! the pointer = &entity->getComp<2ndComp>();!
class posComp : public comp{
  // a class to handle the position of the entity 
public :
        vector_2d axes ,velocity  ;
        int speed =15 ;
   int xpos , ypos ;
    int x () {return xpos; }
    int y () {return ypos; }

   posComp (float x , float y )
   
    {
                axes.x = x ; axes.y =y ; 
           


    }
 void init () override 
 
 
 {
        velocity.x=0 ;
        velocity.y=0 ;
 }
 void update() override 
 {
        axes.x += velocity.x * speed ;
        axes.y += velocity.y * speed ;
        velocity.y=0;
        velocity.x=0;
 }
};
class spritComp : public comp{
// a class to handle the sprite sheet of the entity         
private :
        posComp * pos ;
         
        
public:
        SDL_Rect srcRect , destRect ;
        SDL_Texture *texture ;
        spritComp () = default ; 
        spritComp (const char* filename )       
            {   
                 texture = TextureManger::loadTexture (filename) ; 
   

            }
    void init() override{ 
        pos = &entity->getComp<posComp>();


       // pos->xpos++;
    }
    void update() override{
                         srcRect.h = 32 ;
                         srcRect.w =32 ; 
                         srcRect.x =0 ;
                         srcRect.y =0 ; 
                         destRect.h =srcRect.h*2; 
                         destRect.w=srcRect.w*2;
                         destRect.x = pos->axes.x;
                         destRect.y = pos->axes.y;

    }   
    void draw() override {
       // std :: cout <<" ptr" << texture ;
        TextureManger :: render_tex( texture , srcRect ,  destRect);
        // std:: cout << destRect.x;
    }



};
/* keyboard handle */
class kbcomp  : public comp {
             
public : 
        posComp * pos ;   
        void init() override {
               pos = & entity->getComp<posComp>();



        }
void update () override {  }  
      
                
        
};