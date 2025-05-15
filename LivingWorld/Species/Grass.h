#pragma once
#include "../Plant.h"

class Grass : public Plant {
public:
    Grass(int power, Position position);
    Grass();

    void action(World* world) override;
};