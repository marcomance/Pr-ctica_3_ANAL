set title "Tiempo medio: Búsqueda Lineal vs Binaria"
set xlabel "Tamaño del diccionario (n)"
set ylabel "Tiempo medio (segundos)"
set grid
set key left top

plot \
    "lin_search.log" using 1:2 with linespoints title "Lineal", \
    "bin_search.log" using 1:2 with linespoints title "Binaria"

pause -1

