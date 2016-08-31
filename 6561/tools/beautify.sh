#! /bin/sh

clang-format -i -style=file sources/*.h sources/*.cc
rm -f *.orig
