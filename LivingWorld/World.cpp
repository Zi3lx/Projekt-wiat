#include "World.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include "OrganismFactory.h"

using namespace std;

string World::getOrganismFromPosition(int x, int y)
{	
	for (Organism* org : organisms)
		if (org->getPosition().getX() == x && org->getPosition().getY() == y)
			return org->getSpecies();
	return "";
}

bool World::isPositionOnWorld(int x, int y)
{
	return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position) {
	return this->getOrganismFromPosition(position.getX(), position.getY()).empty();
}

vector<Position> World::getVectorOfFreePositionsAround(Position position)
{	
	int pos_x = position.getX(), pos_y = position.getY();
	vector<Position> result;
	for(int x = -1; x < 2; ++x)
		for (int y = -1; y < 2; ++y)
			if ((x != 0 || y != 0) && 
				isPositionOnWorld(pos_x + x, pos_y + y)) {
				result.push_back(Position(pos_x + x, pos_y + y));
			}
	auto iter = remove_if(result.begin(), result.end(),
		[this](Position pos) {return !isPositionFree(pos); });
	result.erase(iter, result.end());

	return result;
}

Organism* World::getOrganismPointerFromPosition(int x, int y)
{
    for (Organism* org : organisms)
        if (org->getPosition().getX() == x && org->getPosition().getY() == y)
            return org;
    return nullptr;
}

Position World::getRandomFreePosition() {
	int x = rand() % worldX;
	int y = rand() % worldY;
	while (!isPositionFree(Position(x, y))) {
		x = rand() % worldX;
		y = rand() % worldY;
	}
	return Position(x, y);
}

World::World(int worldX, int worldY)
{
	setWorldX(worldX);
	setWorldY(worldY);
}

World::~World()
{
   vector<Organism*> organismsToDelete = organisms;
    
    organisms.clear();

    for (Organism* org : organismsToDelete) {
        delete org;
    }
}

int World::getWorldX()
{
	return this->worldX;
}

void World::setWorldX(int worldX)
{
	this->worldX = worldX;
}

int World::getWorldY()
{
	return this->worldY;
}

void World::setWorldY(int worldY)
{
	this->worldY = worldY;
}

int World::getTurn()
{
	return this->turn;
}

void World::addOrganism(Organism* organism)
{
	this->organisms.push_back(organism);
}

void World::removeOrganism(Organism* organism)
{
    if (organism == nullptr) return;
    
    cout << "Oznaczanie organizmu do usunięcia: " << organism->getSpecies() << " na pozycji " << organism->getPosition().toString() << endl;
    
    if (find(organismsToRemove.begin(), organismsToRemove.end(), organism) == organismsToRemove.end()) {
        organismsToRemove.push_back(organism);
    }
}

void World::makeTurn()
{
	sort(organisms.begin(), organisms.end(), 
        [](Organism* a, Organism* b) {
            return a->getInitiative() > b->getInitiative();
        });

    for (Organism* org : organisms) {
        org->decreaseLiveLength();
        if (org->getLiveLength() == 0) {
            removeOrganism(org);
        }
    }
    
   vector<Organism*> organismsToProcess = organisms; // Kopia, aby uniknąć problemów z iteracją
    for (Organism* org : organismsToProcess) {
        if (find(organismsToRemove.begin(), organismsToRemove.end(), org) == organismsToRemove.end()) {
            org->action(this);
        }
    }
    
    // Teraz faktycznie usuń organizmy oznaczone do usunięcia
    for (Organism* org : organismsToRemove) {
        auto it = find(organisms.begin(), organisms.end(), org);
        if (it != organisms.end()) {
            organisms.erase(it);
            delete org;
            cout << "Organizm usunięty z pamięci" << endl;
        }
    }
    
    organismsToRemove.clear();
    
    turn++;
}

vector<Organism*> World::getOrganisms()
{
	return this->organisms;
}

void World::writeWorld(string fileName)
{
	ofstream file(fileName);
	if (!file) {
		cerr << "Nie można otworzyć pliku do zapisu: " << fileName << endl;
		return;
	}
	
	file << worldX << " " << worldY << " " << turn << endl;
	
	file << organisms.size() << endl;
	
	for (Organism* org : organisms) {
		org->serialize(file);
	}
	
	file.close();
	cout << "Świat został zapisany do pliku: " << fileName << endl;
}

void World::readWorld(string fileName)
{
	ifstream file(fileName);
   	if (!file) {
    	cerr << "Nie można otworzyć pliku do odczytu: " << fileName << endl;
       	return;
	}

	for (Organism* org : organisms) {
		delete org;
	}
	organisms.clear();
	
	file >> worldX >> worldY >> turn;

	int organismCount;
	file >> organismCount;
	
	for (size_t i = 0; i < organismCount; ++i) {
		string type;
		file >> type;
		
		Organism* newOrganism = OrganismFactory::createOrganism(type);
		
		if (newOrganism) {
			newOrganism->deserialize(file);
			organisms.push_back(newOrganism);
		} else {
			cerr << "Nieznany typ organizmu: " << type << endl;
			string line;
			getline(file, line);
		}
	}
	
	file.close();
	cout << "Świat został wczytany z pliku: " << fileName << endl;
}

string World::toString()
{
	string result = "\nturn: " + to_string(getTurn()) + "\n";
	string spec;

	for (int wY = 0; wY < getWorldY(); ++wY) {
		for (int wX = 0; wX < getWorldX(); ++wX) {
			spec = getOrganismFromPosition(wX, wY);
			if (spec != "")
				result += spec;
			else
				result += separator;
		};
		result += "\n";
	}
	return result;
}

