
CC = g++


LD_LIBS = -lCppUTest


TEST_BUILD_DIR = test/build
TEST_SRC_DIR = test/src
TEST_EXE = $(TEST_BUILD_DIR)/test_args
TEST_SRCS = $(TEST_SRC_DIR)/*.cpp


.PHONY: run_tests clean

run_tests: $(TEST_EXE)
	$(TEST_EXE)

$(TEST_EXE): $(ARGS_OBJS) $(ARGS_HDRS) $(TEST_SRCS)
	@mkdir -p $(@D)
	$(CC)  $(TEST_SRCS)  $(LD_LIBS)  -o $@

clean:
	@rm -rf $(TEST_BUILD_DIR)