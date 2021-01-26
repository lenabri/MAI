#include <stdio.h>

typedef struct {
	double re, im;
} complex;

complex makeComplex(double re, double im) {
	complex c;
	c.re = re;
	c.im = im;
	return c;
}

complex sum(complex a, complex b) {
	complex c;
	c.re = a.re + b.re;
	c.im = a.im + b.im;
	return c;
}

complex substract(complex a, complex b) {
	complex c;
	c.re = a.re - b.re;
	c.im = a.im - b.im;
	return c;
}

complex mult(complex a, complex b) {
	complex c;
	c.re = a.re * b.re - a.im * b.im;
	c.im = a.im * b.re + a.re * b.im;
	return c;
}

complex mult(complex a, double b) {
	complex c;
	c.re = a.re * b;
	c.im = a.im * b;
	return c;
}

complex divide(complex a, complex b) {
	complex tmp = b;
	tmp.im *= -1;
	complex c = mult(a, tmp);
	double znam = b.re * b.re + b.im * b.im;
	c.re /= znam;
	c.im /= znam;
	return c;
}

typedef union {
	int integer;
	complex comp;
} vectorDataType;

// use as dataType for vector

int main() {

}