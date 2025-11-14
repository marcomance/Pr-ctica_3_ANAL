/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"
#include <stdlib.h>
void swap(int *a, int *b)
{
    int temp;

    if (!a || !b) {
        return; 
    }

    temp = *a;
    *a = *b;
    *b = temp;
}

/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int InsertSort(int *array, int ip, int iu)
{
    int size, i, j, key;
    int counter = 0; 

    if (!array || ip < 0 || iu < ip) {
        return ERR;
    }

    size = iu - ip + 1;

    for (i = 1; i < size; ++i) {
        key = array[ip + i];
        j = ip + i - 1;

        while (j >= ip) {
            counter++;  
            if (array[j] > key) {
                array[j + 1] = array[j];
                j--;
            } else {
                break;
            }
        }

        array[j + 1] = key;
    }

    return counter;
}




/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int *array, int ip, int iu)
{
    int i, j;
    int size, counter = 0;

    if (!array || ip < 0 || iu < ip) {
        return ERR;
    }

    size = iu - ip + 1;

    for (i = 0; i < size - 1; i++) {
        for (j = ip; j < iu - i; j++) {
            counter++; 
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }

    return counter;
}



#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR -1

int merge(int* tabla, int ip, int iu, int imedio);
int mergesort(int* tabla, int ip, int iu);

int mergesort(int* tabla, int ip, int iu) {
    int medio;
    int count = 0;
    int aux1;
    int aux2;

    if (ip > iu)
        return ERR;

    if (ip == iu)
        return 0; /* no operaciones */

    medio = (ip + iu) / 2;

    aux1 = mergesort(tabla, ip, medio);

    aux2 = mergesort(tabla, medio + 1, iu);

    return aux1 + aux2 + merge(tabla, ip, iu, medio);
}

int merge(int* tabla, int ip, int iu, int imedio) {
    int *Taux;
    int i = ip;
    int j = imedio + 1;
    int k = 0;
    int n = iu - ip + 1;
    int count = 0; /* operaciones básicas */

    Taux = (int*)malloc(n * sizeof(int));
    if (Taux == NULL)
        return ERR;

    /* Comparaciones y asignaciones principales */
    while (i <= imedio && j <= iu) {
        if (tabla[i] <= tabla[j])
            Taux[k++] = tabla[i++]; /* asignación */
        else
            Taux[k++] = tabla[j++]; /* asignación */
        count++; /* por la asignación del elemento */
    }

    while (i <= imedio) {
        Taux[k++] = tabla[i++];
        count++; /* asignación */
    }

    while (j <= iu) {
        Taux[k++] = tabla[j++];
        count++; /* asignación */
    }

    /* Copiar de vuelta a tabla */
    for (k = 0; k < n; k++) {
        tabla[ip + k] = Taux[k];
    }

    free(Taux);
    return count;
}




int quicksort(int* tabla, int ip, int iu) {
    int M;
    int count = 0;
    int aux;

    if (ip > iu)
        return ERR;

    if (ip == iu)
        return 0; /* sin operaciones básicas */

    aux = partition(tabla, ip, iu, &M);
    if (aux == ERR)
        return ERR;
    count += aux; /* operaciones en partition */

    if (ip < M - 1) {
        aux = quicksort(tabla, ip, M - 1);
        if (aux == ERR)
            return ERR;
        count += aux;
    }

    if (M + 1 < iu) {
        aux = quicksort(tabla, M + 1, iu);
        if (aux == ERR)
            return ERR;
        count += aux;
    }

    return count;
}

int partition(int* tabla, int ip, int iu, int *pos) {
    int pivote, i, j, tmp;
    int medio;
    int count = 0; /* operaciones básicas */

    /* Mediana de tres */
    if (median_avg(tabla, ip, iu, &medio) == ERR)
        return ERR;

    /* pivote = tabla[medio] */
    pivote = tabla[medio];
    count++; /* lectura del pivote */

    /* Mover pivote al final */
    tmp = tabla[medio];
    tabla[medio] = tabla[iu];
    tabla[iu] = tmp;
    count += 3; /* tres asignaciones */

    i = ip;
    for (j = ip; j < iu; j++) {
        count++; /* comparación tabla[j] < pivote */
        if (tabla[j] < pivote) {
            tmp = tabla[i];
            tabla[i] = tabla[j];
            tabla[j] = tmp;
            count += 3; /* tres asignaciones por swap */
            i++;
        }
    }

    /* Colocar el pivote en su posición final */
    tmp = tabla[i];
    tabla[i] = tabla[iu];
    tabla[iu] = tmp;
    count += 3; /* tres asignaciones */

    *pos = i;
    return count;
}

int median(int *tabla, int ip, int iu, int *pos) {
    int medio = (ip + iu) / 2;
    int a = tabla[ip];
    int b = tabla[medio];
    int c = tabla[iu];
    int count = 0;
    *pos = ip;
    return count;
}

int median_avg(int *tabla, int ip, int iu, int *pos) {
    int medio = (ip + iu) / 2;
    int a = tabla[ip];
    int b = tabla[medio];
    int c = tabla[iu];
    int count = 0;
    *pos = medio;
    return count;
}


/* median_stat: devuelve en *pos el índice (ip..iu) que contiene
   la mediana entre tabla[ip], tabla[(ip+iu)/2] y tabla[iu].
   Devuelve OK (0) o ERR (-1) en caso de error (por ejemplo ip>iu).
*/


int median_stat(int *tabla, int ip, int iu, int *pos) {
    int imedio;
    int a, b, c;

    if (tabla == NULL || pos == NULL || ip > iu)
        return ERR;

    imedio = (ip + iu) / 2;
    a = tabla[ip];
    b = tabla[imedio];
    c = tabla[iu];

    /* Comparar para hallar la mediana de tres valores */
    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        *pos = imedio;
    } else if ((b <= a && a <= c) || (c <= a && a <= b)) {
        *pos = ip;
    } else {
        *pos = iu;
    }

    return OK;
}

