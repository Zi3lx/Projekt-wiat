#include "Sheep.h"
#include "../World.h"
#include "../Plant.h"
#include <iostream>

Sheep::Sheep(int power, Position position) : Animal(power, position)
{
    setSpecies("S");
    setInitiative(3);
    setLiveLength(10);
    setPowerToReproduce(6);
}

Sheep::Sheep() : Animal(3, Position(0, 0))
{
    setSpecies("S");
    setInitiative(3);
    setLiveLength(10);
    setPowerToReproduce(6);
}

void Sheep::reproduce(World* world)
{
    if (this->getPower() > this->getPowerToReproduce()) {
        int newPower = this->getPower() - 1;
        this->setPower(newPower);
        
        std::vector<Position> freePositions = world->getVectorOfFreePositionsAround(getPosition());
        if (!freePositions.empty()) {
            int randomPos = rand() % freePositions.size();
            Sheep* newSheep = new Sheep(*this);

            newSheep->setPosition(freePositions[randomPos]);
            newSheep->setPower(newPower);
            newSheep->setLiveLength(10);
            newSheep->addAncestor(world->getTurn(), world->getTurn() + newSheep->getLiveLength());

            world->addOrganism(newSheep);
        }
    }
}

void Sheep::action(World* world)
{   
    bool hasEaten = false;
    Position myPos = this->getPosition();
    
    // Poszukiwanie rośliny do zjedzenia
    for (int dx = -1; dx <= 1 && !hasEaten; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            
            int newX = myPos.getX() + dx;
            int newY = myPos.getY() + dy;
            
            if (world->isPositionOnWorld(newX, newY)) {
                Organism* nearby = world->getOrganismPointerFromPosition(newX, newY);

                if (nearby != nullptr) {
                    IEatable* plantToEat = dynamic_cast<IEatable*>(nearby);
                    if (plantToEat != nullptr) {
                        plantToEat->ifEaten(this, 1, world);
                        hasEaten = true;
                        break;
                    }
                }
            }
        }
    }
    
    if (!hasEaten) {
        move(world);
    }
    
    reproduce(world);
}

void Sheep::ifMeatEaten(Organism* other, int power, World* world)
{
    std::cout << "Tura " << world->getTurn() << " Owca została zjedzona przez " << other->getSpecies() << std::endl;
    other->setPower(other->getPower() + power);
    world->removeOrganism(this);
}