#include "Wolf.h"
#include "../World.h"
#include "../IMeatEatable.h"
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

void Wolf::action(World* world) 
{
    bool flag = true;
    Position myPos = this->getPosition();

    // Zjedzenie
    for (int dx = -1; dx <= 1 && flag; dx++) 
    {
        for (int dy = -1; dy <= 1; dy++) 
        {
            if (dx == 0 && dy == 0) continue;
            
            int newX = myPos.getX() + dx;
            int newY = myPos.getY() + dy;
            
            if (world->isPositionOnWorld(newX, newY)) 
            {
                Organism* organismToEat = world->getOrganismPointerFromPosition(newX, newY);

                if (organismToEat && dynamic_cast<IMeatEatable*>(organismToEat)) 
                {
                    IMeatEatable* wolfEatable = dynamic_cast<IMeatEatable*>(organismToEat);
                    Position eatablePos = organismToEat->getPosition();
                    
                    wolfEatable->ifMeatEaten(this, 2, world);
                    
                    flag = false;
                    break;
                }
            }
        }
    }

    Animal::action(world);

    // Rozmnazanie
    if (this->getPowerToReproduce() < this->getPower())
    {
        int newPower = this->getPower() / 2;
        this->setPower(newPower);
        
        vector<Position> freePositions = world->getVectorOfFreePositionsAround(myPos);
        if (!freePositions.empty()) {
            int randomPos = rand() % freePositions.size();
            Wolf* newWolf = new Wolf(*this);

            newWolf->setPosition(freePositions[randomPos]);
            newWolf->setPower(newPower);
            world->addOrganism(newWolf);
        }
        return; 
    }

}