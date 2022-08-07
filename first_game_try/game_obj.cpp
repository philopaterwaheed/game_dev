#include "game_obj.h"//*
#include "game_class.hpp"
   game_obj ::game_obj(const char* filename  , int x , int y , bool enemy = 0  )
    {
            xpos =x ; ypos =y ; 
            std:: cout << "before"<< tex << " ";            
            tex = TextureManger ::   loadTexture (filename ) ;
           std:: cout  << "after" << tex << " ";    
           /*    srand(time(NULL));
          lunch = rand()%10; 
            */if(enemy)
            {        is_enemy= 1;     
                   std:: cout << "got enemy update";
                   std:: cout << tex;    
            }
    }
void game_obj :: render (){
        std :: cout << "rendered " << tex; 
        SDL_RenderCopy ( Game ::renderer, tex , NULL , NULL);
        if (is_enemy)
            std:: cout << "";

    }
void game_obj:: update(){

                         srcr.h = 32 ;
                         srcr.w =32 ; 
                         srcr.x =0 ;
                         srcr.y =0 ; 
                         desr.h =srcr.h*2; 
                         desr.w=srcr.w*2;
          desr.x  = xpos; desr.y =ypos ; 
        
       
    }
    void game_obj :: e_push(){
      
     
     /*   if (lunch <10  ){

              desr.x -- ;
                if (desr.x < 500 )
                   { render();           
                   std :: cout << " enemy should apper  on " << desr.x; 
                   
                   }
                }
       
          */     


    }
    
   void  game_obj :: enemy_move (){ 

   
  
   }  ; 