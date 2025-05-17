#pragma once

class World;

class IMovable {
public:
    virtual ~IMovable() = default;
    virtual void move(World* world) = 0;
};