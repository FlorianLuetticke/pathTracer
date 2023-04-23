TARGET_EXEC ?= sceneTest

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src ../../src/math ../../src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := ../../src  /usr/local/include/
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -O3  -std=c++17
LDFLAGS +=   -lgtest_main  -lgtest -lfmt -lstdc++ -lm

$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	@$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	@$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
	


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) $(TARGET_EXEC)

-include $(DEPS)

MKDIR_P ?= mkdir -p