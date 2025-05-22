#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>
#include <string>
#include "../World.h"
#include "../Organism.h"

class WorldRenderer3D {
private:
    unsigned int shaderProgram;
    unsigned int VAO, VBO;
    
    // Mapowanie gatunków na kolory i wysokości
    map<string, glm::vec3> speciesColors;
    map<string, float> speciesHeights;
    
    // Metody pomocnicze
    vector<float> createCubeMesh(float r, float g, float b);
    void setupShaders();
    void setupBuffers();

public:
    WorldRenderer3D();
    ~WorldRenderer3D();
    
    void renderWorld(const vector<Organism*>& organisms, 
                     const glm::mat4& view, 
                     const glm::mat4& projection,
                     int worldSizeX, int worldSizeY);
};

// Funkcja główna do uruchomienia wizualizacji 3D
void renderWorld3D(World* world);