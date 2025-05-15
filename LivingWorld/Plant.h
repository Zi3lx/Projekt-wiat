#pragma once
#include "Organism.h"
#include "IEatable.h"

class Plant : public Organism, public IEatable
{
	public:
		Plant(int power, Position position);
		Plant();

		void move(int dx, int dy);
		void action(World* world) override;
		void ifEaten(Organism* other, int power, World* world) override;
};

