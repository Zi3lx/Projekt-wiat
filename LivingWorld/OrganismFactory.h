// OrganismFactory.h
#pragma once
#include <string>
#include <map>
#include <functional>
#include "Organism.h"
#include "Species/Sheep.h"
#include "Species/Wolf.h"
#include "Species/Grass.h"
#include "Species/Mlecz.h"
#include "Species/Muchomor.h"

class OrganismFactory {
private:

    using CreatorFunction = function<Organism*()>;
    static map<string, CreatorFunction> creators;
    
public:

    static void registerType(const string& type, CreatorFunction creator);
    
    static Organism* createOrganism(const string& type);
   
    static void initialize();
};