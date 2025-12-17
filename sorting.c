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
#include <stdio.h>
#include <assert.h>

/** Función interna para merge de mergesort */
int merge(int* tabla, int ip, int iu, int imedio);
/** Función interna de mergesort recursiva */
int mergesort(int* tabla, int ip, int iu);

/***************************************************/
/* Function: swap
   Intercambia el valor de dos enteros apuntados por a y b.
   Verifica que los punteros no sean NULL antes de hacer el swap.
***************************************************/
static void swap(int *a, int *b)
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
/* Function: InsertSort
   Algoritmo de ordenamiento por inserción.
   Recorre el array y va insertando cada elemento en la posición correcta
   respecto a los elementos anteriores ya ordenados.
   Devuelve el número de comparaciones realizadas.
   Parámetros:
     array: array a ordenar
     ip: índice inferior del rango
     iu: índice superior del rango
***************************************************/
int InsertSort(int *array, int ip, int iu)
{
    int size, i, j, key;
    int counter = 0; 

    assert(array != NULL);
    assert(ip >= 0);
    assert(iu >= ip);

    size = iu - ip + 1;

    for (i = 1; i < size; ++i) {
        key = array[ip + i];  /** elemento a insertar */
        j = ip + i - 1;

        /** desplaza elementos mayores que key una posición a la derecha */
        while (j >= ip) {
            counter++;  
            if (array[j] > key) {
                array[j + 1] = array[j];
                j--;
            } else {
                break;
            }
        }

        array[j + 1] = key; /** inserta key en su posición correcta */
    }

    return counter;
}

/***************************************************/
/* Function: BubbleSort
   Algoritmo de ordenamiento burbuja.
   Recorre el array varias veces, comparando elementos adyacentes
   y los intercambia si están en orden incorrecto.
   Devuelve el número de comparaciones realizadas.
***************************************************/
int BubbleSort(int *array, int ip, int iu)
{
    int i, j;
    int size, counter = 0;

    assert(array != NULL);
    assert(ip >= 0);
    assert(iu >= ip);

    size = iu - ip + 1;

    /** Recorre el array y realiza intercambios si el elemento actual es mayor que el siguiente */
    for (i = 0; i < size - 1; i++) {
        for (j = ip; j < iu - i; j++) {
            counter++; 
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]); /** intercambio de elementos */
            }
        }
    }

    return counter;
}

/***************************************************/
/* Function: mergesort
   Algoritmo de ordenamiento MergeSort.
   Divide el array en mitades recursivamente.
   Luego combina las mitades ordenadas usando merge().
   Devuelve el número de operaciones realizadas.
***************************************************/
int mergesort(int* tabla, int ip, int iu) {
    int medio;
    int count = 0;
    int status;

    assert(tabla != NULL);
    
    if (ip > iu)
        return ERR;

    if (ip == iu)
        return 0; /** rango de un solo elemento ya está ordenado */

    medio = (ip + iu) / 2;

    status = mergesort(tabla, ip, medio); /** ordena mitad izquierda */
    if(status == ERR){
        return ERR;
    }
    count += status;

    status = mergesort(tabla, medio + 1, iu); /** ordena mitad derecha */
    if(status == ERR){
        return ERR;
    }
    count += status;

    status = merge(tabla, ip, iu, medio); /** combina las dos mitades */
    if(status == ERR){
        return ERR;
    }
    count += status;

    return count;
}

/***************************************************/
/* Function: merge
   Función auxiliar de mergesort que combina dos subarrays ordenados.
   Crea un array temporal para almacenar los elementos ordenados.
   Devuelve el número de asignaciones realizadas (operaciones básicas).
***************************************************/
int merge(int* tabla, int ip, int iu, int imedio) {
    int *Taux;
    int i = ip;
    int j = imedio + 1;
    int k = 0;
    int n = iu - ip + 1;
    int count = 0;

    Taux = (int*)malloc(n * sizeof(int));
    if (Taux == NULL)
        return ERR; /** error de memoria */

    /** mezcla los elementos de ambas mitades en orden ascendente */
    while (i <= imedio && j <= iu) {
        if (tabla[i] <= tabla[j])
            Taux[k++] = tabla[i++]; /** asignación */
        else
            Taux[k++] = tabla[j++]; /** asignación */
        count++; /** cuenta la operación básica de asignación */
    }

    /** copia los elementos restantes de la mitad izquierda */
    while (i <= imedio) {
        Taux[k++] = tabla[i++];
        count++;
    }

    /** copia los elementos restantes de la mitad derecha */
    while (j <= iu) {
        Taux[k++] = tabla[j++];
        count++;
    }

    /** copia de vuelta al array original */
    for (k = 0; k < n; k++) {
        tabla[ip + k] = Taux[k];
    }

    free(Taux);
    return count;
}

