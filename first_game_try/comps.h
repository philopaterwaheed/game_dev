#pragma once 
#include "ent.h"
#include <SDL2/SDL.h>
#include <iostream>
// ! replace !
// to add an entity create a manager object with ---> auto & !object name !  (manager.addEntity());
// to add a comp to the entity ----> !objectname !. addcomp <!Comp name > ( );
// to call a comp instas    !mangar object name !.getComp<!Comp name!>().variable or function ()  
// to use an attribute of a comp from another comp ! 1st comp = &entity->getComp<2ndComp>();!
class posComp : public comp{
  // a class to handle the position of the entity 
public :
   int xpos , ypos ;
    int x () {return xpos; }
    int y () {return ypos; }

   posComp (int x , int y )
   
    {
            xpos = x ; ypos =y ; 
           


    }
 void init () override 
 
 
 {

 }
 void update() override 
 {
   /* xpos ++ ; 
    ypos ++;    
*/

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
                         destRect.x = pos->x();
                         destRect.y = pos->y();

    }   
    void draw() override {
       // std :: cout <<" ptr" << texture ;
        TextureManger :: render_tex( texture , srcRect ,  destRect);
        std:: cout << destRect.x;
    }



};