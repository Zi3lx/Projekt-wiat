#include "OrganismFactory.h"


map<string, OrganismFactory::CreatorFunction> OrganismFactory::creators;

void OrganismFactory::initialize() 
{
    registerType("S", []() { return new Sheep(); });
    registerType("W", []() { return new Wolf(); });
    registerType("G", []() { return new Grass(); });
    registerType("D", []() { return new Mlecz(); });
    registerType("T", []() { return new Muchomor(); });
}


void OrganismFactory::registerType(const string& type, CreatorFunction creator) 
{
    creators[type] = creator;
}

Organism* OrganismFactory::createOrganism(const string& type) 
 {
    auto it = creators.find(type);
    if (it != creators.end()) 
    {
        return it->second();
    }
    return nullptr;
}