#!/bin/bash

meson setup b --cross-file=rk3399.txt --prefix=/tmp

ninja -C b -v

ninja -C b install
