#!/bin/sh
# generate cmake buildsystem
cmake -S . -B build -G Ninja
# build cmake project
cmake --build build -j 4
# Check if symbolic link for compile_commands.json, if not create it
if ! [ -L "./compile_commands.json" ]; then
  ln -s build/compile_commands.json compile_commands.json
fi