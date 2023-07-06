// to add an entity auto & entt name  (manager.addEntity());
// to add to a group just use .addgroup (the group form the enum) 
#include <array>
#include <iostream>
#include <vector>
#include<algorithm>
#include <memory>
#include<bitset>
#include "tex_manager.h"
#include "./SDL2/SDL_image.h"
class comp ;
class Entity ; 
class Manager ;
using compId = std::size_t;
using Group = std::size_t;
inline compId getCompId ()
{
    static compId lastID = 0u;
    return lastID ++ ; 


}


template<typename T > inline compId getCompId () noexcept 
{
    static compId typeID = getCompId();
    return typeID ;


}
constexpr std::size_t maxcomp = 32 ; 
constexpr std::size_t maxGroups =32 ; 
using GroupBitset = std::bitset<maxGroups>;

using compBitset = std:: bitset<maxcomp>;
using compArray = std :: array<comp*,maxcomp>; 
class comp 
{   
public:
    Entity* entity = NULL;  // a pointer to the entity we re at 
    // virtual becuase every entity should over ride them 
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
    GroupBitset groupBitset;
public :
    Manager& manager;
    Entity(Manager& mManager) : manager(mManager){}
    void update(){ 
    for (auto& c : comps ) c->update(); 
    
    }
    void draw() {for (auto& c : comps ) c->draw(); }
    bool isActive(){return true;}
    void destroy() { active = false ;}
template <typename T> bool hasComp() const
	{
		return compbitset[getCompId<T>()];
	}
    template <typename T , typename ... TArgs>
        T& addcomp (TArgs&&... mArgs)
            {   
                T* c(new T ( std::forward<TArgs>(mArgs)...) );
                c->entity = this ; 
                std :: unique_ptr <comp > uPtr {c};
                comps.emplace_back(std::move(uPtr));
                comparray[getCompId<T>()] = c ;
                compbitset [getCompId<T>()] = true ; 
                c-> init(); // enits the componnet 
                return *c ; 

                


            }
bool hasGroup (Group mGroup)
    {
        return groupBitset[mGroup] ;

    }
void addGroup (Group mGroup); // the render group 
void delGroup (Group mGroup)
    {
        groupBitset[mGroup] = false;
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
    std :: array<std::vector<Entity*> , maxGroups > groupedEnts ; 
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
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEnts[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),
				std::end(v));
		}
        entities.erase(std::remove_if(std::begin(entities),std::end(entities),[](const std :: unique_ptr<Entity> &mEntity)

            {
                return !(mEntity-> isActive());
            }),
            std::end(entities));

    

    

     }  
     void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEnts[mGroup].emplace_back(mEntity);
	}
    std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEnts[mGroup];
	}

    Entity & addEntity() { // returns an entitiy pointer  
        Entity * e = new Entity(*this);
        std ::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr)); // add the entity to a vector of entitys 
        return *e ; 

    } 
}; 