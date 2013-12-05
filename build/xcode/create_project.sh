#!/bin/sh

if [ ! -d project ] ; then 
    mkdir project
fi

cd project
cmake -G Xcode ./../../cmake/
