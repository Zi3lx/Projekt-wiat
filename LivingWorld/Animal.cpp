#include "Animal.h"
#include "World.h"
Animal::Animal(int power, Position position) : Organism(power, position)
{
	setSpecies("A");
}

Animal::Animal() : Organism()
{
	setSpecies("A");
}

void Animal::setLastPosition(Position position) 
{
    lastPosition = position;
}

void Animal::reproduce(World* world) {}

void Animal::move(World* world)
{
    vector<Position> possiblePositions = world->getVectorOfFreePositionsAround(this->getPosition());
    
    if (!possiblePositions.empty()) 
    {
        int randomIndex = rand() % possiblePositions.size();
        this->setPosition(possiblePositions[randomIndex]);
    }
}

void Animal::action(World* world) 
{
    move(world);
    //reproduce(world);
}


