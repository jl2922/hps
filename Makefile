# Default options.
CXX := g++
CXX_WARNING_OPTIONS := -Wall -Wextra
CXXFLAGS := -std=c++11 -O3 $(CXX_WARNING_OPTIONS)
LDLIBS := -pthread -lpthread
SRC_DIR := src
BUILD_DIR := build
TEST_EXE := test.out

# Load Makefile.config if exists.
LOCAL_MAKEFILE := local.mk
ifneq ($(wildcard $(LOCAL_MAKEFILE)),)
	include $(LOCAL_MAKEFILE)
endif

# Sources and intermediate objects.
TESTS := $(shell find $(SRC_DIR) -name "*_test.cc" -not -path "$(SRC_DIR)/benchmark/*")
HEADERS := $(shell find $(SRC_DIR) -name "*.h")
COMPILED_HEADERS := $(HEADERS:%.h=%.h.gch)
OBJS := $(SRCS:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TESTS:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)

# Test related.
GTEST_DIR := googletest/googletest
GMOCK_DIR := googletest/googlemock
GTEST_ALL_SRC := ${GTEST_DIR}/src/gtest-all.cc
GMOCK_ALL_SRC := ${GMOCK_DIR}/src/gmock-all.cc
TEST_MAIN_SRC := ${GMOCK_DIR}/src/gmock_main.cc
TEST_MAIN_OBJ := $(BUILD_DIR)/gtest_main.o
TEST_CXXFLAGS := $(CXXFLAGS) -isystem $(GTEST_DIR)/include -isystem $(GMOCK_DIR)/include -pthread
TEST_LIB := $(BUILD_DIR)/libgtest.a

.PHONY: all test benchmark test_all clean

.SUFFIXES:

all:
	$(MAKE) test

test: $(TEST_EXE)
	./$(TEST_EXE) --gtest_filter=-*LargeTest.*

benchmark:
	$(MAKE) -f benchmark.mk

test_all: $(TEST_EXE)
	./$(TEST_EXE)

clean:
	rm -rf $(BUILD_DIR)
	rm -f ./*.out

$(TEST_EXE): $(TEST_OBJS) $(OBJS) $(TEST_LIB)
	$(CXX) $(TEST_CXXFLAGS) $(TEST_OBJS) $(OBJS) $(TEST_MAIN_SRC) $(TEST_LIB) -o $(TEST_EXE) $(LDLIBS)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc $(COMPILED_HEADERS)
	mkdir -p $(@D) && $(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/gtest-all.o: $(GTEST_ALL_SRC)
	mkdir -p $(@D) && $(CXX) $(TEST_CXXFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) -c $(GTEST_ALL_SRC) -o $@

$(BUILD_DIR)/gmock-all.o: $(GMOCK_ALL_SRC)
	mkdir -p $(@D) && $(CXX) $(TEST_CXXFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) -c $(GMOCK_ALL_SRC) -o $@

$(TEST_LIB): $(BUILD_DIR)/gtest-all.o $(BUILD_DIR)/gmock-all.o
	$(AR) $(ARFLAGS) $@ $(BUILD_DIR)/gtest-all.o $(BUILD_DIR)/gmock-all.o

$(TEST_OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc $(COMPILED_HEADERS)
	mkdir -p $(@D) && $(CXX) $(TEST_CXXFLAGS) -c $< -o $@

$(COMPILED_HEADERS): %.h.gch: %.h
	$(CXX) $(TEST_CXXFLAGS) $<
