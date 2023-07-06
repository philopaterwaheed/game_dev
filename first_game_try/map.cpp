#include "map.hpp"
#include <fstream>
extern Manager manager;
Map::Map(){
    // this constructor should take the file as a level ;
    int x =0  ,y =0  ; 
    map.open( "map.map" );
        if( map.fail() )
    {
        printf( "Unable to load map file!\n" );
    }
   else
    {
        //Initialize the tiles
        for( int i = 0; i < TOTAL_TILES; ++i )
        {
            // Determines what kind of tile will be made
            int tileType = -1;

            //Read tile from map file
            map >> tileType;
            //If the was a problem in reading the map
            if( map.fail() )
            {
                //Stop loading map
                printf( "Error loading map: Unexpected end of file!\n" );
                break;
            }
        
                //If the number is a valid tile number
                if( ( tileType >=0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
                {
                    std :: cout << tileType << " tile type" ; 
                    AddTile(0,0,x*tileSize,y*tileSize, tileType);
                }
            x++ ; 
            if (x> RAWS-1)  
            {
                x=0;
                y++ ; 
            }
            //If we don't recognize the tile type
            // else
            // {
            //     //Stop loading map
            //     printf( "Error loading map: Invalid tile type at %d!\n", i );

            //     break;
            // }
            
            // y++  ; 
        }
    
    map.close();
}}

Map::~Map(){}
void Map::loadMap(std::string path , int sizex , int sizey){

    char tile ; 
    std::fstream mapfile ;
        mapfile.open(path) ; 
        int srcX , srcY ; 
        for (int x = 0 ;  x < sizex ; x++  )
            {
                mapfile.get(tile);
            }

        mapfile.close();



}
void Map::AddTile(int srcX, int srcY, int xpos, int ypos ,int id)
{
    // std :: cout << "enterd " << id << "id " ;

	auto& tile(manager.addEntity());
	tile.addcomp<tileComp>(srcX, srcY, xpos, ypos, tileSize, mapScale, id);

	tile.addGroup(group_map);
}




