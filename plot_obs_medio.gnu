set title "Operaciones básicas: Búsqueda Lineal vs Binaria"
set xlabel "Tamaño del diccionario (n)"
set ylabel "Operaciones básicas medias"
set grid
set key left top

plot \
    "lin_search.log" using 1:3 with linespoints title "Lineal", \
    "bin_search.log" using 1:3 with linespoints title "Binaria"

pause -1
