#include "Wolf.h"
#include "../World.h"
#include "../Interface/IMeatEatable.h"
#include <iostream>

Wolf::Wolf(int power, Position position) : Animal(power, position) 
{
    setSpecies("W");
    setInitiative(5);
    setLiveLength(20);
    setPowerToReproduce(16);
}

Wolf::Wolf() : Animal(8, Position(0, 0))
{
    setSpecies("W");
    setInitiative(5);
    setLiveLength(20);
    setPowerToReproduce(16);
}

void Wolf::reproduce(World* world)
{
    if (this->getPower() > this->getPowerToReproduce()) {
        int newPower = this->getPower() - 8;
        this->setPower(newPower);
        
        vector<Position> freePositions = world->getVectorOfFreePositionsAround(getPosition());
        if (!freePositions.empty()) {
            int randomPos = rand() % freePositions.size();
            Wolf* newWolf = new Wolf(*this);

            newWolf->setPosition(freePositions[randomPos]);
            newWolf->setPower(newPower);
            newWolf->addAncestor(world->getTurn(), world->getTurn() + newWolf->getLiveLength());
            world->addOrganism(newWolf);
        }
    }
}

void Wolf::action(World* world) 
{
    bool hasHunted = false;
    Position myPos = this->getPosition();

    for (int dx = -1; dx <= 1 && !hasHunted; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            
            int newX = myPos.getX() + dx;
            int newY = myPos.getY() + dy;
            
            if (world->isPositionOnWorld(newX, newY)) {
                Organism* nearby = world->getOrganismPointerFromPosition(newX, newY);

                if (nearby != nullptr) {
                    IMeatEatable* prey = dynamic_cast<IMeatEatable*>(nearby);
                    if (prey != nullptr) {
                        prey->ifMeatEaten(this, 2, world);
                        hasHunted = true;
                        break;
                    }
                }
            }
        }
    }

    if (!hasHunted)
    {
        move(world);
    }

    reproduce(world);
}