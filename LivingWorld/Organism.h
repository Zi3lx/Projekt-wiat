#pragma once
#include <string>
#include <vector>
#include <utility>
#include "Position.h"
#include "Interface/IAction.h"
#include "Interface/ISeriazible.h"

using namespace std;

class World;

class Organism : public IAction, public ISeriazible
{
private:
	int power;
	Position position;
	string species;
	int initiative;
	int liveLength;
	int powerToReproduce;
	vector<pair<int,int>> ancestors;

protected:
	virtual void additionalSerialize(ostream& os) = 0;
	virtual void additionalDeserialize(istream& is) = 0;

public:
	Organism(int power, Position position);
	Organism() : power(0), position(0, 0), species("O"), initiative(0), liveLength(0), powerToReproduce(0) {};

	// Zad 1
	Organism(const Organism& other);
	Organism(Organism&& other) noexcept;
	Organism& operator=(const Organism& other);
	Organism& operator=(Organism&& other) noexcept;
	virtual ~Organism();
	//---------------------------- 

	int getPower();
	void setPower(int power);
	Position getPosition();
	void setPosition(Position position);
	string getSpecies();
	void setSpecies(string spec);
	int getInitiative();
	void setInitiative(int initiative);
	int getLiveLength();
	void setLiveLength(int liveLength);
	int getPowerToReproduce();
	void setPowerToReproduce(int powerToReproduce);
	void addAncestor(int birthTurn, int deathTurn);
	vector<pair<int, int>> getAncestors();
	void setAncestors(vector<pair<int, int>> ancestors);
	void decreaseLiveLength();

	string toString();

	virtual void action(World* world) override = 0;

	virtual void serialize(ostream& os) override;
	virtual void deserialize(istream& is) override;
};