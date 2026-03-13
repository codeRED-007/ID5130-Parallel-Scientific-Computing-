#include <stdio.h>
#include <math.h>

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

    for (int i = 0; i < partition[0]; i++) {
        double x = limits_lo[0] + i * jumps[0]; 
        
        for (int j = 0; j < partition[1]; j++) {
            double y = limits_lo[1] + j * jumps[1];
            
            for (int k = 0; k < partition[2]; k++) {
                double z = limits_lo[2] + k * jumps[2];
                
                final_value += f(x, y, z) * delta_v;
            }
        }
    }


    return final_value;

}
int main() {
    double lo[] = {0.0, 0.0, 0.0};
    double hi[] = {4.0, 3.0, 2.0};
    int parts[] = {48, 36, 24};

    printf("Reimann Integral Value: %f", reinmann_integral(lo, hi, parts));
}