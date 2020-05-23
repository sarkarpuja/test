	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <string.h>
	#include <math.h>
	#include <unistd.h>
	#include <errno.h>
	#include<malloc.h>

	
	void initial_single_circular_profile( int radius,int *centre,double c, double *cc,int n);
	void write_file(double *conc,int n);
	void phi_matrix_diffuser(double *phi,int n, double d, int itrn);


	void main()
	{
	double *cc,*ptrcc,ci,c_large;
	int i,j,n,centre[2],radius;
	int p,q;
	n=100;
	ci=0.45;
	c_large=0.55;
	
	cc = (double *) malloc(n*n*sizeof(double));
		ptrcc=&cc[0];
		for(i=0;i<n*n;i++)
		{
			*ptrcc=ci;
			ptrcc++;
		}
	

	for(p=50;p<=90;)
	{
		for(q=50;q<99;)
		{
			centre[0]=p;
			centre[1]=q;
			radius=1;
		if((p==50)&&(q==50))
		{		
		initial_single_circular_profile(radius,centre,c_large,cc,n);
		}
	
		/*else if((p==90)&&(q==80))
		{		
		initial_single_circular_profile(radius,centre,c_low,cc,n);
		}*/
		
		else
		{
		initial_single_circular_profile(radius,centre,ci,cc,n);
		}
	
		
			
			q=q+15;
	      }
	      p=p+10;
	}
	double d=0.2;
	int itrn=10;
	phi_matrix_diffuser(cc,n,d,itrn);
	write_file(cc,n);

	}



	void initial_single_circular_profile( int radius,int *centre,double c, double *cc,int n)
	{
	
	int i,j,x,y;	
	double cij[n][n];
	int dist;
	
	double *ptrcc;
	ptrcc=&cc[0];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
		cij[i][j]=*ptrcc;
		ptrcc++;
		
		}


	}
	x=centre[0]-radius;
	y=centre[1]-radius;
	if(((centre[0]<0)||(centre[0]<radius))||((centre[1]<0)||(centre[1]<radius)))
	{
	printf("Unrealistic centre\n");
	exit(0);
	}
	else
	{
		
		for(i=(centre[0]-radius);i<=(centre[0]+radius);i++)
		{
			for(j=(centre[1]-radius);j<=(centre[1]+radius);j++)
			{
			dist=sqrt((i-centre[0])*(i-centre[0])+(j-centre[1])*(j-centre[1]));
				if(dist<=radius)
				{
				cij[i][j]=c;
				
				}
				
	
			}
		
			
		}
	
		
	}

	ptrcc=&cc[0];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
		*ptrcc=cij[i][j];
		ptrcc++;
		}


	}		
	}


	void phi_matrix_diffuser(double *phi,int n, double d, int itrn)
	{
	double *bphi,*ptrphi,*ptrbphi;
	int i,j,k,*ptr,l,lm,counter;
	bphi = (double *) malloc(n*n*sizeof(double));
	
	//copying values
		ptrphi=&phi[0];ptrbphi=&bphi[0];
		for(i=0;i<n*n;i++)
		{
			*ptrbphi=*ptrphi;
		         ptrphi++;ptrbphi++; 	
		}
		
	for(k=0;k<itrn;k++)
	{
		
	
				
		//diffusing
		ptrphi=&phi[0];ptrbphi=&bphi[0];
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
			
				if((i==n-1)&&((j!=0)&&(j!=n-1)))
				{
				*ptrbphi=*ptrphi+d*(*(ptrphi+1)+*(ptrphi-1)+2**(ptrphi-n)-4**ptrphi);
				}
				else if((i==0)&&((j!=0)&&(j!=n-1)))
				{
				*ptrbphi=*ptrphi+d*(*(ptrphi+1)+*(ptrphi-1)+2**(ptrphi+n)-4**ptrphi);
				}
				else if((j==0)&&((i!=0)&&(i!=n-1)))
				{
				*ptrbphi=*ptrphi+d*(2**(ptrphi+1)+*(ptrphi+n)+*(ptrphi-n)-4**ptrphi);
				}
				else if((j==n-1)&&((i!=0)&&(i!=n-1)))
				{
				*ptrbphi=*ptrphi+d*(2**(ptrphi-1)+*(ptrphi+n)+*(ptrphi-n)-4**ptrphi);
				}
				else if((i==0)&&(j==0))
				{
				*ptrbphi=*ptrphi+d*(2**(ptrphi+1)+2**(ptrphi+n)-4**ptrphi);
				}
				else if((i==n-1)&&(j==0))
				{
				*ptrbphi=*ptrphi+d*(2**(ptrphi+1)+2**(ptrphi-n)-4**ptrphi);
				}
				else if((i==n-1)&&(j==n-1))
				{
				*ptrbphi=*ptrphi+d*(2**(ptrphi-1)+2**(ptrphi-n)-4**ptrphi);
				}
				else if((i==0)&&(j==n-1))
				{
				*ptrbphi=*ptrphi+d*(2**(ptrphi-1)+2**(ptrphi+n)-4**ptrphi);
				}
				else
				{	
				
				*ptrbphi=*ptrphi+d*(*(ptrphi+1)+*(ptrphi-1)+*(ptrphi+n)+*(ptrphi-n)-4**ptrphi);
				}
			ptrphi++;ptrbphi++;
			}
			
		}
		
		//copying values
		ptrphi=&phi[0];ptrbphi=&bphi[0];
		for(i=0;i<n*n;i++)
		{
			*ptrphi=*ptrbphi;
		         ptrphi++;ptrbphi++; 	
		}	
	
	}
	
	
	}

	
	

	void write_file(double *conc,int n)
	{
	FILE *fp;
	double *ptrconc;
	int i,j;
	fp=fopen("concentration3_0.txt","w");
	ptrconc=&conc[0];
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
			
			fprintf(fp,"%d\t%d\t%e\n",i,j,*ptrconc);
			//fprintf(fp,"%e\t",*ptrconc);
			ptrconc++;
		

			}
			fprintf(fp,"\n");
		}
	fclose(fp);
	
	}

