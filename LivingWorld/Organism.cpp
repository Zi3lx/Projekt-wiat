#include "Organism.h"
#include "World.h"
#include <iostream>

Organism::Organism(const Organism& other)
    : power(other.power), 
      position(other.position), 
      species(other.species),
      initiative(other.initiative),
      liveLength(other.liveLength),
      powerToReproduce(other.powerToReproduce),
      ancestors(other.ancestors)
{}

Organism::Organism(Organism&& other) noexcept
    : power(other.power),
      position(std::move(other.position)),
      species(std::move(other.species)),
      initiative(other.initiative),
      liveLength(other.liveLength),
      powerToReproduce(other.powerToReproduce),
      ancestors(std::move(other.ancestors))
{
    other.power = 0;
    other.initiative = 0;
    other.liveLength = 0;
    other.powerToReproduce = 0;
}

Organism& Organism::operator=(const Organism& other)
{
    if (this != &other)
    {
        power = other.power;
        position = other.position;
        species = other.species;
        initiative = other.initiative;
        liveLength = other.liveLength;
        powerToReproduce = other.powerToReproduce;
        ancestors = other.ancestors;
    }
    return *this;
}

Organism& Organism::operator=(Organism&& other) noexcept
{
    if (this != &other)
    {
        power = other.power;
        position = std::move(other.position);
        species = std::move(other.species);
        initiative = other.initiative;
        liveLength = other.liveLength;
        powerToReproduce = other.powerToReproduce;
        ancestors = std::move(other.ancestors);
        
        other.power = 0;
        other.initiative = 0;
        other.liveLength = 0;
        other.powerToReproduce = 0;
    }
    return *this;
}

Organism::~Organism() {}

void Organism::action(World* world){}

Organism::Organism(int power, Position position)
{
	setPower(power);
	setPosition(position);
	setSpecies("O");
}

int Organism::getPower()
{
	return this->power;
}

void Organism::setPower(int power)
{
	this->power = power;
}

Position Organism::getPosition()
{
	return this->position;
}

void Organism::setPosition(Position position)
{
	this->position = position;
}

string Organism::toString()
{
	string result = "{ species: " + getSpecies() +
		", power: " + to_string(getPower()) +
		", position: " + getPosition().toString() + 
		", initiative: " + to_string(getInitiative()) +
		", liveLength: " + to_string(getLiveLength()) +
		", powerToReproduce: " + to_string(getPowerToReproduce()) +
		", ancestors: [";

	for (auto a : ancestors)
		result += "(" + to_string(a.first) + "," + to_string(a.second) + "), ";
	result += "]}";

	return result;
}

string Organism::getSpecies()
{
	return this->species;
}

void Organism::setSpecies(string spec)
{
	this->species = spec;
}

// Zad 1
void Organism::addAncestor(int birthTurn, int deathTurn) 
{
    ancestors.push_back({birthTurn, deathTurn});
}

vector<pair<int, int>> Organism::getAncestors() 
{
    return ancestors;
}
//---------------------------------------------------------
// Zad 2
int Organism::getInitiative()
{
	return this->initiative; 
}
void Organism::setInitiative(int initiative) 
{ 
	this->initiative = initiative; 
}

int Organism::getLiveLength() 
{ 
	return this->liveLength; 
}
void Organism::setLiveLength(int liveLength) 
{ 
	this->liveLength = liveLength; 
}

int Organism::getPowerToReproduce() 
{
	return this->powerToReproduce; 
}

void Organism::setPowerToReproduce(int powerToReproduce) 
{ 
	this->powerToReproduce = powerToReproduce; 
}

void Organism::decreaseLiveLength()
{
	liveLength--;
}

//---------------------------------------------------------