TARGET = garbageboy
BUILD_DIR = build
DEBUG = 1

OPT = -O0

CC = g++ -std=c++11
CP = objcopy
SZ = size

CPP_SOURCES = $(wildcard src/*.cpp)
CPP_INCLUDES = -I ./inc
CPP_FLAGS = $(CPP_INCLUDES) $(OPT) -Wall -MMD -MP -MF"$(@:%.o=%.d)"

LD_FLAGS = -l boost_program_options

ifeq ($(DEBUG), 1)
	CPP_FLAGS += -ggdb
endif

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

all: $(BUILD_DIR)/$(TARGET)

.PHONY: run
run: all
	@echo "running $(BUILD_DIR)/$(TARGET)..."
	@echo ""
	@./build/$(TARGET)

.PHONY: test
test: all
	@python3 ./run_tests.py

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR) 
	$(CC) -c $(CPP_FLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@echo ""
	$(CC) $(OBJECTS) $(LD_FLAGS) -o $@
	@echo ""
	@$(SZ) $@
	@echo ""

$(BUILD_DIR):
	mkdir $@
	@echo ""

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
