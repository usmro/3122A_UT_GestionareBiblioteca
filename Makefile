CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I./src -pthread
TARGET   = biblioteca_app
SRC_DIR  = src
TEST_DIR = tests
BUILD_DIR = build

# -----------------------------------------------------------------------
# Build principal
# -----------------------------------------------------------------------
all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR)/main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -pthread
	@echo ""
	@echo ">>> Build reusit: ./$(TARGET)"

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilare rapida (un singur pas)
quick:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_DIR)/main.cpp -pthread
	@echo ">>> Quick build reusit: ./$(TARGET)"

# Rulare aplicatie
run: all
	./$(TARGET)

# -----------------------------------------------------------------------
# Teste unitare
# -----------------------------------------------------------------------
TEST_BINS = $(BUILD_DIR)/TestStoc \
            $(BUILD_DIR)/TestImprumuturi \
            $(BUILD_DIR)/TestPolimorfism

tests: $(BUILD_DIR) $(TEST_BINS)
	@echo ""
	@echo ">>> Rulare teste..."
	@echo ""
	@$(BUILD_DIR)/TestStoc        && echo "" || echo "[FAIL] TestStoc"
	@$(BUILD_DIR)/TestImprumuturi && echo "" || echo "[FAIL] TestImprumuturi"
	@$(BUILD_DIR)/TestPolimorfism && echo "" || echo "[FAIL] TestPolimorfism"
	@echo ">>> Toate testele rulate."

$(BUILD_DIR)/TestStoc: $(TEST_DIR)/TestStoc.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< -pthread

$(BUILD_DIR)/TestImprumuturi: $(TEST_DIR)/TestImprumuturi.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< -pthread

$(BUILD_DIR)/TestPolimorfism: $(TEST_DIR)/TestPolimorfism.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< -pthread

# Ruleaza un singur test
test-stoc:
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/TestStoc $(TEST_DIR)/TestStoc.cpp -pthread
	./$(BUILD_DIR)/TestStoc

test-imprumuturi:
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/TestImprumuturi $(TEST_DIR)/TestImprumuturi.cpp -pthread
	./$(BUILD_DIR)/TestImprumuturi

test-polimorfism:
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/TestPolimorfism $(TEST_DIR)/TestPolimorfism.cpp -pthread
	./$(BUILD_DIR)/TestPolimorfism

# -----------------------------------------------------------------------
# Utilitare
# -----------------------------------------------------------------------
clean:
	rm -rf $(BUILD_DIR) $(TARGET) biblioteca_log.txt
	@echo ">>> Curatat."

rebuild: clean all

check:
	$(CXX) $(CXXFLAGS) --syntax-only $(SRC_DIR)/main.cpp