#!/bin/bash

[ -d submitDir ] && rm -rf submitDir

time ./eventLoop.py -b
