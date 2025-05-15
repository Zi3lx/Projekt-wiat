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

void Mlecz::action(World* world) 
{
    Position myPos = this->getPosition();

    // Nowe mlecze
    Position freePositions = world->getRandomFreePosition();
    if (rand() % 5 == this->getPowerToReproduce()) {
        Organism* newGrass = new Mlecz(*this);

        newGrass->setPosition(freePositions);
        newGrass->setLiveLength(6);

        world->addOrganism(newGrass);
    }
}