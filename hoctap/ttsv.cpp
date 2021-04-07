#include <stdio.h>

struct Sinhvien {
	char mssv[10];
	char hoten[25];
	char ngaysinh[11];
	char quequan[20];
	float diemtl;
	
	
};

void nhapluutt (Sinhvien sv[],int *n)
{
	FILE *f;
	printf ("nhap so luong sinh vien: ");
	scanf ("%d",n);
	fflush (stdin);
	f=fopen("Sinhvien.txt","wb");
	if (f!=NULL)
	for (int i=0;i<*n;i++)
	{
		printf("\tnhap thong tin sinh vien thu %d :\n", i+1);
		printf ("mssv: ");
		gets (sv[i].mssv);
		fputs (sv[i].mssv,f);
		printf ("hoten: ");
		gets (sv[i].hoten);
		fputs (sv[i].hoten,f);
		printf ("ngaysinh: ");
		gets (sv[i].ngaysinh);
		fputs (sv[i].ngaysinh,f);
		printf ("que quan: ");
		gets (sv[i].quequan);
		fputs (sv[i].quequan,f);
		printf ("diem tich luy: ");
		scanf ("%f",&sv[i].diemtl);
		fprintf (f,"%f",sv[i].diemtl);
		fputc ('\n',f);
		
	}
	fclose (f);
	
	
}


int main ()
{
	Sinhvien sv[50]; int n;
	nhapluutt (sv,&n);
	
	
	
}


