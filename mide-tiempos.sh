#!/bin/bash 
#echo "" >> salida.dat
i=10000
while [ "$i" -le 250000 ]
do
	 ./Generador/datagen $i $3
    ./$1 $2 $3 /dev/null >> $1TablaDatos$2Comensales.dat
      i=$(( $i + 10000 ))
done
      
