# Default options.
CXX := g++
CXX_WARNING_OPTIONS := -Wall -Wextra
CXXFLAGS := -std=c++11 -O3 $(CXX_WARNING_OPTIONS)
LDLIBS := -pthread -lprotobuf -lcapnp -lkj -lboost_serialization -lpthread
SRC_DIR := src
BUILD_DIR := build
TEST_EXE := benchmark.out

# Libraries.
BOOST_DIR := $(TOOLS_DIR)/boost
PROTOBUF_DIR := $(TOOLS_DIR)/protobuf
CAPNPROTO_DIR := $(TOOLS_DIR)/capnproto
CXXFLAGS := $(CXXFLAGS) -isystem $(BOOST_DIR)/include \
    -isystem $(PROTOBUF_DIR)/include -isystem $(CAPNPROTO_DIR)/include
LDLIBS := -L $(BOOST_DIR)/lib -L $(PROTOBUF_DIR)/lib -L $(CAPNPROTO_DIR)/lib $(LDLIBS)

# Load Makefile.config if exists.
LOCAL_MAKEFILE := local.mk
ifneq ($(wildcard $(LOCAL_MAKEFILE)),)
	include $(LOCAL_MAKEFILE)
endif

# Sources and intermediate objects.
BENCHMARK_DIR := $(SRC_DIR)/benchmark
PROTOBUF_SRC := $(BENCHMARK_DIR)/protobuf_benchmark.proto
PROTOBUF_COMPILED := $(BENCHMARK_DIR)/protobuf_benchmark.pb.h $(BENCHMARK_DIR)/protobuf_benchmark.pb.cc
CAPNPROTO_SRC := $(BENCHMARK_DIR)/capnproto_benchmark.capnp
CAPNPROTO_COMPILED_H := $(BENCHMARK_DIR)/capnproto_benchmark.capnp.h
CAPNPROTO_COMPILED_CC := $(BENCHMARK_DIR)/capnproto_benchmark.capnp.cc
CAPNPROTO_COMPILED_CXX := $(BENCHMARK_DIR)/capnproto_benchmark.capnp.c++
SRCS := $(shell find $(SRC_DIR) ! -name "*_test.cc" -name "*.cc")
TESTS := $(shell find $(SRC_DIR)/benchmark -name "*_test.cc")
HEADERS := $(shell find $(SRC_DIR) -name "*.h")
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

.PHONY: all benchmark test_build

.SUFFIXES:

all:
	$(MAKE) -f benchmark.mk benchmark

benchmark: test_build
	./$(TEST_EXE)

test_build: $(PROTOBUF_COMPILED) $(CAPNPROTO_COMPILED_H) $(CAPNPROTO_COMPILED_CC)
	$(MAKE) -f benchmark.mk $(TEST_EXE)

$(TEST_EXE): $(TEST_OBJS) $(OBJS) $(TEST_LIB)
	$(CXX) $(TEST_CXXFLAGS) $(TEST_OBJS) $(OBJS) $(TEST_MAIN_SRC) $(TEST_LIB) -o $(TEST_EXE) $(LDLIBS)

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

%.pb.h %.pb.cc: %.proto
	protoc -I=$(@D) --cpp_out=$(@D) $<

%.capnp.c++ %.capnp.h: %.capnp
	capnp compile -oc++ $<

%.capnp.cc: %.capnp.c++
	cp $< $@
