#pragma once
#include "../Plant.h"
class Muchomor : public Plant {
public:
    Muchomor(int power, Position position);
    Muchomor();

    void action(World* world) override;
    void ifEaten(Organism* other, int power, World* world) override;
};