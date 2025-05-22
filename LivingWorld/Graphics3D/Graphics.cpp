#include "Graphics.h"
#include <iostream>

// Vertex Shader
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ourColor = aColor;
}
)";

// Fragment Shader
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}
)";

// Konstruktor
WorldRenderer3D::WorldRenderer3D() {
    // Inicjalizacja mapowań kolorów i wysokości
    speciesColors = {
        {"S", glm::vec3(1.0f, 1.0f, 1.0f)},   // Owca - biała
        {"W", glm::vec3(0.3f, 0.3f, 0.3f)},   // Wilk - czarny
        {"G", glm::vec3(0.0f, 0.8f, 0.0f)},   // Trawa - zielona
        {"D", glm::vec3(1.0f, 1.0f, 0.0f)},   // Mlecz - żółty
        {"T", glm::vec3(1.0f, 0.0f, 0.0f)}    // Muchomor - czerwony
    };
    
    speciesHeights = {
        {"S", 0.5f},  // Owca
        {"W", 0.7f},  // Wilk
        {"G", 0.2f},  // Trawa
        {"D", 0.3f},  // Mlecz
        {"T", 0.4f}   // Muchomor
    };
    
    setupShaders();
    setupBuffers();
}

// Destruktor
WorldRenderer3D::~WorldRenderer3D() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

vector<float> WorldRenderer3D::createCubeMesh(float r, float g, float b) {
    // Standardowy sześcian z kolorami
    float vertices[] = {
        // pozycje            // kolory
        -0.5f, -0.5f, -0.5f,  r, g, b,
         0.5f, -0.5f, -0.5f,  r, g, b,
         0.5f,  0.5f, -0.5f,  r, g, b,
         0.5f,  0.5f, -0.5f,  r, g, b,
        -0.5f,  0.5f, -0.5f,  r, g, b,
        -0.5f, -0.5f, -0.5f,  r, g, b,

        -0.5f, -0.5f,  0.5f,  r, g, b,
         0.5f, -0.5f,  0.5f,  r, g, b,
         0.5f,  0.5f,  0.5f,  r, g, b,
         0.5f,  0.5f,  0.5f,  r, g, b,
        -0.5f,  0.5f,  0.5f,  r, g, b,
        -0.5f, -0.5f,  0.5f,  r, g, b,

        -0.5f,  0.5f,  0.5f,  r, g, b,
        -0.5f,  0.5f, -0.5f,  r, g, b,
        -0.5f, -0.5f, -0.5f,  r, g, b,
        -0.5f, -0.5f, -0.5f,  r, g, b,
        -0.5f, -0.5f,  0.5f,  r, g, b,
        -0.5f,  0.5f,  0.5f,  r, g, b,

         0.5f,  0.5f,  0.5f,  r, g, b,
         0.5f,  0.5f, -0.5f,  r, g, b,
         0.5f, -0.5f, -0.5f,  r, g, b,
         0.5f, -0.5f, -0.5f,  r, g, b,
         0.5f, -0.5f,  0.5f,  r, g, b,
         0.5f,  0.5f,  0.5f,  r, g, b,

        -0.5f, -0.5f, -0.5f,  r, g, b,
         0.5f, -0.5f, -0.5f,  r, g, b,
         0.5f, -0.5f,  0.5f,  r, g, b,
         0.5f, -0.5f,  0.5f,  r, g, b,
        -0.5f, -0.5f,  0.5f,  r, g, b,
        -0.5f, -0.5f, -0.5f,  r, g, b,

        -0.5f,  0.5f, -0.5f,  r, g, b,
         0.5f,  0.5f, -0.5f,  r, g, b,
         0.5f,  0.5f,  0.5f,  r, g, b,
         0.5f,  0.5f,  0.5f,  r, g, b,
        -0.5f,  0.5f,  0.5f,  r, g, b,
        -0.5f,  0.5f, -0.5f,  r, g, b
    };
    
    return vector<float>(vertices, vertices + sizeof(vertices) / sizeof(float));
}

