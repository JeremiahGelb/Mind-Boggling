#!/bin/sh -l

echo "pwd:"
pwd

echo "files here:"
ls

echo "linting:"
cpplint --recursive */*