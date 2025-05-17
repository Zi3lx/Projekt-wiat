// IMeatEatable.h
#pragma once

class Organism;
class World;

class IMeatEatable {
public:
    virtual ~IMeatEatable() = default;
    virtual void ifMeatEaten(Organism* other, int power, World* world) = 0;
};