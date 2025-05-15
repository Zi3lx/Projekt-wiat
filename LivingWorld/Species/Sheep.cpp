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

void Sheep::action(World* world)
{   
    bool flag = true;
    Position myPos = this->getPosition();
    
    // Zjedzenie roślin
    for (int dx = -1; dx <= 1 && flag; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            
            int newX = myPos.getX() + dx;
            int newY = myPos.getY() + dy;
            
            if (world->isPositionOnWorld(newX, newY)) {
                Organism* plantToEat = world->getOrganismPointerFromPosition(newX, newY);

                Plant* organism2 = dynamic_cast<Plant*>(plantToEat);
                if (organism2 != nullptr) {
                    organism2->ifEaten(this, 1, world);
                    flag = false;
                    break;
                }
                    
            }
        }
    }
    
    if (flag) Animal::action(world);
        
    // Sprawdzenie, czy owca ma wystarczającą moc do reprodukcji
    if (this->getPower() > this->getPowerToReproduce()) {
        
        int newPower = this->getPower() - 1 ;
        this->setPower(newPower);
        
        vector<Position> freePositions = world->getVectorOfFreePositionsAround(myPos);
        if (!freePositions.empty()) {
            int randomPos = rand() % freePositions.size();
            Sheep* newSheep = new Sheep(*this);

            newSheep->setPosition(freePositions[randomPos]);
            newSheep->setPower(newPower);
            newSheep->setLiveLength(10);
            newSheep->addAncestor(world->getTurn(), world->getTurn() + newSheep->getLiveLength());

            world->addOrganism(newSheep);
        }
        return; 
    }
}

void Sheep::ifMeatEaten(Organism* other, int power, World* world)
{
    std::cout << "Tura " << world->getTurn() << " Owca została zjedzona przez " << other->getSpecies() << std::endl;
    other->setPower(other->getPower() + power);
    world->removeOrganism(this);
}