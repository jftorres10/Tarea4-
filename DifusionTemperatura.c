#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initial_condition(double Ti, double nx, double *T,double dx,double *x, double *y, double T2,double *T_future);
void cond_fijas(double nx, double *T,double *T_future, double alpha, double tf, double dt,double *x ,double *y,int caso,char filename[100], char filename2[100]);
void cond_periodicas(double nx, double *T,double *T_future, double alpha, double tf, double dt,double *x ,double *y,int caso,char filename[100], char filename2[100]);
void cond_abiertas(double nx, double *T,double *T_future, double alpha, double tf, double dt,double *x ,double *y,int caso,char filename[100], char filename2[100]);
double Calcular_Promedio(double *T, double NX );
int main(){


double v=0.0001;
int i;
double Ti=50.0;
double T2=100.0;
double Tcentro =1000;
double  l = 1;
double dx = 0.05;
double nx = (l/dx)+1;
double alpha= 0.1;
double dt=((dx*dx)/v)*alpha;
double tf = 2510.0;
 


double *x = malloc(nx*nx*sizeof(double));
double *y = malloc(nx*nx*sizeof(double));
double *T = malloc(nx*nx*sizeof(double));
double *T_future= malloc(nx*nx*sizeof(double));

initial_condition(Ti,  nx, T,dx, x, y, T2,T_future);



for(i=0;i<nx*nx;i++)
{
	printf("%f %f %f\n",x[i],y[i],T[i]);
}

cond_fijas(nx,T,T_future, alpha,tf, dt,x,y,1, "C1_fijas_Tprom.dat","C1_fijas_x_y_T.dat");



initial_condition(Ti,  nx, T,dx, x, y, T2,T_future);
cond_abiertas(nx, T, T_future, alpha, tf, dt, x , y,1, "C1_abiertas_Tprom.dat","C1_abiertas_x_y_T.dat");

initial_condition(Ti,  nx, T,dx, x, y, T2,T_future);
cond_fijas(nx,T,T_future, alpha,tf, dt,x,y,2,"C2_fijas_Tprom.dat","C2_fijas_x_y_T.dat");

initial_condition(Ti,  nx, T,dx, x, y, T2,T_future);
cond_periodicas(nx, T, T_future, alpha, tf, dt, x , y,2, "C2_periodicas_Tprom.dat","C2_periodicas_x_y_T.dat");

initial_condition(Ti,  nx, T,dx, x, y, T2,T_future);
cond_abiertas(nx, T, T_future, alpha, tf, dt, x , y,2, "C2_abiertas_Tprom.dat","C2_abiertas_x_y_T.dat");

initial_condition(Ti,  nx, T,dx, x, y, T2,T_future);
cond_periodicas(nx, T, T_future, alpha, tf, dt, x , y,1, "C1_periodicas_Tprom.dat","C1_periodicas_x_y_T.dat");
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
	if(x[i]>=0.2 && x[i]<=0.40 && y[i]>=0.45 && y[i]<=0.55)
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
void cond_fijas(double nx, double *T,double *T_future, double alpha, double tf, double dt,double *x ,double *y,int caso, char filename[100], char filename2[100])
{
	FILE *in;
/* 
char filename[100]= "C1_fijas_Tprom.dat";*/
in = fopen(filename,"w");

	FILE *in2;
/*char filename2[100]= "C1_fijas_x_y_T.dat";*/
in2 = fopen(filename2,"w");

	int i;
	int j;
	int k;
	double T2=100.0;
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
	/* si es el caso 2 matener la temperatura del cuadrad del centro en 100 c */
if(caso == 2)
{
for(i=0;i<nx*nx;i++)
	{
	if(x[i]>=0.2 && x[i]<=0.40 && y[i]>=0.45 && y[i]<=0.55)
	{
		T_future[i] = T2;
	}		
}
}
	T_prom = Calcular_Promedio(T,nx*nx);
 	fprintf(in,"%f %f \n",k*dt,T_prom);

	if(abs(k*dt-0)<=dt/2 || abs(k*dt-100)<=dt/2 || abs(k*dt-2500)<=dt/2)
	{
	fprintf(in2, "Tiempo %f \n",k*dt );
	for(i=0;i<nx*nx;i++)	
		{
		fprintf(in2,"%f %f %f \n",x[i],y[i],T[i]);	
		}
	}

}
}





