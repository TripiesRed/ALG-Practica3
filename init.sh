#!/bin/bash 

#Script que permite generar un caso dados dos argumentos:
# numero_puntos = Tamaño del problema a resolver
# <nombre_archivo> = Nombre del archivo donde se almacene el caso
#
#Así pues, además de generar el problema, este script también se encarga de hacer:
# 	1) make all (Para crear los archivos objetos)
# 	2) Resolver el problema/caso con los algoritmos Dyv y Específico


if (( $# > 2 || $# == 0 )); then echo "./init nombre_archivo <numero_puntos>"; exit

elif (( $# == 2 ))
	then
	make all
	./Generador/datagen $2 $1
	./Dyv/dyv $1
	./Especifico/especifico $1
	
else (( $# == 1 ))
	make all
	./Dyv/dyv $1
	./Especifico/especifico $1
	
fi

