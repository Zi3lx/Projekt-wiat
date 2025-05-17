#include "Mlecz.h"
#include "../World.h"

Mlecz::Mlecz(int power, Position position) : Plant(power, position) {
    setSpecies("D");
    setInitiative(0);
    setLiveLength(6);
    setPowerToReproduce(2);
}

Mlecz::Mlecz() : Plant(0, Position(0, 0)) {
    setSpecies("D");
    setInitiative(0);
    setLiveLength(6);
    setPowerToReproduce(2);
}

void Mlecz::reproduce(World* world) 
{
    Position freePositions = world->getRandomFreePosition();
    if (rand() % 4 == this->getPowerToReproduce()) {
        Organism* newGrass = new Mlecz(*this);

        newGrass->setPosition(freePositions);
        newGrass->setLiveLength(6);
        newGrass->addAncestor(world->getTurn(), world->getTurn() + newGrass->getLiveLength());

        world->addOrganism(newGrass);
    }
}

void Mlecz::additionalDeserialize(istream& is) 
{
    this->setSpecies("D");
}