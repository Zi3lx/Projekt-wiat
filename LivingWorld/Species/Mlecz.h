#pragma once
#include "../Plant.h"

class Mlecz : public Plant {
public:
    Mlecz(int power, Position position);
    Mlecz();

    void reproduce(World* world) override;
    
    void additionalSerialize(ostream& os) override {};
    void additionalDeserialize(istream& is) override;
};