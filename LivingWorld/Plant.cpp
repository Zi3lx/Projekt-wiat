#include "Plant.h"
#include "World.h"
#include <iostream>

Plant::Plant(int power, Position position) : Organism(power, position)
{
	setSpecies("P");
}

Plant::Plant() : Organism()
{
	setSpecies("P");
}

void Plant::action(World* world)
{
	Organism::action(world);
}

void Plant::move(int dx, int dy)
{
	Organism::move(0, 0);
}

void Plant::ifEaten(Organism* other, int power, World* world)
{
	std::cout << "Roślina została zjedzona przez " << other->getSpecies() << std::endl;
	other->setPower(other->getPower() + power);
	world->removeOrganism(this);
}
