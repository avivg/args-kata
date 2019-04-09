CPPFLAGS = -Wall -g -pedantic

ARGS_HDRS_DIR = argslib/include
ARGS_SRC_DIR = argslib/src
ARGS_BUILD_DIR = argslib/build

ARGS_HDRS = $(shell find $(ARGS_HDRS_DIR) -iname "*.hpp")
ARGS_SRCS = $(shell find $(ARGS_SRC_DIR) -iname "*.cpp")

ARGS_OBJS = $(subst $(ARGS_SRC_DIR),$(ARGS_BUILD_DIR),$(ARGS_SRCS:.cpp=.o))

ARGS_INCLUDE = -I$(ARGS_HDRS_DIR)

TEST_BUILD_DIR = test/build
TEST_SRC_DIR = test/src

TEST_EXE = $(TEST_BUILD_DIR)/test_args
TEST_SRCS = $(shell find $(TEST_SRC_DIR) -iname "*.cpp")
TEST_OBJS = $(subst $(TEST_SRC_DIR),$(TEST_BUILD_DIR),$(TEST_SRCS:.cpp=.o))

TEST_LD_LIBS = -lCppUTest -lCppUTestExt


.PHONY: all run_tests clean

all: run_tests

run_tests: $(TEST_EXE)
	$(TEST_EXE)

$(TEST_EXE): $(TEST_OBJS) $(ARGS_OBJS) $(ARGS_HDRS)
	@mkdir -p $(@D)
	$(CXX)  -o $@  $(TEST_OBJS)  $(ARGS_OBJS)  $(CPPFLAGS) $(TEST_LD_LIBS)

$(TEST_BUILD_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp $(ARGS_HDRS)
	@echo $@
	@mkdir -p $(dir $@)
	$(CXX)  -o $@  -c $<  $(CPPFLAGS)  $(ARGS_INCLUDE)  

$(ARGS_BUILD_DIR)/%.o: $(ARGS_SRC_DIR)/%.cpp $(ARGS_HDRS)
	@echo $@
	@mkdir -p $(dir $@)
	$(CXX)  -o $@  -c $<  $(CPPFLAGS)  $(ARGS_INCLUDE)  


clean:
	rm -rf $(TEST_BUILD_DIR)
	rm -rf $(ARGS_BUILD_DIR)