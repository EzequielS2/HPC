#!/bin/bash

# ======================================
# Script para compilar com varias flags
#
# v=0.1    
#
# Autor: Ezequiel
#
# =====================================


   for i in  $(seq 0 3)
     do
       cp laplaceserial.c laplace.c
       sed -i "s/XYX/$i/g" laplace.c
       gcc -pg -g -O$i laplace.c -lm -o laplace.x
       date +%r > TS$i.dat
       time ./laplace.x
       date +%r >> TS$i.dat
       gprof laplace.x gmon.out > profilingSerialFlagO$i.dat

 done
