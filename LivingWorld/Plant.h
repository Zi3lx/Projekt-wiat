#pragma once

#include "Organism.h"
#include "Interface/IEatable.h"
#include "Interface/IReproducible.h"

using namespace std;

class Plant : public Organism, public IEatable, public IReproducible
{
	public:
		Plant(int power, Position position);
		Plant();
		virtual ~Plant() = default;

		void action(World* world) override;
		void ifEaten(Organism* other, int power, World* world) override;
		void reproduce(World* world) override;
};

