#include <stdio.h>
#include <stdlib.h>


#include "lib/imp1/sin_integral.h"
#include "lib/imp1/derivative.h"


int main() {
	int n;
	float par1, par2, par3;
	while (scanf("%d", &n) != EOF) {
		if (n == 1) {
			if (scanf("%f %f %f", &par1, &par2, &par3) < 3) {
				fprintf(stderr, "Invalid parameters\n");
				exit(1);
			}
			printf("%f\n", SinIntegral(par1, par2, par3));
		} else if (n == 2) {
			if (scanf("%f %f", &par1, &par2) < 2) {
				fprintf(stderr, "Invalid parameters\n");
				exit(2);
			}
 			printf("%f\n", Derivative(par1, par2));
		} else {
			fprintf(stderr, "Invalid command\n");
			exit(3);
		}
	}
	return 0;
}

