/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: swap
 *            This function swaps two elements in different positions
 */
static void swap(int *a, int *b){
  int temp;

  temp = *a;
  *a = *b;
  *b = temp;
}

/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order)
{
  PDICT dic;

	assert(size >= 0);

  dic = malloc(sizeof(DICT));
  if (dic == NULL){
    return NULL;
  }

  dic->size = size;
  dic->order = order;
  dic->n_data = 0;

  dic->table = malloc(sizeof(int) * dic->size);
  if (dic->table == NULL) {
    free(dic); 
    return NULL;
  }

  return dic;
}

void free_dictionary(PDICT pdict)
{
  if (pdict != NULL){
    free(pdict->table);
    free(pdict);
  }
}

int insert_dictionary(PDICT pdict, int key)
{
  int j; 

	assert(pdict != NULL);

  if (pdict->n_data >= pdict->size){
    return ERR;
  }

  if (pdict->order == SORTED){
    pdict->table[pdict->n_data] = key;
    j = pdict->n_data - 1;

    while (j >= 0 && pdict->table[j] > key){
      pdict->table[j+1] = pdict->table[j];
      j--;
    }
    pdict->table[j+1] = key;

    pdict->n_data ++;
  }
  else{
    pdict->table[pdict->n_data] = key;
    pdict->n_data ++;
  }

  return OK;
}

int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys)
{
  int i, ob = 0, status = 0;

	assert(pdict != NULL);
  assert(keys != NULL);
  assert(n_keys > 0);

  for (i = 0; i < n_keys; i++){
    status = insert_dictionary(pdict, keys[i]);
    if (status == ERR){
      return ERR;
    }

    ob ++;
  }

  return ob;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
	assert(pdict != NULL);
  assert(ppos != NULL);
  assert(method != NULL);

  return method(pdict->table, 0, pdict->n_data-1, key, ppos);
}


/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos)
{
  int ob = 0;
    int mid;

    assert(table != NULL);
    assert(F <= L);
    assert(ppos != NULL);

    while (F <= L) {
      ob++; 
      mid = F + (L - F) / 2;
      if (table[mid] == key) {
        *ppos = mid;
        return ob;
      }
      else if (table[mid] < key){
        F = mid + 1;
      }
      else{
        L = mid - 1;
      }
    }

    *ppos = NOT_FOUND;
    return ob;
}

int lin_search(int *table,int F,int L,int key, int *ppos)
{
	int i, ob = 0;

  assert(table != NULL);
  assert(F <= L);
  assert(ppos != NULL);

  for (i = F; i <= L; i++){
    ob ++;
    if (table[i] == key){
      *ppos = i;
      return ob;
    }
  }

  *ppos = NOT_FOUND;

  return ob;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
	int i, ob = 0;

  assert(table != NULL);
  assert(F <= L);
  assert(ppos != NULL);

  for (i = F; i <= L; i++) {
    ob++;
    if (table[i] == key) {
      *ppos = i;
      if (i > 0) {
        swap(&table[i-1], &table[i]);
        *ppos = i-1; 
      }
      return ob;
    }
  }

  *ppos = NOT_FOUND;
  return ob;
}


