#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>



double f(double x, double y, double z) {
    return (4*pow(x, 3) + x*pow(y,2) + 5*y + 6*z);
}

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void monte_carlo(double *lo, double *hi, long N, double *result) {
    double sum = 0.0, square_sum = 0.0, average, square_average, rms;

    for (long i=0 ; i<N ; i++) {
        double rand_f = f(randfrom(lo[0], hi[0]), randfrom(lo[1], hi[1]), randfrom(lo[2], hi[2]));
        sum += rand_f;
        square_sum += rand_f*rand_f; 
    }

    average = sum/N;
    square_average = square_sum/N;
    rms = sqrt(square_average - average*average)/N;

    double V = (hi[0] - lo[0]) * (hi[1] - lo[1]) * (hi[2] - lo[2]);

    result[0] = average*V;
    result[1] = rms*V;

}

int main(int argc, char ** argv) {
    srand (time ( NULL));

    long N = 10;
    if (argc >= 2) {
        N = strtol(argv[1], NULL, 10);
        printf("Using %ld points \n", N);
    }
    else {
        printf("Defaulting to 10 points \n");
    }

    double lo[] = {0.0, 0.0, 0.0};
    double hi[] = {4.0, 3.0, 2.0};

    double result[2];
    monte_carlo(lo, hi, N, result);

    printf("Monte Carlo result: %f +- %f \n", result[0], result[1]);

}