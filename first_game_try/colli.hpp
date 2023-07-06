
#include <SDL2/SDL.h>
class colliderComp ;
struct colli {
    public:
    static bool AABB (const SDL_Rect& recA ,const SDL_Rect& recB ) ; 
    static bool AABB ( colliderComp & colA ,  colliderComp & colB);
    static bool grounded( colliderComp & colA ,  colliderComp & colB);
    static void over_lap (const SDL_Rect recA , const SDL_Rect recB);
};