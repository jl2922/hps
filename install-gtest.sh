#!/bin/bash
echo "Downloading Google Test"
wget -O release-1.8.0.tar.gz https://github.com/google/googletest/archive/release-1.8.0.tar.gz
tar xzf release-1.8.0.tar.gz
rm release-1.8.0.tar.gz
mv googletest-release-1.8.0 gtest
echo "Completed"
echo
