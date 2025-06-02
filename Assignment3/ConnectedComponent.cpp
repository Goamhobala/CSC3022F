#include <unordered_map>
#include <set>
#include <memory>
#include <utility>
#include "ConnectedComponent.h"

using namespace yhxjin001;
using ComponentYSetPtr = std::unique_ptr<std::set<int>>;
using ComponentMap = unordered_map<int, ComponentYSetPtr>;
int ConnectedComponent::count = 0;
ConnectedComponent::ConnectedComponent(): size(0), pixels(std::make_unique<ComponentMap>()), id(-1){}
ConnectedComponent::ConnectedComponent(const ConnectedComponent & rhs):id(rhs.id), size(rhs.size){
    // std::unique_ptr<ComponentMap> this->pixels;
    pixels = std::make_unique<ComponentMap>();
    for ( const std::pair<int, ComponentYSetPtr & > & keyVal : *rhs.pixels){
        int key = keyVal.first;
        ComponentYSetPtr & value = keyVal.second;
        // to create deep copy of the set
        (*pixels)[key] = std::make_unique<std::set<int>>(* value);
    }
}

ConnectedComponent::ConnectedComponent(ConnectedComponent && rhs):id(rhs.id), size(rhs.size){
    pixels = std::move(rhs.pixels);
    rhs.id = -1;
    rhs.size = 0;
}
// ConnectedComponent::~ConnectedComponent(){} // unique pointers take care of this

ConnectedComponent & ConnectedComponent::operator=(const ConnectedComponent &rhs){
    if (this != &rhs){
        id = rhs.id;
        size = rhs.id;
        for ( const std::pair<int, ComponentYSetPtr & > & keyVal : *rhs.pixels){
            int key = keyVal.first;
            ComponentYSetPtr & rhsValues = keyVal.second;
            // to create deep copy of the set
            (*pixels)[key] = std::make_unique<std::set<int>>(*rhsValues);
        }
    }

    return *this;
}

ConnectedComponent & ConnectedComponent::operator=(ConnectedComponent && rhs){
    if (this != &rhs){
        id = rhs.id;
        size = rhs.size;
        pixels = std::move(rhs.pixels);
        rhs.id = -1;
        size = 0;
    }
    return * this;
}
/*
To add a single coordinate to the connected component
*/
void ConnectedComponent::add_point(int x, int y){
    if (!(*pixels)[x]){
        (*pixels)[x] = std::make_unique<std::set<int>>();
    }
    (*pixels)[x]->insert(y);
    ++size;
}

/*
Set component id using internal counter
*/
void ConnectedComponent::set_id(){
    id = count++;
}
/*
Overloading < to allow sorting
*/
bool ConnectedComponent::operator<(const ConnectedComponent & rhs) const {
    return this->size < rhs.size;
}
