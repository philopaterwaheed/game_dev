#include <iostream>
#include "music.hpp"
Mix_Music* Music_Dj :: load_music (char * path) {
    Mix_Music* gMusic ;
    gMusic = Mix_LoadMUS (path);
     if( gMusic == NULL )
    {
        std ::cout <<  "Failed to load beat music! SDL_mixer Error:" <<  Mix_GetError() << "\n" ;
    }
    else 
        std :: cout << "got music " ; 
    return gMusic ; 

}