#!/bin/sh

FILE="$1"
MODEL="$2"   # 1 = n^2, 2 = n log n

if [ -z "$FILE" ] || [ -z "$MODEL" ]; then
    echo "Uso: $0 <logfile> <1|2>"
    exit 1
fi

OUTPNG="${FILE}_TIME.png"

echo "Generando gráfica de tiempo con ajuste para $FILE..."
echo "Modelo: $MODEL"

gnuplot <<EOF
set terminal pngcairo size 1200,800
set output "${OUTPNG}"

set title "Tiempo medio vs n para ${FILE}"
set xlabel "n"
set ylabel "Tiempo Medio (seg)"
set grid

# Leer datos: columna 1 = n, columna 3 = avg

if (${MODEL} == 1) {
    f(x) = a2 * x**2 + b2
    a2 = 1e-9
    b2 = 1e-6
    FITFUNC = "n^2"
} else {
    f(x) = a2 * x*log(x) + b2
    a2 = 1e-9
    b2 = 1e-6
    FITFUNC = "n log n"
}

fit f(x) "${FILE}" using 1:3 via a2, b2

set key left top

plot "${FILE}" using 1:3 with points pointtype 7 pointsize 1.2 title "Tiempos Medios", \
     f(x) with lines linewidth 3 title sprintf("Ajuste (%s)", FITFUNC)

EOF

echo "Listo. Gráfica generada en: ${OUTPNG}"
