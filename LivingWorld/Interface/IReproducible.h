#pragma once

class World;

class IReproducible {
public:
    virtual ~IReproducible() = default;
    virtual void reproduce(World* world) = 0;
};