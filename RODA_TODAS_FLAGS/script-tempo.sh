#!/bin/bash



for i in $(seq 0 3)
do
	gcc -o LaplaceSerialO$i.exe laplace.c -O$i -lm
	t1=$(date "+%s")
	./LaplaceSerialO$i.exe
	t2=$(date "+%s")

	tempo=$(($t2-$t1))
	
	echo $i $tempo >> tempos-flagO.dat

done 


