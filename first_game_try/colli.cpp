#include <iostream>
#include "colli.hpp"
#include "comps.h"
#include"music.hpp"

bool colli::AABB (const SDL_Rect& recA ,const SDL_Rect& recB ) {
   if ( 
        recA.x +recA.w > recB.x &&
        recB.x + recB.w > recA.x &&
        recA.y + recA.h > recB.y &&
        recB.y + recB.h > recA.y
    )
            {
                
                return 1;
            }
    return 0;
}
bool colli::grounded ( colliderComp & colA ,  colliderComp & colB)
{
        if(SDL_HasIntersection(&colA.phy_collider, &colB.phy_collider) && colA.collider.y < colB.collider.y )
                {
                    //note do a function for the over lap
                    int overlapX = std::min(colA.phy_collider.x + colA.phy_collider.w, colB.phy_collider.x + colB.phy_collider.w) - std::max(colA.phy_collider.x, colB.phy_collider.x);
                    int overlapY = std::min(colA.phy_collider.y+ colA.phy_collider.h, colB.phy_collider.y + colB.phy_collider.h) - std::max(colA.phy_collider.y, colB.phy_collider.y);
                    if (colA.phy!= NULL && overlapY < overlapX)
                            {
                                colA.phy->grounded=1;
                                Game::hit_ground= 1;
                            }

                  return true;
                } 
            else if (!Game::hit_ground) {
                    colA.phy->grounded= 0;
                    return false;
            } 
        else 
            return false  ;
}
bool colli::AABB ( colliderComp & colA ,  colliderComp & colB){
     
    if(colA.tag != colB.tag )
            {
                grounded(colA , colB) ;
    if  (SDL_HasIntersection(&colA.collider , &colB.collider))
    // if (AABB(colA.collider,colB.collider))
        {   
            int overlapX = std::min(colA.collider.x + colA.collider.w, colB.collider.x + colB.collider.w) - std::max(colA.collider.x, colB.collider.x);
            int overlapY = std::min(colA.collider.y+ colA.collider.h, colB.collider.y + colB.collider.h) - std::max(colA.collider.y, colB.collider.y);
                // Move cube back to previous position
                
            //    colA.pos->axes.x -= 1* (colA.pos->velocity.x>0) - 1* (colA.pos->velocity.x < 0);
            //    colA.pos->axes.y -= 1 * (colA.pos->velocity.y >0) - 1* (colA.pos->velocity.y <0);

                // // Adjust position to prevent overlap
                if (overlapX <= overlapY) {
                    if (colA.pos->axes.x  < colB.collider.x) {
                        colA.pos->axes.x = colB.collider.x - colA.collider.w;
                    }
                    else {
                        colA.pos->axes.x = colB.collider.x + colB.collider.w;
                    }
                }
                else {
                    if (colA.pos->axes.y <= colB.collider.y) {
                        colA.pos->axes.y= colB.collider.y - colA.collider.h;

                    }
                    else {
                        colA.pos->axes.y= colB.collider.y + colB.collider.h;
                        
                    }
                }
            int r_overlapX = std::min(colA.real_collider.x + colA.real_collider.w, colB.real_collider.x + colB.real_collider.w) - std::max(colA.real_collider.x, colB.real_collider.x);
            int r_overlapY = std::min(colA.real_collider.y+ colA.real_collider.h, colB.real_collider.y + colB.real_collider.h) - std::max(colA.real_collider.y, colB.real_collider.y);
                // Move cube back to previous position
                
            //    colA.pos->safe_pos.x -= 1* (colA.pos->velocity.x>0) - 1* (colA.pos->velocity.x < 0);
            //    colA.pos->safe_pos.y -= 1 * (colA.pos->velocity.y >0) - 1* (colA.pos->velocity.y <0);

                // // Adjust position to prevent overlap
                if (overlapX <= overlapY) {
                    if (colA.pos->safe_pos.x  < colB.real_collider.x) {
                        colA.pos->safe_pos.x = colB.real_collider.x - colA.real_collider.w;
                    }
                    else {
                        colA.pos->safe_pos.x = colB.real_collider.x + colB.real_collider.w;
                    }
                }
                else {
                    if (colA.pos->safe_pos.y <= colB.real_collider.y) {
                        colA.pos->safe_pos.y= colB.real_collider.y - colA.real_collider.h;
                    }
                    else {
                        colA.pos->safe_pos.y= colB.real_collider.y + colB.real_collider.h;
                    }
                }


            return true;
            }
        else {
        
        return false;}
            return true;
        }
      return false;

    }
