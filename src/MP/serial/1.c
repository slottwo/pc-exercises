#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../lib/headers/generators.h"

/* Dado um vetor com 5e8 de elementos aleatórios, escrever um programa que faça
 * uma busca por um valor N (0.3578)
 */

int main(int argc, char const *argv[])
{
    double *v = (double *)malloc(SIZE * sizeof(double));
    gen_vector_zto(v);

    int index_of_target = -1;
    double target = 0.3578; // N

    double t_start = omp_get_wtime();

    for (int i = 0; i < SIZE; i++)
    {
        if (v[i] == target)
        {
            index_of_target = i;
            break;
        }
    }

    printf("t: %.5fs\n", omp_get_wtime() - t_start);

    printf("i: %d\n", index_of_target);

    return 0;
}
