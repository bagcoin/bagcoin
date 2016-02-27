#!/bin/bash

TARGET_OS=NATIVE_WINDOWS mingw32-make clean
make clean
TARGET_OS=NATIVE_WINDOWS mingw32-make libleveldb.a libmemenv.a
