#include <math.h>
#include <stdio.h>

const int n = 100;

double get_error(double *x, double *x_final) {
    double max = 0;
    int i;
    for(i = 0; i < n; i++) {
	double error = fabs(x[i] - x_final[i]);
	if(error > max) {
	    max = error;
	}
    }
    return max;
}

int main(int argc, char **argv) {
    const double PI = 3.14159265;
    const int index = 2;
    const int max_iter = 1000;
    const double alpha = 2;
    double errors[max_iter];
    double T[n][n];
    double b[n];
    double x[n];
    double x_old[n];
    double x_final[n];
    double h = 2*(1-cos(index*PI/(n+1)));
    int i, j, k, step;
    for(i = 0; i < n; i++) {
	b[i] = h*sin((i+1)*index*PI/(n+1));
	x[i] = 0;
	x_final[i] = sin((i+1)*index*PI/(n+1));
	for(j = 0; j < n; j++) {
	    T[i][j] = 0;
	}
	if(i == 0) {
	    T[i][0] = alpha;
	    T[i][1] = -1;
	}
	else if(i == n-1) {
	    T[i][n-2] = -1;
	    T[i][n-1] = alpha;
	}
	else {
	    T[i][i-1] = -1;
	    T[i][i] = alpha;
	    T[i][i+1] = -1;
	}
    }
    for(step = 0; step < max_iter; step++) {
	for(i = 0; i < n; i++) {
	    x_old[i] = x[i];
	}
	for(i = 0; i < n; i++) {
	    double sum = 0;
	    for(j = 0; j < n; j++) {
		sum += T[i][j]*x_old[j];
	    }
	    sum -= T[i][i]*x_old[i];
	    x[i] = (b[i] - sum)/T[i][i];
	}
	errors[step] = get_error(x, x_final);
    }
    FILE *file = fopen("jacobi_output.csv", "w");
    for(step = 0; step < max_iter; step++) {
	fprintf(file, "%f\n", errors[step]);
    }
    fclose(file);
}
