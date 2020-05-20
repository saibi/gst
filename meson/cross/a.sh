#!/bin/bash 

meson setup b --cross-file=rk3399.txt
ninja -C b -v
