#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../../lib/headers/generators.h"

int main(int argc, char const *argv[])
{
    int NTHREADS = omp_get_num_procs() / 2;

    int i, hi, sub_hi;

    int *v = (int *)malloc(SIZE * sizeof(int));
    gen_vector_int(v, 0, 999);

    // Parallel
    double t_start = omp_get_wtime();

    hi = v[0];
    for (i = 1; i < SIZE; i++)
    {
        if (v[i] > hi)
        {
            hi = v[i];
        }
    }

    double t_serial = omp_get_wtime() - t_start;

    printf("\n     serial\n");
    printf("hi: %d\n", hi);

    // Parallel
    t_start = omp_get_wtime();

    hi = v[0];
    sub_hi = v[0];
#pragma omp parallel num_threads(NTHREADS) firstprivate(sub_hi)
    {
#pragma omp for
        for (i = 1; i < SIZE; i++)
        {
            if (v[i] > sub_hi)
            {
                sub_hi = v[i];
            }
        }
#pragma omp critical
        if (sub_hi > hi)
        {
            hi = sub_hi;
        }
    }

    double t_parallel = omp_get_wtime() - t_start;

    printf("\n    critical\n");
    printf("hi: %d\n", hi);

    printf("\n");
    statistic_log("analysis", 8, t_parallel, t_serial, NTHREADS);
}
