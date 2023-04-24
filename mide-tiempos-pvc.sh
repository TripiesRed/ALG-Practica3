#!/bin/bash 
#echo "" >> salida.dat
i=200
while [ "$i" -le 5000 ]
do
	 ./Generador-pvc/datagen $i 
    ./$1 Generador-pvc/data >> $1TablaDatos.dat
      i=$(( $i + 200 ))
done
      
