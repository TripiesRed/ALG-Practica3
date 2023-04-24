#!/bin/bash 
#echo "" >> salida.dat
i=100000
while [ "$i" -le 2500000 ]
do
	 ./Generador/datagen1 $i $3
    ./$1 $2 $3 /dev/null >> $1TablaDatos$2.dat
      i=$(( $i + 100000 ))
done
      
