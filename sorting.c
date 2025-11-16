/**
 *
 * Descripcion: Implementacion de funciones de ordenamiento
 *
 * Fichero: sorting.c
 * Autor: Ruben García, Marco Manceñido
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/***************************************************/
/* Funcion: swap                                   */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que intercambia dos elementos          */
/*                                                 */
/* Entrada:                                        */
/* int *a: primer elemento                         */
/* int *b: segundo elemento                        */
/* Salida: void                                   */
/***************************************************/
static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/***************************************************/
/* Funcion: InsertSort                              */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que implementa el algoritmo InsertSort */
/*                                                 */
/* Entrada:                                        */
/* int *array: array a ordenar                     */
/* int ip: indice inicial                           */
/* int iu: indice final                             */
/* Salida: int: numero de operaciones basicas     */
/***************************************************/
int InsertSort(int *array, int ip, int iu)
{
    int size, i, j, key;
    int counter = 0;

    assert(array != NULL);
    assert(ip >= 0);
    assert(iu >= ip);

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
/* Funcion: BubbleSort                              */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que implementa el algoritmo BubbleSort */
/*                                                 */
/* Entrada:                                        */
/* int *array: array a ordenar                     */
/* int ip: indice inicial                           */
/* int iu: indice final                             */
/* Salida: int: numero de operaciones basicas     */
/***************************************************/
int BubbleSort(int *array, int ip, int iu)
{
    int i, j;
    int size, counter = 0;

    assert(array != NULL);
    assert(ip >= 0);
    assert(iu >= ip);

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

/***************************************************/
/* Funcion: mergesort                               */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que implementa el algoritmo MergeSort  */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: array a ordenar                     */
/* int ip: indice inicial                           */
/* int iu: indice final                             */
/* Salida: int: numero de operaciones basicas     */
/***************************************************/
int mergesort(int* tabla, int ip, int iu) {
    int medio;
    int count = 0;

    assert(ip <= iu);

    if (ip == iu) {
        return 0;
    } 

    medio = (ip + iu) / 2;

    count += mergesort(tabla, ip, medio);
    count += mergesort(tabla, medio + 1, iu);
    count += merge(tabla, ip, iu, medio);

    return count;
}

/***************************************************/
/* Funcion: merge                                   */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que fusiona dos mitades ordenadas      */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: array a fusionar                    */
/* int ip: indice inicial                           */
/* int iu: indice final                             */
/* int imedio: indice medio                          */
/* Salida: int: numero de operaciones basicas     */
/***************************************************/
int merge(int* tabla, int ip, int iu, int imedio) {
    int *Taux;
    int i = ip;
    int j = imedio + 1;
    int k = 0;
    int n = iu - ip + 1;
    int count = 0;

    assert(tabla != NULL);
    assert(ip <= iu);

    Taux = (int*)malloc(n * sizeof(int));
    if (Taux == NULL) {
        return ERR;
    }

    while (i <= imedio && j <= iu) {
        if (tabla[i] <= tabla[j])
            Taux[k++] = tabla[i++];
        else
            Taux[k++] = tabla[j++];
        count++;
    }

    while (i <= imedio) {
        Taux[k++] = tabla[i++];
        count++;
    }

    while (j <= iu) {
        Taux[k++] = tabla[j++];
        count++;
    }

    for (k = 0; k < n; k++) {
        tabla[ip + k] = Taux[k];
    }

    free(Taux);
    return count;
}

/***************************************************/
/* Funcion: quicksort                               */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que implementa el algoritmo QuickSort  */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: array a ordenar                     */
/* int ip: indice inicial                           */
/* int iu: indice final                             */
/* Salida: int: numero de operaciones basicas     */
/***************************************************/
int quicksort(int* tabla, int ip, int iu) {
    int M;
    int count = 0, status;

    assert(tabla != NULL);
    assert(ip <= iu);

    if (ip >= iu) {
        return 0; 
    }

    status = partition(tabla, ip, iu, &M);
    if (status == ERR) {
        return ERR;
    }
    count += status;

    if (ip < M - 1) {
        status = quicksort(tabla, ip, M - 1);
        if (status == ERR) {
            return ERR;
        }
        count += status;
    }

    if (M + 1 < iu) {
        status = quicksort(tabla, M + 1, iu);
        if (status == ERR) {
            return ERR;
        }
        count += status;
    }

    return count;
}

/***************************************************/
/* Funcion: partition                               */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que particiona un array para QuickSort */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: array a particionar                 */
/* int ip: indice inicial                           */
/* int iu: indice final                             */
/* int *pos: posicion del pivote                     */
/* Salida: int: numero de operaciones basicas     */
/***************************************************/
int partition(int* tabla, int ip, int iu, int *pos) {
    int pivote, i, j;
    int medio;
    int count = 0, status; 

    assert(tabla != NULL);
    assert(ip <= iu);
    assert(pos != NULL);

    status = median_stat(tabla, ip, iu, &medio);
    if (status == ERR) {
        return ERR;
    }
    count += status;

    pivote = tabla[medio];
    count++; 

    swap(&tabla[medio], &tabla[iu]);
    count += SWAP_OP; 

    for (i = ip, j = ip; j < iu; j++) {
        count++; 
        if (tabla[j] < pivote) {
            if (i != j) {
                swap(&tabla[i], &tabla[j]);
                count += SWAP_OP; 
            }
            i++;
        }
    }

    swap(&tabla[i], &tabla[iu]);
    count += SWAP_OP; 

    *pos = i;
    return count;
}

/***************************************************/
/* Funcion: median                                  */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que devuelve el primer elemento como pivote */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: array                               */
/* int ip: indice inicial                           */
/* int iu: indice final                             */
/* int *pos: posicion del pivote                     */
/* Salida: int: 0 operaciones                      */
/***************************************************/
int median(int *tabla, int ip, int iu, int *pos) {
    assert(tabla != NULL);
    assert(pos != NULL); 
    assert(ip <= iu);

    *pos = ip;

    return 0;
}

/***************************************************/
/* Funcion: median_avg                              */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que devuelve el elemento medio como pivote */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: array                               */
/* int ip: indice inicial                           */
/* int iu: indice final                             */
/* int *pos: posicion del pivote                     */
/* Salida: int: 0 operaciones                      */
/***************************************************/
int median_avg(int *tabla, int ip, int iu, int *pos) {
    assert(tabla != NULL);
    assert(ip <= iu);
    assert(pos != NULL);

    *pos = (ip + iu) / 2;

    return 0; 
}

/***************************************************/
/* Funcion: median_stat                             */
/* Autores: Ruben García, Marco Manceñido         */
/*                                                 */
/* Funcion que devuelve la mediana entre primer,  */
/* medio y ultimo elemento como pivote             */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: array                               */
/* int ip: indice inicial                           */
/* int iu: indice final                             */
/* int *pos: posicion del pivote                     */
/* Salida: int: numero de operaciones basicas     */
/***************************************************/
int median_stat(int *tabla, int ip, int iu, int *pos) {
    int a, b, c;
    int count = 0;

    assert(tabla != NULL);
    assert(ip <= iu);
    assert(pos != NULL);

    a = tabla[ip];
    b = tabla[(ip + iu) / 2];
    c = tabla[iu];

    if (a <= b && b <= c) {
        *pos = (ip + iu) / 2;
        count += 2;
    }
    else if(c <= b && b <= a) {
        *pos = (ip + iu) / 2;
        count += 4;
    }
    else if (b <= a && a <= c) {
        *pos = ip;
        count += 6;
    } 
    else if (c <= a && a <= b) {
        *pos = ip;
        count += 8;
    }
    else {
        *pos = iu;
        count += 8;
    }

    return count;
}









