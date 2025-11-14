/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */
#include <stdlib.h>
#include <time.h>
#include "permutations.h"

/***************************************************/
/* Function: random_num Date:                      */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  if(inf > sup){
    return ERR;
  }
  return rand()/(RAND_MAX+1.)*(sup-inf+1)+inf;
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int *perm;
  int j;
  int num;
  int dum;
  perm = malloc(N*sizeof(int));
  if(perm==NULL){
    return NULL;
  }
  for(j=0; j<N; j++){
    perm[j] = j+1;
  }
  for(j=0; j<N; j++){
    num = random_num(j, N-1);
    dum = perm[j];
    perm[j] = perm[num];
    perm[num] = dum;
  }
  return perm;

}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int **perm;
  int i;

  perm = malloc(n_perms*sizeof(int*));
  if (perm == NULL){
    return NULL;
  }

  for (i = 0; i < n_perms; i++){
    perm[i] = generate_perm(N);
    if (perm[i] == NULL){
      for (i = i-1; i >= 0; i--){
        free(perm[i]);
      }
      return NULL;
    }
  }

  return perm;
}

void free_permutations(int **perm, int n_perms)
{
    int i;

    if(perm == NULL){
        return;
    }

    for(i = 0; i < n_perms; i++){
        free(perm[i]);
    }

    free(perm);
}