void cond_periodicas(double nx, double *T,double *T_future, double alpha, double tf, double dt,double *x ,double *y,int caso,char filename[100], char filename2[100])
{
	FILE *in;

in = fopen(filename,"w");

	FILE *in2;

in2 = fopen(filename2,"w");


	int i;
	int j;
	int k;
	double T2=100.0;
	double nt = tf/dt;
	double T_prom = 0.0;
	
	FILE *gif;

gif = fopen("animacion.dat","w");

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
	if(y[i]==0.0)
	{
/* Calcular el valor de la temperatura del siguiente tiempo con la ecuacion de diferencias finitas para difusion*/
/* para cada if verificamos las fronteras periodicas , que se trata espeficicamente para cada punto de interes*/
        T_future[i]=T[i]+ alpha*(T[i-1]-4*T[i]+T[i+1]+T[i+(int)nx]+T[i+((int)(nx*nx)-(int)nx)]); 
	}
	else if(x[i]==0.0)
	{
	T_future[i]=T[i]+ alpha*(T[i+(int)nx-1]-4*T[i]+T[i+1]+T[i+(int)nx]+T[i-(int)nx]);	
	}
	else if(x[i]==1.0)
	{
	T_future[i]=T[i]+ alpha*(T[i-1]-4*T[i]+T[i-(int)nx+1]+T[i+(int)nx]+T[i-(int)nx]);
	}
	else if(y[i]==1.0)
	{
	T_future[i]=T[i]+ alpha*(T[i-1]-4*T[i]+T[i+1]+T[i-((int)(nx*nx)-(int)nx)]+T[i-(int)nx]);	
	}
	else
	{
	T_future[i]=T[i]+ alpha*(T[i-1]-4*T[i]+T[i+1]+T[i+(int)nx]+T[i-(int)nx]); 	
	}
	}
	/* si es el caso 2 matener la temperatura del cuadrad del centro en 100 c */
if(caso == 2)
{
for(i=0;i<nx*nx;i++)
	{
	if(x[i]>=0.2 && x[i]<=0.40 && y[i]>=0.45 && y[i]<=0.55)
	{
		T_future[i] = T2;
	}		
}
}	
 if(caso==1)
	{
	for(i=0;i<nx*nx;i++)	
		{
		fprintf(gif,"%f %f %f \n",x[i],y[i],T[i]);	
		}
	}	
		
	
	T_prom = Calcular_Promedio(T,nx*nx);
 	fprintf(in,"%f %f \n",k*dt,T_prom);

	if(abs(k*dt-0)<=dt/2 || abs(k*dt-100)<=dt/2 || abs(k*dt-2500)<=dt/2)
	{
	fprintf(in2, "Tiempo %f \n",k*dt );
	for(i=0;i<nx*nx;i++)	
		{
		fprintf(in2,"%f %f %f \n",x[i],y[i],T[i]);	
		}
	}

}
}


double Calcular_Promedio(double *T, double NX )
{ 	
	double T_prom = 0.0;
	int i =0;

	for(i=0;i<NX;i++)
	{
	T_prom = T_prom + T[i];
	} 	
	T_prom = T_prom/NX;
return T_prom;	
	
}

void cond_abiertas(double nx, double *T,double *T_future, double alpha, double tf, double dt,double *x ,double *y,int caso,char filename[100], char filename2[100])
{
	FILE *in;

in = fopen(filename,"w");

	FILE *in2;

in2 = fopen(filename2,"w");


	int i;
	int j;
	int k;
	double T2=100.0;
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
	if(y[i]==0.0)
	{
/* Calcular el valor de la temperatura del siguiente tiempo con la ecuacion de diferencias finitas para difusion*/
/* para cada uno de las fronteras miramos que la derivada sea 0. */
        T_future[i]=T[i+(int)nx]; 
	}
	else if(x[i]==0.0)
	{
	T_future[i]=T[i+1];	
	}
	else if(x[i]==1.0)
	{
	T_future[i]=T[i-1];
	}
	else if(y[i]==1.0)
	{
	T_future[i]=T[i-(int)nx];	
	}
	else
	{
	T_future[i]=T[i]+ alpha*(T[i-1]-4*T[i]+T[i+1]+T[i+(int)nx]+T[i-(int)nx]); 	
	}
	}
	/* si es el caso 2 matener la temperatura del cuadrad del centro en 100 c */
if(caso == 2)
{
for(i=0;i<nx*nx;i++)
	{
	if(x[i]>=0.2 && x[i]<=0.40 && y[i]>=0.45 && y[i]<=0.55)
	{
		T_future[i] = T2;
	}		
}
}	
 
	T_prom = Calcular_Promedio(T,nx*nx);
 	fprintf(in,"%f %f \n",k*dt,T_prom);

	if(abs(k*dt-0)<=dt/2 || abs(k*dt-100)<=dt/2 || abs(k*dt-2500)<=dt/2)
	{
	fprintf(in2, "Tiempo %f \n",k*dt );
	for(i=0;i<nx*nx;i++)	
		{
		fprintf(in2,"%f %f %f \n",x[i],y[i],T[i]);	
		}
	}

}
}








	




