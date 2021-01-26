#include <stdio.h>
#include <math.h>

const double eps = 0.0000001; 

double DelP(double f(double), double a,double b)
{
	double c;
	while(fabs(a-b)>eps)
	{
		c=(a+b)/2;
		if (f(a)*f(c)>0) a=c; 
		else b=c;
	}
	return c;
}


double Iter(double F(double), double a,double b)
{
	double x=(a+b)/2;
	while (fabs(x-F(x))>eps)
	{
		
		x=F(x);
	}
	return x;
}



double Newton(double f(double), double p(double), double a,double b)
{
	double x=(a+b)/2;
	while (fabs(f(x)/p(x))>eps)
	{
		
		x=x-f(x)/p(x);
		}
		return x;
	}
		
		
		
		
double Hord(double f(double), double a,double b)
{

	while (fabs(a-b)>eps)
	{
		
		a=b-(b-a)*f(b)/(f(b)-f(a));
		b=a-(a-b)*f(a)/(f(a)-f(b));
	
	}
	return a;
}
		

double f1(double x) {return sinh(x)-1;}
double f2(double x) {return sin(log(x))-cos(log(x))+2*log(x);}
double f3(double x) {return x-2+sin(pow(x,-1));}

double F1(double x) {return asinh(1);}
double F2(double x) {return exp((cos(log(x))-sin(log(x)))/2);}
double F3(double x) {return 2 -sin(pow(x,-1));}

double p1(double x) {return 2*cosh(x);}
double p2(double x) {return cos(log(x))*pow(x,-1)+sin(log(x))*pow(x,-1)+2*pow(x,-1);}
double p3(double x) {return 1-pow(x,-2)*cos(pow(x,-1));}

int main()
{
	printf("Корень функции f1 метод деления пополам = %.4f\n", DelP(f1,0,1));
	printf("Корень функции f1 метод итерации = %.4f\n", Iter(F1,0,1));
    printf("Корень функции f1 метод Ньютона = %.4f\n", Newton(f1,p1,0,1));
	printf("Корень функции f1 метод хорд = %.4f\n", Hord(f1,0,1));
	printf("Корень функции f2 метод деления пополам = %.4f\n", DelP(f2,1,3));
	printf("Корень функции f2 метод итерации = %.4f\n", Iter(F2,1,3));
	printf("Корень функции f2 метод Ньютона = %.4f\n", Newton(f2,p2,1,3));
	printf("Корень функции f2 метод хорд = %.4f\n", Hord(f2,1,3));
	printf("Корень функции f3 метод деления пополам = %.4f\n", DelP(f3,1.2,2));
	printf("Корень функции f3 метод итерации = %.4f\n", Iter(F3,1.2,2));
	printf("Корень функции f3 метод Ньютона = %.4f\n", Newton(f3,p3,1.2,2));
	printf("Корень функции f3 метод хорд = %.4f\n", Hord(f3,1.2,2));
	return 0;

}
//printf("Корень функции f1 метод Ньютона = %3lf\n", Newton(f1,p1,0.,1.));
