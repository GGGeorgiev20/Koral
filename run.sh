#!/bin/bash
# set -a
# source .env
# set +a

set -e
cmake --preset=default
cmake --build --preset=default
./build/default/koral "$@"
