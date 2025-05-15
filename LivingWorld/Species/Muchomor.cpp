#include "Muchomor.h"
#include "../World.h"


Muchomor::Muchomor(int power, Position position) : Plant(power, position) 
{
    setSpecies("T");
    setInitiative(0);
    setLiveLength(12);
    setPowerToReproduce(4);
}

Muchomor::Muchomor() : Plant(0, Position(0, 0)) {
    setSpecies("T");
    setInitiative(0);
    setLiveLength(12);
    setPowerToReproduce(4);
}

void Muchomor::action(World* world) 
{
    Position myPos = this->getPosition();

    // Rozmnazanie
    if (rand() % 10 == this->getPowerToReproduce()) {
        Position freePosition = world->getRandomFreePosition();
        Organism* newMuchomor = new Muchomor(*this);

        newMuchomor->setPosition(freePosition);
        newMuchomor->setLiveLength(12);

        world->addOrganism(newMuchomor);
    }
}

void Muchomor::ifEaten(Organism* other, int power, World* world) {
    world->removeOrganism(other);
    world->removeOrganism(this);
}