#include <stdio.h>
#include <math.h>
#include "omp.h"

double f(double x, double y, double z) {
    return (4*pow(x, 3) + x*pow(y,2) + 5*y + 6*z);
}


double reinmann_integral(double *limits_lo, double *limits_hi, int *partition) {
    double jumps[3];
    double final_value = 0.0;


    for (int i=0 ; i<3 ; i++) {
        jumps[i] = (limits_hi[i] - limits_lo[i])/(double) partition[i];

    }

    double delta_v = jumps[0]*jumps[1]*jumps[2];

#pragma omp parallel 
{
    #pragma omp for collapse(3) reduction(+: final_value) 
    for (int i = 0; i < partition[0]; i++) {
        for (int j = 0; j < partition[1]; j++) {
            for (int k = 0; k < partition[2]; k++) {
                double x = limits_lo[0] + i * jumps[0]; 
                double y = limits_lo[1] + j * jumps[1];
                double z = limits_lo[2] + k * jumps[2];
                
                final_value += f(x, y, z) * delta_v;
            }
        }
    }
    

}


    return final_value;

}

int main(int argc, char **argv) {
    double lo[] = {0.0, 0.0, 0.0};
    double hi[] = {4.0, 3.0, 2.0};
    int parts[] = {48, 36, 24};
    int n = 1;

    

    if (argc >= 2) {
        n = strtol(argv[1], NULL, 10);
    }
    else {
        printf("Number of threads not mentioned as argument. Defaulting to serial execution");
    }

    printf("Setting number of threads as %d \n", n);
    omp_set_num_threads(n);

    printf("Reimann Integral Value: %f", reinmann_integral(lo, hi, parts));

}