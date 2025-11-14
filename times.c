/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso (adaptado con implementación)
 * Version: 1.1
 * Fecha: 02-10-2025
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "times.h"
#include "sorting.h"
#include "permutations.h" /* Necesaria para generate_permutations() */
#include "search.h"
#include <assert.h>

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms, int N, PTIME_AA ptime)
{
  clock_t time0, time1;
  int **permutations = NULL;
  int i, ob, allob = 0;
  int min_ob;
  int max_ob;

  if (metodo == NULL || ptime == NULL || n_perms < 1 || N < 1)
  {
    return ERR;
  }

  permutations = generate_permutations(n_perms, N);
  if (permutations == NULL)
  {
    return ERR;
  }

  time0 = clock();

  for (i = 0; i < n_perms; i++)
  {
    ob = metodo(*(permutations + i), 0, N - 1);
    if (i == 0)
    {
      min_ob = max_ob = ob;
    }
    if (ob == ERR)
    {
      free(permutations);
      return ERR;
    }
    else
    {
      allob += ob;

      if (ob < min_ob)
      {
        min_ob = ob;
      }

      if (ob > max_ob)
      {
        max_ob = ob;
      }
    }
  }

  time1 = clock();

  ptime->time = (double)(time1 - time0) / (double)CLOCKS_PER_SEC / (double)n_perms;
  ptime->average_ob = (double)allob / (double)n_perms;
  ptime->min_ob = min_ob;
  ptime->max_ob = max_ob;
  ptime->N = N;
  ptime->n_elems = n_perms;

  free_permutations(permutations, n_perms);

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times                */
/*                                                 */
/* Ejecuta average_sorting_time para varios N      */
/* y guarda los resultados en un fichero           */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char *file,
                             int num_min, int num_max,
                             int incr, int n_perms)
{
  int i, n_times;
  PTIME_AA times = NULL;

  if (!method || !file || num_min <= 0 || num_max < num_min || incr <= 0 || n_perms <= 0)
    return ERR;

  n_times = ((num_max - num_min) / incr) + 1;
  times = (PTIME_AA)malloc(n_times * sizeof(TIME_AA));
  if (!times)
    return ERR;

  for (i = 0; i < n_times; i++)
  {
    int N = num_min + i * incr;
    if (average_sorting_time(method, n_perms, N, &times[i]) == ERR)
    {
      free(times);
      return ERR;
    }
  }

  if (save_time_table(file, times, n_times) == ERR)
  {
    free(times);
    return ERR;
  }

  free(times);
  return OK;
}

/***************************************************/
/* Function: save_time_table                       */
/*                                                 */
/* Guarda los resultados en un fichero de texto    */
/* con el formato:                                 */
/* N   time   avg_OB   min_OB   max_OB             */
/***************************************************/
short save_time_table(char *file, PTIME_AA times, int n_times)
{
  int i;
  FILE *fout;

  if (!file || !times || n_times <= 0)
    return ERR;

  fout = fopen(file, "w");
  if (!fout)
    return ERR;

  for (i = 0; i < n_times; i++)
  {
    fprintf(fout, "%d\t%.6f\t%.2f\t%d\t%d\n",
            times[i].N,
            times[i].time,
            times[i].average_ob,
            times[i].min_ob,
            times[i].max_ob);
  }

  fclose(fout);
  return OK;
}

short generate_search_times(pfunc_search method, pfunc_key_generator generator,
                            int order, char *file,
                            int num_min, int num_max,
                            int incr, int n_times)
{
  int i, n_results;
  PTIME_AA results = NULL;

  /* Comprobaciones de argumentos */
  assert(method != NULL);
  assert(generator != NULL);
  assert(file != NULL);
  assert(num_min >= 1);
  assert(num_max >= num_min);
  assert(incr >= 1);
  assert(n_times >= 1);

  /* Número de tamaños diferentes (N) que vamos a medir */
  n_results = ((num_max - num_min) / incr) + 1;

  results = (PTIME_AA)malloc(n_results * sizeof(TIME_AA));
  if (results == NULL)
  {
    return ERR;
  }

  /* Bucle de medidas para cada N */
  for (i = 0; i < n_results; i++)
  {
    int N = num_min + i * incr;

    if (average_search_time(method, generator, order,
                            N, n_times, &results[i]) == ERR)
    {
      free(results);
      return ERR;
    }
  }

  /* Guardar tabla */
  if (save_time_table(file, results, n_results) == ERR)
  {
    free(results);
    return ERR;
  }

  free(results);
  return OK;
}

short average_search_time(pfunc_search metodo, pfunc_key_generator generator,
                          int order,
                          int N,
                          int n_times,
                          PTIME_AA ptime)
{

  PDICT dict;
  int *perm = NULL;
  int *keys = NULL;
  int total_keys;
  int i, obs, pos, obs_total = 0;
  clock_t t_ini, t_fin;
  int min_ob, max_ob;

  assert(metodo != NULL);
  assert(generator != NULL);
  assert(N > 0);
  assert(n_times > 0);
  assert(ptime != NULL);
  
  dict = init_dictionary(N, order);
  if (dict == NULL)
  {
    return ERR;
  }
  
  perm = generate_perm(N);
  if (perm == NULL)
  {
    free_dictionary(dict);
    return ERR;
  }
  
  if (massive_insertion_dictionary(dict, perm, N) == ERR)
  {
    free_dictionary(dict);
    free(perm);
    return ERR;
  }
  
  total_keys = n_times * N;
  
  keys = malloc(total_keys * sizeof(int));
  if (keys == NULL)
  {
    free_dictionary(dict);
    free(perm);
    return ERR;
  }
  
  generator(keys, total_keys, N); /*Cambiar si eso a la otra en exercise2*/

  min_ob = INT_MAX
  max_ob = INT_MIN;
  t_ini = clock();
  for (i = 0; i < total_keys; i++)
  {
    obs = search_dictionary(dict, keys[i], &pos, metodo);
    if (obs == ERR)
    {
      free(keys);
      free(perm);
      free_dictionary(dict);
      return ERR;
    }
    obs_total += obs;

    if (max_ob < obs){
      max_ob = obs;
    }

    if (min_ob > obs){
      min_ob = obs;
    }
  }
  t_fin = clock();

  ptime->N = N;
  ptime->n_elems = total_keys;
  ptime->time = ((double)(t_fin - t_ini) / CLOCKS_PER_SEC) / total_keys;
  ptime->average_ob = (double)obs_total / (double)total_keys;
  ptime->min_ob = min_ob;
  ptime->max_ob = max_ob;

  /* 8. Liberar memoria */
  free(keys);
  free(perm);
  free_dictionary(dict);
  return OK;
}




