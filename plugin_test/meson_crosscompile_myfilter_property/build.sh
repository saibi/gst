#!/bin/bash
meson setup local --prefix=/tmp
ninja -C local -v
ninja -C local install
