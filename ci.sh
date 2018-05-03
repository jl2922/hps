#!/bin/bash

set -x
export TOOLS_DIR=$TRAVIS_BUILD_DIR/tools
echo $TOOLS_DIR

# Install or Load Protocol Buffers.
if [ -f "$TOOLS_DIR/protobuf/bin/protoc" ]; then
  echo "Found cached Protocol Buffers"
else
  echo "Downloading Protocol Buffers"
  mkdir -p downloads
  cd downloads
  wget -O protobuf-cpp-3.5.1.tar.gz https://github.com/google/protobuf/releases/download/v3.5.1/protobuf-cpp-3.5.1.tar.gz
  tar xzf protobuf-cpp-3.5.1.tar.gz
  echo "Configuring and building Protocol Buffers"
  cd protobuf-3.5.1
  mkdir -p $TOOLS_DIR/protobuf
  ./configure --prefix=$TOOLS_DIR/protobuf CC=$C_COMPILER CXX=$CXX_COMPILER
  make -j 8
  make install
  echo "Completed"
  cd ../../
fi
export PATH=$TOOLS_DIR/protobuf/bin:$PATH
export LD_LIBRARY_PATH=$TOOLS_DIR/protobuf/lib:$LD_LIBRARY_PATH

# Install or Load CapnProto.
if [ -f "$TOOLS_DIR/capnproto/bin/capnp" ]; then
  echo "Found cached CapnProto"
else
  echo "Downloading CapnProto"
  mkdir -p downloads
  cd downloads
  wget -O capnproto-c++-0.6.1.tar.gz https://capnproto.org/capnproto-c++-0.6.1.tar.gz
  tar xzf capnproto-c++-0.6.1.tar.gz
  echo "Configuring and building CapnProto"
  cd capnproto-c++-0.6.1
  mkdir -p $TOOLS_DIR/capnproto
  ./configure --prefix=$TOOLS_DIR/capnproto CC=$C_COMPILER CXX=$CXX_COMPILER
  make -j 8
  make install
  echo "Completed"
  cd ../../
fi
export PATH=$TOOLS_DIR/capnproto/bin:$PATH
export LD_LIBRARY_PATH=$TOOLS_DIR/capnproto/lib:$LD_LIBRARY_PATH

# Install or Load Boost.
if [ -f "$TOOLS_DIR/boost/lib/libboost_serialization.so" ] ; then
  echo "Found cached Boost"
else
  echo "Downloading Boost"
  mkdir -p downloads
  cd downloads
  wget -O boost_1_66_0.tar.bz2 https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.bz2
  tar xjf boost_1_66_0.tar.bz2
  echo "Configuring and building Boost"
  cd boost_1_66_0
  mkdir -p $TOOLS_DIR/boost
  ./bootstrap.sh
  echo 'libraries = --with-serialization ;' >> project-config.jam
  echo $BOOST_USE >> project-config.jam
  ./b2 -j8 --prefix=$TOOLS_DIR/boost install
  echo "Completed"
  cd ../../
fi
export PATH=$TOOLS_DIR/boost/bin:$PATH
export LD_LIBRARY_PATH=$TOOLS_DIR/boost/lib:$LD_LIBRARY_PATH

make test_all -j
make benchmark -j