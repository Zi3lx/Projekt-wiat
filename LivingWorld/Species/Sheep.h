#pragma once 
#include "../Animal.h"
#include "../Interface/IMeatEatable.h"

class Sheep : public Animal, public IMeatEatable
{
public:
    Sheep();
    Sheep(int power, Position position);
    
    void action(World* world) override;
    void ifMeatEaten(Organism* other, int power, World* world) override;
    void reproduce(World* world) override;
};