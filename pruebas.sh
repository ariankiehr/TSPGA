#!/bin/bash
NUM=0

while [ $NUM -le 10 ]; do
	./gen > entrada.txt
	echo Nuevo tour generado
	echo Prim con 2opt:
	time ./Prim2opt < entrada.txt 
	echo TSPGA:
	time ./TSPGA < entrada.txt
	let NUM=$NUM+1
done
