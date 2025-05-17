#pragma once

class World;

class IAction {
public:
    virtual ~IAction() = default;
    virtual void action(World* world) = 0;
};