#!/bin/sh
for file in `find . -name '*.[hc]pp'`
do
    clang-format -i $file -style=file
done
