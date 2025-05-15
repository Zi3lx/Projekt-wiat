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

void Animal::action(World* world)
{
    // Podstawowe zachowanie zwierzęcia - losowy ruch
    vector<Position> possiblePositions = world->getVectorOfFreePositionsAround(this->getPosition());
    
    if (!possiblePositions.empty()) {
        int randomIndex = rand() % possiblePositions.size();
        this->setPosition(possiblePositions[randomIndex]);
    }
}

