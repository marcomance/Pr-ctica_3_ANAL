#!/bin/bash

# Comprobación de argumento
if [ $# -ne 1 ]; then
    echo "Uso: $0 fichero.log"
    exit 1
fi

LOGFILE="$1"
OUTPNG="${LOGFILE%.log}_OBs.png"

echo "Generando gráfica de OBs para $LOGFILE → $OUTPNG"

gnuplot << EOF
set terminal pngcairo size 1200,800 enhanced font "Arial,14"
set output "$OUTPNG"

set title "OBs (min, max y promedio) para $LOGFILE"
set xlabel "Tamaño / búsqueda"
set ylabel "Operaciones básicas (OB)"
set grid
set key left top

plot \
    "$LOGFILE" using 1:3 with lines lw 2 title "OB promedio", \
    "$LOGFILE" using 1:4 with lines lw 2 title "OB mínimo", \
    "$LOGFILE" using 1:5 with lines lw 2 title "OB máximo"
EOF

echo "Listo. Gráfica generada: $OUTPNG"