/***************************************************/
/* Function: quicksort
   Algoritmo de ordenamiento QuickSort.
   Escoge un pivote usando partition().
   Ordena recursivamente subarrays a la izquierda y derecha del pivote.
   Devuelve el número de operaciones realizadas.
***************************************************/
int quicksort(int* tabla, int ip, int iu) {
    int M;
    int count = 0;
    int aux;

    if (ip > iu)
        return ERR;

    if (ip == iu)
        return 0; /** sin operaciones básicas */

    aux = partition(tabla, ip, iu, &M);
    if (aux == ERR)
        return ERR;
    count += aux; /** operaciones en partition */

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

/***************************************************/
/* Function: partition
   Función auxiliar de QuickSort.
   Selecciona un pivote usando median_avg.
   Reorganiza el array de forma que elementos menores al pivote
   queden a la izquierda y mayores a la derecha.
   Devuelve la posición final del pivote en *pos y el número de operaciones.
***************************************************/
int partition(int* tabla, int ip, int iu, int *pos) {
    int pivote, i, j;
    int medio;
    int count = 0; /** operaciones básicas */

    /** obtiene índice del pivote mediante mediana */
    if (median_avg(tabla, ip, iu, &medio) == ERR)
        return ERR;

    pivote = tabla[medio];
    count++; /** lectura del pivote */

    /** mueve pivote al final */
    swap(&tabla[medio], &tabla[iu]);
    count += 3; /** tres asignaciones */

    i = ip;
    for (j = ip; j < iu; j++) {
        count++; /** comparación tabla[j] < pivote */
        if (tabla[j] < pivote) {
            swap(&tabla[i], &tabla[j]);
            count += 3; /** tres asignaciones por swap */
            i++;
        }
    }

    /** coloca pivote en su posición final */
    swap(&tabla[i], &tabla[iu]);
    count += 3; /** tres asignaciones */

    *pos = i;
    return count;
}

/***************************************************/
/* Function: median Date:                          */
/* Authors: Marco Manceñido y Rubén García         */
/*                                                 */
/* Function that returns first element as pivot    */
/*                                                 */
/* Input:                                          */
/* int *tabla: array                               */
/* int ip: initial index                           */
/* int iu: final index                             */
/* int *pos: pointer to store pivot position       */
/* Output:                                         */
/* int: 0 operations                               */
/* or ERR in case of error                         */
/***************************************************/
int median(int *tabla, int ip, int iu, int *pos) {
    assert(tabla != NULL);
    assert(pos != NULL); 
    assert(ip <= iu);

    *pos = ip;

    return 0;
}

/***************************************************/
/* Function: median_avg Date:                      */
/* Authors: Marco Manceñido y Rubén García         */
/*                                                 */
/* Function that returns middle element as pivot   */
/*                                                 */
/* Input:                                          */
/* int *tabla: array                               */
/* int ip: initial index                           */
/* int iu: final index                             */
/* int *pos: pointer to store pivot position       */
/* Output:                                         */
/* int: 0 operations                               */
/* or ERR in case of error                         */
/***************************************************/
int median_avg(int *tabla, int ip, int iu, int *pos) {
    assert(tabla != NULL);
    assert(ip <= iu);
    assert(pos != NULL);

    *pos = (ip + iu) / 2;

    return 0; 
}

/***************************************************/
/* Function: median_stat
   Devuelve en *pos el índice que contiene la mediana entre
   tabla[ip], tabla[(ip+iu)/2] y tabla[iu].
   Devuelve el número de comparaciones realizadas como "operaciones básicas".
***************************************************/
int median_stat(int *tabla, int ip, int iu, int *pos) {
    int mid = (iu + ip)/2;
    int ob_count =0;
    ob_count ++;
    if(tabla[ip] < tabla[mid]){
        ob_count++;
        if(tabla[mid] < tabla[iu]){
            *pos = mid;
            return ob_count;
        }else if(tabla[ip] > tabla[iu]){
            *pos = ip;
            return ++ob_count;
        }else{
            *pos = iu;
            return ++ob_count;
        }
    }else{
        ob_count++;
        if(tabla[ip] < tabla[iu]){
            *pos = ip;
            return ob_count;
        }else if(tabla[mid] < tabla[iu]){
            *pos = iu;
            return ++ob_count;
        }else{
            *pos = mid;
            return ++ob_count;
        }
    }
    return ERR;
}

/***************************************************/
/* Function: partition_count
   Variante de partition que usa median_stat como pivote.
   Permite acumular operaciones básicas en *ops.
   Coloca en *pos la posición final del pivote.
***************************************************/
int partition_count(int *tabla, int ip, int iu, int *pos, long *ops) {
    int piv_idx;
    int piv_val;
    int i, j;

    if (tabla == NULL || pos == NULL || ip > iu)
        return ERR;

    /** obtiene índice del pivote usando median_stat */
    if (median_stat(tabla, ip, iu, &piv_idx) == ERR)
        return ERR;

    /** lleva pivote al final */
    swap(&tabla[piv_idx], &tabla[iu]);

    piv_val = tabla[iu];
    i = ip;

    /** reorganiza elementos comparando con el pivote */
    for (j = ip; j < iu; j++) {
        if (ops) (*ops)++; /** cuenta comparación */

        if (tabla[j] < piv_val) {
            if (ops) (*ops)+=3; /** comparaciones swap */
            swap(&tabla[i], &tabla[j]);
            i++;
        }
    }

    /** coloca pivote en su posición final */
    swap(&tabla[i], &tabla[iu]);

    if (ops) (*ops)+=3; /** comparaciones swap */

    *pos = i;
    return OK;
}
