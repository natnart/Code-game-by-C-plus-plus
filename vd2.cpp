#include <stdio.h>
#include <string.h>
#include <conio.h>
 
 struct Sinhvien {
	char mssv[10];
	char hoten[32];
	int sotc;
	float diem;
	float diemtl;
	
 };

void docfile (Sinhvien sv[],int *n)
{
	int i=0; char t[100];
	FILE *f=fopen ("diemthi.txt","r+");
	if (f!=NULL)
	while (!feof(f)){
		fgets (sv[i].mssv,10,f);
		fgets (sv[i].hoten,32,f);
		fscanf (f,"%d %f",&sv[i].sotc,&sv[i].diem);
		//fscanf (f,"%2d",&sv[i].sotc);
		//fgets (t,2,f);
		//fscanf (f,"%f",&sv[i].diem);
		sv[i].diemtl=sv[i].diem*sv[i].sotc;
		fgets (t,100,f);
		i++;
	}
	*n=i;
	fclose (f);
	
	getch ();
	
}

void inds (Sinhvien sv[],int n)
{
	printf ("+STT+--MSSV---+--HOTEN------------------------+sotc+diem+\n");
	
	
	
	for (int i=0;i<n;i++)
	{

		printf ("|%3d|%-9s|%-31s|%-4d|%4.1f|\n",i+1,sv[i].mssv,sv[i].hoten,sv[i].sotc,sv[i].diem);
			printf ("+---+---------+-------------------------------+----+----+\n");
			
	}
	
}


void xoasv (Sinhvien sv[],int *n,int x)
{
	for (int i=x;i<*n-1;i++)
	{
		sv[i]=sv[i+1];
		
	}
		
	*n--;
}

void tonghop (Sinhvien sv[],int *n)
{
	for (int i=0;i<*n-1;i++)
		for (int j=i+1;j<*n;j++)
		{
			if (strcmp (sv[i].mssv,sv[j].mssv)==0)
			{
				sv[i].sotc+=sv[j].sotc;
				sv[i].diem+=sv[j].diem;
				sv[i].diemtl+=sv[j].diemtl;
				xoasv (sv,&*n,j);
			}
		}
	
	printf ("+STT+--MSSV---+--HOTEN------------------------+sotc+diemtl+\n");
	for (int i=0;i<*n;i++)
	{
		printf ("|%3d|%-9s|%-31s|%-4d|%6.1f|\n",i+1,sv[i].mssv,sv[i].hoten,sv[i].sotc,sv[i].diemtl/sv[i].sotc);
		printf ("+---+---------+-------------------------------+----+------+\n");
		
	}
		
	
}


int main ()
{
	int n; 
	Sinhvien sv[50];
	docfile (sv,&n);
	inds (sv,n);
	printf ("\n\ndanh sach sau khi tong hop : (an phim bat ky de tiep tuc)\n");
	getch ();
	tonghop (sv,&n);
	getch ();


}