/* Variante de partition que usa median_stat como pivote.
   Además permite acumular operaciones básicas (ops): si ops != NULL,
   se incrementa *ops por cada comparación entre elementos del array
   (esto es una definición de ejemplo de "operación básica").
   Firma: int partition_count(int *tabla, int ip, int iu, int *pos, long *ops)
   Devuelve OK/ERR y coloca la posición final del pivote en *pos.
*/
int partition_count(int *tabla, int ip, int iu, int *pos, long *ops) {
    int piv_idx;
    int piv_val;
    int i, j, tmp;
    int cmp_result;

    if (tabla == NULL || pos == NULL || ip > iu)
        return ERR;

    /* obtener índice del pivote usando median_stat */
    if (median_stat(tabla, ip, iu, &piv_idx) == ERR)
        return ERR;

    /* opcional: contar la comparación que hace median_stat (si quieres) */
    /* aquí no incrementamos ops por median_stat internamente,
       pero podrías sumar 2 ó 3 si quieres reflejar esas comparaciones. */

    /* llevar pivote al final (iu) */
    tmp = tabla[piv_idx];
    tabla[piv_idx] = tabla[iu];
    tabla[iu] = tmp;

    piv_val = tabla[iu];
    i = ip;

    for (j = ip; j < iu; j++) {
        /* contar comparación tabla[j] < piv_val */
        if (ops) (*ops)++;

        if (tabla[j] < piv_val) {
            /* swap tabla[i] <-> tabla[j] */
            tmp = tabla[i];
            tabla[i] = tabla[j];
            tabla[j] = tmp;
            i++;
            /* contar también el swap como operaciones si lo deseas:
               if (ops) (*ops) += SWAP_COST; */
        }
    }

    /* colocar pivote en su posición final i */
    tmp = tabla[i];
    tabla[i] = tabla[iu];
    tabla[iu] = tmp;

    *pos = i;
    return OK;
}









