#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Position.h"
#include "Organism.h"
#include "Plant.h"
#include "Animal.h"
#include "World.h"
#include "Species/Sheep.h"
#include "Species/Grass.h"
#include "Species/Mlecz.h"
#include "Species/Muchomor.h"
#include "Species/Wolf.h"
#include "OrganismFactory.h"

using namespace std;

void test_owcy()
{
	cout << "\n=== TEST OWIEC ===\n";
    
    // Tworzymy nowy świat o większych wymiarach
    World* sheepWorld = new World(10, 10);
    
    // Dodajemy owce w różnych pozycjach
    Sheep* sheep1 = new Sheep(3, Position(2, 3));
    Sheep* sheep2 = new Sheep(4, Position(5, 5));
    Sheep* sheep3 = new Sheep(5, Position(7, 2));
    
    // Dodajemy rośliny jako "trawę"
    Plant* grass1 = new Grass(0, Position(3, 3));  // Obok sheep1
    Plant* grass2 = new Grass(0, Position(6, 7));  // Obok sheep2
    Plant* grass3 = new Grass(0, Position(6, 3));  // Obok sheep3
    Plant* grass4 = new Grass(0, Position(8, 8));  // Z dala od owiec
	Plant* grass5 = new Grass(0, Position(1, 1));
	Plant* grass6 = new Grass(0, Position(1, 9));
	Plant* grass7 = new Mlecz(0, Position(9, 1));
	Plant* grass8 = new Mlecz(0, Position(9, 9));
    
    // Dodajemy organizmy do świata
    sheepWorld->addOrganism(sheep1);
    sheepWorld->addOrganism(sheep2);
    sheepWorld->addOrganism(sheep3);
    sheepWorld->addOrganism(grass1);
    sheepWorld->addOrganism(grass2);
    sheepWorld->addOrganism(grass3);
    sheepWorld->addOrganism(grass4);
	sheepWorld->addOrganism(grass5);
	sheepWorld->addOrganism(grass6);
	sheepWorld->addOrganism(grass7);
	sheepWorld->addOrganism(grass8);
    
    // Wyświetlamy początkowy stan świata
    cout << "Stan początkowy świata:\n";
    cout << sheepWorld->toString() << endl;
    
    // Szczegółowe informacje o owcach
    cout << "Szczegóły owiec:\n";
    cout << "Owca 1: " << sheep1->toString() << endl;
    cout << "Owca 2: " << sheep2->toString() << endl;
    cout << "Owca 3: " << sheep3->toString() << endl;
    
    // Symulujemy kilka tur
    for (int i = 1; i <= 50; i++) {
        sheepWorld->makeTurn();
        cout << "\n--- Tura " << i << " ---\n";
        cout << sheepWorld->toString() << endl;
        
        // Zliczamy ilość każdego typu organizmu
        int sheepCount = 0;
        int plantCount = 0;
        for (auto org : sheepWorld->getOrganisms()) {
            if (org->getSpecies() == "S") sheepCount++;
            if (org->getSpecies() == "G") plantCount++;
        }
        
        cout << "Liczba owiec: " << sheepCount << endl;
        cout << "Liczba roślin: " << plantCount << endl;

		cout << "Szczegóły owiec:\n";
		for (auto org : sheepWorld->getOrganisms()) 
		{
            if (org->getSpecies() == "S")
			{
				cout << "Owca: " << org->toString() << endl;
			}
		}

		if (i % 3 == 0)
		{
			Plant* grass = new Grass(0, Position(rand() % sheepWorld->getWorldX(), rand() % sheepWorld->getWorldY()));
			sheepWorld->addOrganism(grass);
		}

		this_thread::sleep_for(chrono::seconds(1));
    }
    
    delete sheepWorld;	
}

