# Default options.
CXX := g++
CXX_WARNING_OPTIONS := -Wall -Wextra
CXXFLAGS := -std=c++11 -O3 $(CXX_WARNING_OPTIONS)
LDLIBS := -pthread -lboost_serialization -lprotobuf -lpthread
SRC_DIR := src
BUILD_DIR := build
TEST_EXE := test.out

# Libraries.
BOOST_DIR := $(TOOLS_DIR)/boost
PROTOBUF_DIR := $(TOOLS_DIR)/protobuf
CXXFLAGS := $(CXXFLAGS) -isystem $(BOOST_DIR)/include -isystem $(PROTOBUF_DIR)/include
LDLIBS := -L $(BOOST_DIR)/lib -L $(PROTOBUF_DIR)/lib $(LDLIBS)

# Load Makefile.config if exists.
LOCAL_MAKEFILE := local.mk
ifneq ($(wildcard $(LOCAL_MAKEFILE)),)
	include $(LOCAL_MAKEFILE)
endif

# Sources and intermediate objects.
PROTO_SRC := $(SRC_DIR)/benchmarks/data.proto
PROTO_COMPILED := $(SRC_DIR)/benchmarks/data.pb.h $(SRC_DIR)/benchmarks/data.pb.cc
SRCS := $(shell find $(SRC_DIR) ! -name "*_test.cc" -name "*.cc")
TESTS := $(shell find $(SRC_DIR) -name "*_test.cc")
HEADERS := $(shell find $(SRC_DIR) -name "*.h")
OBJS := $(SRCS:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TESTS:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)

# Test related.
GTEST_DIR := gtest/googletest
GMOCK_DIR := gtest/googlemock
GTEST_ALL_SRC := ${GTEST_DIR}/src/gtest-all.cc
GMOCK_ALL_SRC := ${GMOCK_DIR}/src/gmock-all.cc
TEST_MAIN_SRC := ${GMOCK_DIR}/src/gmock_main.cc
TEST_MAIN_OBJ := $(BUILD_DIR)/gtest_main.o
TEST_CXXFLAGS := $(CXXFLAGS) -isystem $(GTEST_DIR)/include -isystem $(GMOCK_DIR)/include -pthread
TEST_LIB := $(BUILD_DIR)/libgtest.a

.PHONY: all test benchmark all_tests test_exe proto clean

all:
	$(MAKE) test

test: test_exe
	./$(TEST_EXE) --gtest_filter=-*LargeTest.*

benchmarks: test_exe
	./$(TEST_EXE) --gtest_filter=*BenchmarkLargeTest.*

all_tests: test_exe
	./$(TEST_EXE)

test_exe: proto
	$(MAKE) $(TEST_EXE)

proto:
	$(MAKE) $(PROTO_COMPILED)

clean:
	rm -rf $(BUILD_DIR)
	rm -f ./$(TEST_EXE)

$(TEST_EXE): $(TEST_OBJS) $(OBJS) $(TEST_MAIN_OBJ) $(TEST_LIB)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) $(OBJS) $(TEST_MAIN_OBJ) $(TEST_LIB) -o $(TEST_EXE) $(LDLIBS) -lpthread

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc $(HEADERS)
	mkdir -p $(@D) && $(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/gtest-all.o: $(GTEST_ALL_SRC)
	mkdir -p $(@D) && $(CXX) $(TEST_CXXFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) -c $(GTEST_ALL_SRC) -o $@

$(BUILD_DIR)/gmock-all.o: $(GMOCK_ALL_SRC)
	mkdir -p $(@D) && $(CXX) $(TEST_CXXFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) -c $(GMOCK_ALL_SRC) -o $@

$(TEST_LIB): $(BUILD_DIR)/gtest-all.o $(BUILD_DIR)/gmock-all.o
	$(AR) $(ARFLAGS) $@ $(BUILD_DIR)/gtest-all.o $(BUILD_DIR)/gmock-all.o

$(TEST_OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc $(HEADERS)
	mkdir -p $(@D) && $(CXX) $(TEST_CXXFLAGS) -c $< -o $@

$(TEST_MAIN_OBJ): $(TEST_MAIN_SRC)
	mkdir -p $(@D) && $(CXX) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(TEST_CXXFLAGS) -c $< -o $@

$(PROTO_COMPILED): $(PROTO_SRC)
	protoc -I=$(SRC_DIR)/benchmarks --cpp_out=$(SRC_DIR)/benchmarks $<