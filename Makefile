CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Katalogi
SRC_DIR = LivingWorld
INTERFACE_DIR = $(SRC_DIR)/Interface
SPECIES_DIR = $(SRC_DIR)/Species
OBJ_DIR = build
BIN_DIR = bin

# Docelowy plik wykonywalny
TARGET = $(BIN_DIR)/LivingWorld

# Identyfikacja plików źródłowych
MAIN_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
SPECIES_SRCS = $(wildcard $(SPECIES_DIR)/*.cpp)
ALL_SRCS = $(MAIN_SRCS) $(SPECIES_SRCS)

# Przekształcenie nazw plików źródłowych na pliki obiektowe
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

# Reguła kompilacji plików z głównego katalogu
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(INTERFACE_DIR) -c $< -o $@

# Reguła kompilacji plików z podkatalogu Species
$(OBJ_DIR)/Species_%.o: $(SPECIES_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(INTERFACE_DIR) -c $< -o $@

# Czyszczenie
clean:
	rm -rf $(OBJ_DIR)/* $(TARGET)

# Pełne czyszczenie (włącznie z katalogami)
distclean: clean
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Ponowne budowanie projektu
rebuild: clean all

.PHONY: all clean distclean rebuild directories debug