#! /bin/sh

clang-format -i -style=file sources/*.h sources/*.cc tests/*.cc
rm -f *.orig
