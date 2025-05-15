#pragma once
#include "../Plant.h"

class Mlecz : public Plant {
public:
    Mlecz(int power, Position position);
    Mlecz();

    void action(World* world) override;
};