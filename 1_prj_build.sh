#!/bin/bash

build_dir=$PWD/build
rm -r $build_dir
mkdir -p $build_dir
cd $build_dir

cmake ..

make
