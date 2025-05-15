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

void Grass::action(World* world) {
    Position myPos = this->getPosition();

    // Nowe trawy
    vector<Position> freePositions = world->getVectorOfFreePositionsAround(myPos);
    if (rand() % 5 == this->getPowerToReproduce() && !freePositions.empty()) {
        int randomPos = rand() % freePositions.size();
        Organism* newGrass = new Grass(*this);

        newGrass->setPosition(freePositions[randomPos]);
        newGrass->setLiveLength(6);
        
        world->addOrganism(newGrass);
    }

}