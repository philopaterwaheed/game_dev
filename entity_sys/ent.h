#include <iostream>
#include <array>
#include <vector>
#include<algorithm>
#include <memory>
#include<bitset>
#include "tex_manager.h" // a texture manager in sdl2 you can find it in texture handling folder here 
#include "SDl2/SDL_image.h"
class comp ;
class Entity ; 
using compId = std::size_t;
inline compId getCompId ()
{
    static compId lastID = 0 ;
    return lastID ++ ; 


}


template<typename T > inline compId getCompId () noexcept 
{
    static compId typeID = getCompId();
    return typeID ;


}
constexpr std::size_t maxcomp = 32 ; 
using compBitset = std:: bitset<maxcomp>;
using compArray = std :: array<comp*,maxcomp>; 
class comp 
{   
public:
    Entity* entity ; 
    virtual void init () {}
     virtual void update(){} 
     virtual void draw (){}
     virtual ~comp() {}



};

class Entity {
private : 
    bool active = true ; 
    std :: vector < std::unique_ptr <comp>> comps ; 
    compArray comparray ; 
    compBitset compbitset ; 
public : 
    void update(){ 
    for (auto& c : comps ) c->update(); 
    
    }
    void draw() {for (auto& c : comps ) c->draw(); }
    bool isActive(){}
    void destroy() { active = false ;}
    template <typename T > bool hasComp() const 
    {   
        return compbitset [getCompId<T>]; 
        

    }
    template <typename T , typename ... TArgs>
        T& addcomp (TArgs&&... mArgs)
            {   
                T* c(new T (std::forward<TArgs>(mArgs)...));
                c->entity = this ; 
                std :: unique_ptr <comp > uPtr {c};
                comps.emplace_back(std::move(uPtr));
                comparray[getCompId<T>()] = c ;
                compbitset [getCompId<T>()] = true ; 
                c-> init();
                return *c ; 

                


            }
template <typename T > T& getComp() const 
{
    auto ptr (comparray[getCompId<T>()]);
    return * static_cast<T*>(ptr);
}



};
class Manager 
{
    std :: vector <std:: unique_ptr <Entity>> entities ; 
public:
    void update ()
    { 
        for (auto& e : entities) e->update();


    }
    void draw()
    {
        for(auto&e : entities) e-> draw();

    }


    void refresh(){
        entities.erase(std::remove_if(std::begin(entities),std::end(entities),[](const std :: unique_ptr<Entity> &mEntity)
    
            {
                return !(mEntity-> isActive());
            }),
            std::end(entities));

    

    

     }  
    Entity & addEntity() {
        Entity* e =new Entity();
        std ::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return*e; 

    } 
}; 
