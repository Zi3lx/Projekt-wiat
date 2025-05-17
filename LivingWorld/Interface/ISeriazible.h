#pragma once

class ISeriazible
{
public:
    virtual void serialize(ostream& os) = 0;
    virtual void deserialize(istream& is) = 0;
};