#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initial_condition(double Ti, double nx, double *T,double dx,double *x, double *y, double T2,double *T_future);
void cond_fijas(double nx, double *T,double *T_future, double alpha, double tf, double dt,double *x ,double *y);
int main(){


double v=0.0001;
int i;
double Ti=50.0;
double T2=100.0;
double Tcentro =1000;
double  l = 1;
double dx = 0.1;
double nx = (l/dx)+1;
double alpha= 0.1;
double dt=((dx*dx)/v)*alpha;
double tf = 2500.0;
 


double *x = malloc(nx*nx*sizeof(double));
double *y = malloc(nx*nx*sizeof(double));
double *T = malloc(nx*nx*sizeof(double));
double *T_future= malloc(nx*nx*sizeof(double));

initial_condition(Ti,  nx, T,dx, x, y, T2,T_future);



for(i=0;i<nx*nx;i++)
{
	printf("%f %f %f\n",x[i],y[i],T[i]);
}

cond_fijas(nx,T,T_future, alpha,tf, dt,x,y);


return 0;
}

void initial_condition(double Ti, double nx, double *T,double dx,double *x,double *y, double T2, double *T_future)
{
	
	int i;
	int j;
	int k;

	

	for(i=0;i<nx;i++)
	{		
		for(j=0;j<nx;j++)
		{
			k = nx*i + j;
			printf("%d \n",k); 
			x[k]=dx*j;
			y[k]=i*dx;
	
		}
	}

	for(i=0;i<nx*nx;i++)
	{
	if(x[i]<=0.2 && y[i]>=0.45 && y[i]<=0.55)
	{


		T[i] = T2;
		T_future[i] = T2;
	}	
	else
	{
	T[i] = Ti;
	T_future[i] = Ti;
	}	
		
	}

	
}
void cond_fijas(double nx, double *T,double *T_future, double alpha, double tf, double dt,double *x ,double *y)
{
	FILE *in;
char filename[100]= "Cond_fijas_Tprom.dat";
in = fopen(filename,"w");
	int i;
	int j;
	int k;
	double nt = tf/dt;
	double T_prom = 0.0;
/* Utilizamos recorrido en el tiempo para la difusion*/
for(k=0;k<nt;k++)
{
 for(i=0;i<nx*nx;i++) 
	{
/* mis valores futuros se convierte en los del presente para seguir iternado*/ 
	T[i]=T_future[i];	

	}					
	for(i=0;i<nx*nx;i++)
	{
	if(x[i]>0 && x[i]<1.0 && y[i]>0 && y[i]<1.0)
	{
/* Calcular el valor de la temperatura del siguiente tiempo con la ecuacion de diferencias finitas para difusion*/
        T_future[i]=T[i]+ alpha*(T[i-1]-4*T[i]+T[i+1]+T[i+(int)nx]+T[i-(int)nx]); 
	}
	
	}		
/* if(K*dt=0.0 || k*dt = 100 || k*dt=25000) */
 
	
	T_prom = 0.0;
	
	for(i=0;i<nx*nx;i++)
	{
	T_prom = T_prom + T[i];
	} 	
	T_prom = T_prom/(nx*nx);
	
	fprintf(in,"%f %f \n",k*dt,T_prom);
	
	

}
	
}



