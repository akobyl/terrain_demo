# Variables
BUILD_DIR = build
CMAKE = cmake
NINJA = ninja

# Default target
all: build

# Build the project
build:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) -G Ninja .. && $(NINJA)

# Run tests
test: build
	@cd $(BUILD_DIR) && $(NINJA) test

# Run the application
run: build
	@cd $(BUILD_DIR) && ./TerrainDemo

clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all build test clean
