#pragma once
#include "../Plant.h"

class Grass : public Plant {
public:
    Grass(int power, Position position);
    Grass();

    void reproduce(World* world) override;
    
    void additionalSerialize(ostream& os) override {};
    void additionalDeserialize(istream& is) override;
};