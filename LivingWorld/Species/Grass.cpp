#include "Grass.h"
#include "../World.h"

Grass::Grass(int power, Position position) : Plant(power, position) {
    setSpecies("G");
    setInitiative(0);
    setLiveLength(6);
    setPowerToReproduce(3);
}

Grass::Grass() : Plant(0, Position(0, 0)) {
    setSpecies("G");
    setInitiative(0);
    setLiveLength(6);
    setPowerToReproduce(3);
}


void Grass::reproduce(World* world) 
{
    Position myPos = this->getPosition();
    
    vector<Position> freePositions = world->getVectorOfFreePositionsAround(myPos);
    if (rand() % 4 == this->getPowerToReproduce() && !freePositions.empty()) {
        int randomPos = rand() % freePositions.size();
        Organism* newGrass = new Grass(*this);

        newGrass->setPosition(freePositions[randomPos]);
        newGrass->setLiveLength(6);
        newGrass->addAncestor(world->getTurn(), world->getTurn() + newGrass->getLiveLength());
        
        world->addOrganism(newGrass);
    }
}

void Grass::additionalDeserialize(istream& is) 
{
    this->setSpecies("G");
}