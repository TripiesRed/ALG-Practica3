#!/bin/bash 
#echo "" >> salida.dat
i=1000
while [ "$i" -le 25000 ]
do
	 ./Generador-pvc/datagen $i 
    ./$1 $2 >> $1TablaDatos.dat
      i=$(( $i + 1000 ))
done
      
