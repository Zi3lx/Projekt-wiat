#pragma once
#include "../Animal.h"

class Wolf : public Animal {
public:
    Wolf(int power, Position position);
    Wolf();

    void action(World* world) override;
    void reproduce(World* world) override;
    
    void additionalSerialize(ostream& os) override {};
    void additionalDeserialize(istream& is) override;
};