void WorldRenderer3D::setupShaders() {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Inicjalizacja buforów OpenGL
void WorldRenderer3D::setupBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    // Tymczasowe dane dla bufora - będą aktualizowane przy renderowaniu
    vector<float> tempData = createCubeMesh(1.0f, 1.0f, 1.0f);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, tempData.size() * sizeof(float), tempData.data(), GL_DYNAMIC_DRAW);
    
    // Atrybut pozycji
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Atrybut koloru
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void WorldRenderer3D::renderWorld(const vector<Organism*>& organisms, 
                                 const glm::mat4& view, 
                                 const glm::mat4& projection,
                                 int worldSizeX, int worldSizeY) {
    glUseProgram(shaderProgram);
    
    // Ustawienie macierzy widoku i projekcji
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    // Renderowanie podłoża (szachownica)
    for (int x = 0; x < worldSizeX; x++) {
        for (int y = 0; y < worldSizeY; y++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(x, -0.5f, y));  // Podłoże na y = -0.5
            model = glm::scale(model, glm::vec3(1.0f, 0.1f, 1.0f)); // Płaskie
            
            // Wzór szachownicy?
            //float g = (x + y) % 2 == 0 ? 0.8f : 0.6f;
            
            unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            
            // Aktualizacja danych bufora dla podłoża
            vector<float> groundVertices = createCubeMesh(0.3f, 0.6f, 0.3f);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, groundVertices.size() * sizeof(float), groundVertices.data(), GL_DYNAMIC_DRAW);
            
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36); // 36 wierzchołków dla sześcianu
        }
    }
    
    for (auto* organism : organisms) {
        Position pos = organism->getPosition();
        string species = organism->getSpecies();
        
        // Domyślne wartości dla nieznanych gatunków
        glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f);
        float height = 0.5f;
        
        // Pobieranie koloru i wysokości dla gatunku
        if (speciesColors.find(species) != speciesColors.end()) {
            color = speciesColors[species];
        }
        
        if (speciesHeights.find(species) != speciesHeights.end()) {
            height = speciesHeights[species];
        }
        
        // Model matrix dla organizmu
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(pos.getX(), height/2.0f, pos.getY())); // y jest wysokością, z jest y z 2D
        model = glm::scale(model, glm::vec3(0.8f, height, 0.8f)); // Skalowanie do właściwej wysokości
        
        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        
        // Aktualizacja danych bufora dla organizmu
        vector<float> orgVertices = createCubeMesh(color.r, color.g, color.b);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, orgVertices.size() * sizeof(float), orgVertices.data(), GL_DYNAMIC_DRAW);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp, bool& nextTurn) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    float cameraSpeed = 0.1f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += cameraUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPos -= cameraUp * cameraSpeed;
        
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        nextTurn = true;
    else
        nextTurn = false;
}

void renderWorld3D(World* world) {
    // Inicjalizacja GLFW
    if (!glfwInit()) {
        cerr << "Błąd inicjalizacji GLFW" << endl;
        return;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Tworzenie okna
    GLFWwindow* window = glfwCreateWindow(1024, 768, "LivingWorld 3D", NULL, NULL);
    if (window == NULL) {
        cerr << "Błąd tworzenia okna GLFW" << endl;
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Inicjalizacja GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Błąd inicjalizacji GLAD" << endl;
        return;
    }
    
    // Tworzenie renderera 3D
    WorldRenderer3D renderer;
    
    glm::vec3 cameraPos = glm::vec3(world->getWorldX() / 2.0f, 8.0f, world->getWorldY() + 5.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, -0.5f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    
    // Zmienne do kontroli tury
    bool nextTurn = false;
    bool keyReleased = true;
    
    while (!glfwWindowShouldClose(window)) {
        processInput(window, cameraPos, cameraFront, cameraUp, nextTurn);
        
        if (nextTurn && keyReleased) {
            world->makeTurn();
            
            int sheepCount = 0;
            int wolfCount = 0;
            int grassCount = 0;
            int mleczCount = 0;
            int muchomorCount = 0;
            
            for (auto org : world->getOrganisms()) {
                string species = org->getSpecies();
                if (species == "S") sheepCount++;
                else if (species == "W") wolfCount++;
                else if (species == "G") grassCount++;
                else if (species == "D") mleczCount++;
                else if (species == "T") muchomorCount++;

                cout << org->toString() << endl;
            }
            
            cout << "\n--- Tura " << world->getTurn() << " ---\n";
            cout << "Populacja organizmów:\n";
            cout << "Owce: " << sheepCount << endl;
            cout << "Wilki: " << wolfCount << endl;
            cout << "Trawy: " << grassCount << endl;
            cout << "Mlecze: " << mleczCount << endl;
            cout << "Muchomory: " << muchomorCount << endl;
            
            keyReleased = false;
        }
        
        if (!nextTurn) {
            keyReleased = true;
        }
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Ustawienie macierzy widoku i projekcji
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        
        // Renderowanie świata
        renderer.renderWorld(world->getOrganisms(), view, projection, world->getWorldX(), world->getWorldY());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
}