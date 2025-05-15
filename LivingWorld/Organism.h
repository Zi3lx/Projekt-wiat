#pragma once
#include <string>
#include <vector>
#include <utility>
#include "Position.h"

using namespace std;

class World;

class Organism
{
private:
	int power;
	Position position;
	string species;
	int initiative;
	int liveLength;
	int powerToReproduce;
	vector<pair<int,int>> ancestors;

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
	void decreaseLiveLength();

	string toString();

	virtual void move(int dx, int dy);
	virtual void action(World* world);
};