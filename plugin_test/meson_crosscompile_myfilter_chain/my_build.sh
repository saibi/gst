#!/bin/bash
meson setup build --prefix=/tmp
ninja -C build -v
ninja -C build install
