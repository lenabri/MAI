#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>


#define LIBINT1 "./lib/imp1/libint.so"
#define LIBDER1 "./lib/imp1/libder.so"
#define LIBINT2 "./lib/imp2/libint.so"
#define LIBDER2 "./lib/imp2/libder.so"


int main() {
	int lib = 1;
	void *handle1 = dlopen(LIBINT1, RTLD_LAZY);
	void *handle2 = dlopen(LIBDER1, RTLD_LAZY);
    
	if (dlerror()) {
		fprintf(stderr, "dlopen error\n");
		exit(1);
	}

	int n;
	float par1, par2, par3;

	while (scanf("%d", &n) == 1) {
		if (n == 0) {
			if (lib == 1) {
				lib = 2;
				handle1 = dlopen(LIBINT2, RTLD_LAZY);
				handle2 = dlopen(LIBDER2, RTLD_LAZY);
			} else {
				lib = 1;
				handle1 = dlopen(LIBINT1, RTLD_LAZY);
				handle2 = dlopen(LIBDER1, RTLD_LAZY);
			}

			if (dlerror()) {
				fprintf(stderr, "dlopen");
				exit(2);
			}

			printf("Library has successfully changed\n");
		} else if (n == 1) {
			if (scanf("%f %f %f", &par1, &par2, &par3) != 3) {
				fprintf(stderr, "Invalid parameters");
				exit(3);
			}

			float (*SinIntegral) (float, float, float);
			SinIntegral = dlsym(handle1, "SinIntegral");
			if (SinIntegral == NULL) {
				fprintf(stderr, "dlsym error\n");
				exit(4);
			}

			printf("Result = %f\n", SinIntegral(par1, par2, par3));	    
		} else if (n == 2) {
			if (scanf("%f %f", &par1, &par2) != 2) {
				fprintf(stderr, "Invalid parameters");
				exit(5);
			}
			
			float (*Derivative) (float, float);
			Derivative = dlsym(handle2, "Derivative");
			if (Derivative == NULL) {
				fprintf(stderr, "dlsym error\n");
				exit(6);
			}
			
			printf("Result = %f\n", Derivative(par1, par2));
			} else {
				fprintf(stderr, "Invalid command\n");
			}
	}

	dlclose(handle1);
	dlclose(handle2);

	if (dlerror()) {
		fprintf(stderr, "dlclose error\n");
		exit(7);
	}
	return 0;
}
