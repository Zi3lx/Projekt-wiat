#pragma once

class Organism;
class World;

class IEatable {
public:
    virtual ~IEatable() = default;
    virtual void ifEaten(Organism* other, int power, World* world) = 0;
};