void test_ecosystem()
{
    cout << "\n=== TEST EKOSYSTEMU ===\n";
    
    World* ecoWorld = new World(15, 15);
    
    for (int i = 0; i < 20; i++) {
        int x = rand() % ecoWorld->getWorldX();
        int y = rand() % ecoWorld->getWorldY();
        if (ecoWorld->isPositionFree(Position(x, y))) {
            ecoWorld->addOrganism(new Sheep(3 + rand() % 3, Position(x, y)));
        }
    }
    
    // Wilki
    for (int i = 0; i < 3; i++) {
        int x = rand() % ecoWorld->getWorldX();
        int y = rand() % ecoWorld->getWorldY();
        if (ecoWorld->isPositionFree(Position(x, y))) {
            ecoWorld->addOrganism(new Wolf(8 + rand() % 4, Position(x, y)));
        }
    }
    
    // Trawa
    for (int i = 0; i < 35; i++) {
        int x = rand() % ecoWorld->getWorldX();
        int y = rand() % ecoWorld->getWorldY();
        if (ecoWorld->isPositionFree(Position(x, y))) {
            ecoWorld->addOrganism(new Grass(0, Position(x, y)));
        }
    }
    
    // Mlecze
    for (int i = 0; i < 20; i++) {
        int x = rand() % ecoWorld->getWorldX();
        int y = rand() % ecoWorld->getWorldY();
        if (ecoWorld->isPositionFree(Position(x, y))) {
            ecoWorld->addOrganism(new Mlecz(0, Position(x, y)));
        }
    }
    
    // Muchomory
    for (int i = 0; i < 8; i++) {
        int x = rand() % ecoWorld->getWorldX();
        int y = rand() % ecoWorld->getWorldY();
        if (ecoWorld->isPositionFree(Position(x, y))) {
            ecoWorld->addOrganism(new Muchomor(0, Position(x, y)));
        }
    }
    
    cout << "Stan początkowy świata:\n";
    cout << ecoWorld->toString() << endl;

    for (int i = 1; i <= 50; i++) {
        int sheepCount = 0;
        int wolfCount = 0;
        int grassCount = 0;
        int mleczCount = 0;
        int muchomorCount = 0;

        ecoWorld->makeTurn();
        cout << "\n--- Tura " << i << " ---\n";
        cout << ecoWorld->toString() << endl;
        
        for (auto org : ecoWorld->getOrganisms()) {
            string species = org->getSpecies();
            //cout << org->toString() << endl;
            if (species == "S") sheepCount++;
            else if (species == "W") wolfCount++;
            else if (species == "G") grassCount++;
            else if (species == "D") mleczCount++;
            else if (species == "T") muchomorCount++;
        }
        
        cout << "Populacja organizmów:\n";
        cout << "Owce: " << sheepCount << endl;
        cout << "Wilki: " << wolfCount << endl;
        cout << "Trawy: " << grassCount << endl;
        cout << "Mlecze: " << mleczCount << endl;
        cout << "Muchomory: " << muchomorCount << endl;
        
        this_thread::sleep_for(chrono::seconds(1));
    }
    
    cout << "\n=== STATYSTYKI KOŃCOWE ===\n";

    int finalSheepCount = 0;
    int finalWolfCount = 0;
    int finalGrassCount = 0;
    int finalMleczCount = 0;
    int finalMuchomorCount = 0;
    
    for (auto org : ecoWorld->getOrganisms()) {
        string species = org->getSpecies();
        if (species == "S") finalSheepCount++;
        else if (species == "W") finalWolfCount++;
        else if (species == "G") finalGrassCount++;
        else if (species == "D") finalMleczCount++;
        else if (species == "T") finalMuchomorCount++;
    }
    
    cout << "Owce: " << finalSheepCount << endl;
    cout << "Wilki: " << finalWolfCount << endl;
    cout << "Trawy: " << finalGrassCount << endl;
    cout << "Mlecze: " << finalMleczCount << endl;
    cout << "Muchomory: " << finalMuchomorCount << endl;
    
    delete ecoWorld;
}

void test_serialization() {
    cout << "\n=== TEST SERIALIZACJI ===\n";
    
    World testWorld(10, 10);
    
    testWorld.addOrganism(new Sheep(10, Position(2, 3)));
    testWorld.addOrganism(new Wolf(8, Position(5, 5)));
    testWorld.addOrganism(new Grass(0, Position(7, 7)));
    
    cout << "Stan początkowy świata:\n";

    testWorld.makeTurn();
    cout << testWorld.toString() << endl;
    for (auto org : testWorld.getOrganisms()) {
        cout << org->toString() << endl;
    }

    testWorld.writeWorld("test_world.bin");
    
    for (int i = 0; i < 3; i++) {
        testWorld.makeTurn();
        cout << "\n--- Tura " << i + 1 << " ---\n";
        cout << testWorld.toString() << endl;
        
        //Wypisz oranizmy
        for (auto org : testWorld.getOrganisms()) {
            cout << org->toString() << endl;
        }

        this_thread::sleep_for(chrono::seconds(1));
    }
    
    testWorld.readWorld("test_world.bin");
    
    cout << "Stan świata po wczytaniu z pliku:\n";
    cout << testWorld.toString() << endl;

    for (auto org : testWorld.getOrganisms()) {
        cout << org->toString() << endl;
    }
}

int main()
{
    srand(time(NULL));
    OrganismFactory::initialize();
    test_serialization();
	//test_ecosystem();
	//test_owcy();
	return 0;
}
