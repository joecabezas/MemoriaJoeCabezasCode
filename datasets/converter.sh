#!/bin/bash

usage()
{
cat << EOF

Uso: $0 <options>

Este script transforma todas las imagenes de una cierta carpeta al formato
PGM, y las guarda en un subdirectorio llamado pgm/ dentro de la carpeta
mencionada.

OPCIONES:
	-h	Imprime este mensaje de ayuda de uso
	-d	Carpeta donde estan las imagenes a transformar
	-t	Carpeta destino de imagenes transformadas (default: pgm)
	-r	Argumento -resize usado por ImageMagick (default: 100%)
	-a	Modo sin compresion ASCII de imagemagick (-compress none)
EOF
}

#if [ $# -eq 0 ]; then
#	usage
#	exit
#fi

while getopts "hd:e:t:r:a" opt; do
	case $opt in
		h)
			usage
			;;
		d)
			BASE_DIR=$OPTARG
			;;
		t)
			TARGET_DIR=$OPTARG
			;;
		r)
			RESIZE=$OPTARG
			;;
		a)
			COMPRESS="-compress none"
			;;
	esac
done

#VALORES POR DEFECTO
if [ -z "$BASE_DIR" ]; then BASE_DIR="."; fi
if [ -z "$RESIZE" ]; then RESIZE="100%"; fi
if [ -z "$TARGET_DIR" ]; then TARGET_DIR="pgm"; fi

###########
#EXECUTION#
###########

ARGUMENTS="-verbose -resize $RESIZE $COMPRESS"

#Go to base dir
cd "$BASE_DIR"

#make target dir
if [ ! -d "$TARGET_DIR" ]; then
	mkdir "$TARGET_DIR"
fi 

for f in *; do
	convert "$f" $ARGUMENTS "$TARGET_DIR/$f.pgm"
done
