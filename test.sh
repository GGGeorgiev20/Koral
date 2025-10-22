#!/bin/bash
set -e

# compile whole project first to make sure the binary is up-to-date
cmake --preset=default 1>/dev/null
cmake --build --preset=default 1>/dev/null

ctest --test-dir ./build/default --output-on-failure

