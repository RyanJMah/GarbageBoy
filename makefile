TARGET = main
BUILD_DIR = build
DEBUG = true

ifeq ($(DEBUG), true)
	OPT = -Og
else
	OPT = -O2
endif

CC = g++ -std=c++11
CP = objcopy
SZ = size

CPP_SOURCES = $(wildcard src/*.cpp)
CPP_INCLUDES = -I ./inc
CPP_FLAGS = $(CPP_INCLUDES) $(OPT) -Wall -MMD -MP -MF"$(@:%.o=%.d)"

ifeq ($(DEBUG), true)
	CPP_FLAGS += -ggdb
endif

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

all: $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR) 
	$(CC) -c $(CPP_FLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@
	
$(BUILD_DIR):
	mkdir $@

clean:
	rm -rf $(BUILD_DIR)
