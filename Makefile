CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = bin/LivingWorld

# Katalogi
SRC_DIR = LivingWorld
SPECIES_DIR = $(SRC_DIR)/Species
OBJ_DIR = build
BIN_DIR = bin

# Źródła
MAIN_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
SPECIES_SRCS = $(wildcard $(SPECIES_DIR)/*.cpp)
ALL_SRCS = $(MAIN_SRCS) $(SPECIES_SRCS)

# Obiekty
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRCS))
SPECIES_OBJS = $(patsubst $(SPECIES_DIR)/%.cpp,$(OBJ_DIR)/Species_%.o,$(SPECIES_SRCS))
ALL_OBJS = $(MAIN_OBJS) $(SPECIES_OBJS)

# Domyślna reguła
all: directories $(TARGET)

# Wypisanie zmiennych (do debugowania)
debug:
	@echo "MAIN_SRCS: $(MAIN_SRCS)"
	@echo "SPECIES_SRCS: $(SPECIES_SRCS)"
	@echo "MAIN_OBJS: $(MAIN_OBJS)"
	@echo "SPECIES_OBJS: $(SPECIES_OBJS)"

# Tworzenie katalogów
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Tworzenie pliku wykonywalnego
$(TARGET): $(ALL_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Reguła kompilacji plików głównego katalogu
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Reguła kompilacji plików z podkatalogu Species
$(OBJ_DIR)/Species_%.o: $(SPECIES_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Czyszczenie
clean:
	rm -rf $(OBJ_DIR)/* $(TARGET)

.PHONY: all clean directories debug