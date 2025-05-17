#pragma once
#include "../Plant.h"
class Muchomor : public Plant {
public:
    Muchomor(int power, Position position);
    Muchomor();

    void ifEaten(Organism* other, int power, World* world) override;
    void reproduce(World* world) override;
    
    void additionalSerialize(ostream& os) override {};
    void additionalDeserialize(istream& is) override;
};