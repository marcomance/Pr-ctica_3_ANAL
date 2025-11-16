/**
 *
 * Descripcion: Header file for sorting functions 
 *
 * Fichero: sorting.h
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#ifndef SORTING_H
#define SORTING_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

#ifndef SWAP_OP
  #define SWAP_OP 3
#endif

#include <assert.h>

/* type definitions */
typedef int (* pfunc_sort)(int*, int, int);

/* Functions */
int BubbleSort(int* array, int ip, int iu);
int InsertSort(int* array, int ip, int iu);
int merge(int* tabla, int ip, int iu, int imedio);
int mergesort(int* tabla, int ip, int iu);
int partition(int* tabla, int ip, int iu, int *pos);
int median(int *tabla, int ip, int iu, int *pos);
int quicksort(int* tabla, int ip, int iu);
int median_stat(int *tabla, int ip, int iu, int *pos);

#endif
