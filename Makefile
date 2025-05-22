CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17 -DGL_SILENCE_DEPRECATION

# Katalogi
SRC_DIR = LivingWorld
INTERFACE_DIR = $(SRC_DIR)/Interface
SPECIES_DIR = $(SRC_DIR)/Species
GRAPHICS_DIR = $(SRC_DIR)/Graphics3D
OBJ_DIR = build
BIN_DIR = bin
EXTERNAL_DIR = $(SRC_DIR)/external

# Ścieżki do bibliotek
INCLUDES = -I$(SRC_DIR) -I$(INTERFACE_DIR) -I$(EXTERNAL_DIR)/include
LIBS = -L$(EXTERNAL_DIR)/lib -lglfw3
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

# Docelowy plik wykonywalny
TARGET = $(BIN_DIR)/LivingWorld

# Identyfikacja plików źródłowych
MAIN_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
SPECIES_SRCS = $(wildcard $(SPECIES_DIR)/*.cpp)
GRAPHICS_SRCS = $(wildcard $(GRAPHICS_DIR)/*.cpp)
GLAD_SRC = $(EXTERNAL_DIR)/src/glad.c
ALL_SRCS = $(MAIN_SRCS) $(SPECIES_SRCS) $(GRAPHICS_SRCS) $(GLAD_SRC)

# Przekształcenie nazw plików źródłowych na pliki obiektowe
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRCS))
SPECIES_OBJS = $(patsubst $(SPECIES_DIR)/%.cpp,$(OBJ_DIR)/Species_%.o,$(SPECIES_SRCS))
GRAPHICS_OBJS = $(patsubst $(GRAPHICS_DIR)/%.cpp,$(OBJ_DIR)/Graphics_%.o,$(GRAPHICS_SRCS))
GLAD_OBJ = $(OBJ_DIR)/glad.o
ALL_OBJS = $(MAIN_OBJS) $(SPECIES_OBJS) $(GRAPHICS_OBJS) $(GLAD_OBJ)

# Domyślna reguła
all: directories $(TARGET)

# Wypisanie zmiennych (do debugowania)
debug:
	@echo "MAIN_SRCS: $(MAIN_SRCS)"
	@echo "SPECIES_SRCS: $(SPECIES_SRCS)"
	@echo "GRAPHICS_SRCS: $(GRAPHICS_SRCS)"
	@echo "MAIN_OBJS: $(MAIN_OBJS)"
	@echo "SPECIES_OBJS: $(SPECIES_OBJS)"
	@echo "GRAPHICS_OBJS: $(GRAPHICS_OBJS)"

# Tworzenie katalogów
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Tworzenie pliku wykonywalnego
$(TARGET): $(ALL_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS) $(FRAMEWORKS)

# Reguła kompilacji plików z głównego katalogu
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Reguła kompilacji plików z podkatalogu Species
$(OBJ_DIR)/Species_%.o: $(SPECIES_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Reguła kompilacji plików z podkatalogu Graphics3D
$(OBJ_DIR)/Graphics_%.o: $(GRAPHICS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Kompilacja GLAD
$(GLAD_OBJ): $(EXTERNAL_DIR)/src/glad.c
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Czyszczenie
clean:
	rm -rf $(OBJ_DIR)/* $(TARGET)

# Pełne czyszczenie (włącznie z katalogami)
distclean: clean
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Ponowne budowanie projektu
rebuild: clean all

.PHONY: all clean distclean rebuild directories debug