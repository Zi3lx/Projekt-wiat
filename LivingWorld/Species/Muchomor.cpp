#include <iostream>
#include "Muchomor.h"
#include "../World.h"

using namespace std;

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

void Muchomor::reproduce(World* world) 
{
    if (rand() % 5 == this->getPowerToReproduce()) {
        Position freePosition = world->getRandomFreePosition();
        Organism* newMuchomor = new Muchomor(*this);

        newMuchomor->setPosition(freePosition);
        newMuchomor->setLiveLength(12);
        newMuchomor->addAncestor(world->getTurn(), world->getTurn() + newMuchomor->getLiveLength());

        world->addOrganism(newMuchomor);
    }
}

void Muchomor::ifEaten(Organism* other, int power, World* world) {
    cout << "Muchomor zabił organizm " << other->getSpecies() << " podczas próby zjedzenia!" << endl;
    world->removeOrganism(this);
    world->removeOrganism(other);
}