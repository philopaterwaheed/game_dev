#pragma once 
#include <string>
#include <fstream>
#include "comps.h"

extern Manager manager;
enum grouplabels : std::size_t // render groups  
{      
        group_map,
        group_players,
        group_enemies,
        group_colliders

 };
class Map 
{
    private:
    const int TILE_WIDTH = 89;
    const int TILE_HEIGHT = 15;
    const int COLS = 80;  
    const int RAWS =  80;
    const int TOTAL_TILES = COLS * RAWS;
    const int TOTAL_TILE_SPRITES = 12;
	std::string texID;
	int mapScale =1 ;
	int tileSize = 32 ;
	int scaledSize;
    std::ifstream map;
    public : 
        Map();
        ~Map();
        void loadMap (std:: string path ,int sizeX , int sizeY ) ; 
        void AddTile(int srcX, int srcY, int xpos, int ypos ,int );


};