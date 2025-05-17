#pragma once
#include "Organism.h"
#include "Interface/IMovable.h"
#include "Interface/IReproducible.h"

using namespace std;

class World;

class Animal : public Organism, public IMovable, public IReproducible
{
	private:
		Position lastPosition;
	public:
		Animal(int power, Position position);
		Animal();

		void setLastPosition(Position position);
		void action(World* world) override;

		void move(World* world) override;
		void reproduce(World* world) override = 0;
};

