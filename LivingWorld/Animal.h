#pragma once
#include "Organism.h"

using namespace std;

class Animal : public Organism
{
	private:
		Position lastPosition;
	public:
		Animal(int power, Position position);
		Animal();

		void setLastPosition(Position position);
		void action(World* world) override;
};

