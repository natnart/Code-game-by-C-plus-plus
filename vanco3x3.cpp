#include <stdio.h>
#include <conio.h>
#include <windows.h>
int a[10];

void danh (int vtri, int man)
{
	if (man==1) a[vtri]=1;
	if (man==0) a[vtri]=-10;
}

struct tt
	{
		int x;
		int y;
		int z;
		int tong;
	};
	
void kt_kq (tt t[])
{
	for (int i=1;i<=8;i++)
	{
		if (t[i].tong== -30) {printf ("\n\t\t\tban da thua");
		}
		if (t[i].tong== 3) {printf ("\n\t\t\tban da thang");
		}
	}
}

void hien_thi (int a[])
{
	char ht[10];
	for (int i=1;i<=9;i++)
	{
		if (a[i]==1) ht[i]='o';
		if (a[i]==-10) ht[i]='x';
		if (a[i]==0) ht[i]=' ';
	}
	printf ("\n%c%c%c%c%c%c%c\n",218,196,194,196,194,196,191); 
	printf ("%c%c%c%c%c%c%c\n",179,ht[1],179,ht[2],179,ht[3],179); 
	printf ("%c%c%c%c%c%c%c\n",195,196,197,196,197,196,180); 
	printf ("%c%c%c%c%c%c%c\n",179,ht[4],179,ht[5],179,ht[6],179);
	printf ("%c%c%c%c%c%c%c\n",195,196,197,196,197,196,180);
	printf ("%c%c%c%c%c%c%c\n",179,ht[7],179,ht[8],179,ht[9],179);
	printf ("%c%c%c%c%c%c%c\n",192,196,193,196,193,196,217); 
}

int kt (tt t[], int a[],int i, int j)
	{
		int x=t[j].x;
		int y=t[j].y;
		int z=t[j].z;
	if (t[i].x==x||t[i].x==y||t[i].x==z) return t[i].x;
	if (t[i].y==x||t[i].y==y||t[i].y==z) return t[i].y;
	if (t[i].z==x||t[i].z==y||t[i].z==z) return t[i].z;
		return 0;
	}

void chon_danh (tt t[],int i, int a[])
{
	if (a[t[i].x]==0) {danh(t[i].x,0); return;}
	if (a[t[i].y]==0) {danh(t[i].y,0); return;}
	if (a[t[i].z]==0) {danh(t[i].z,0); return;}
}

void gan (tt t[],int i,int a[], int x, int y, int z)
{
	t[i].x=x; t[i].y=y; t[i].z=z;
}


int tong_hang (int a[], int x, int y, int z)
{
	int t=0;
	return t=a[x]+a[y]+a[z];
	
}



int main ()
{
	tt t[10]; int kthuc; int vtri;int kqua=0; int tam=0;
	int da_danh=0;

	for (int i=1;i<=9;i++)
	{
		a[i]=0;
	}
	
	gan	(t,1,a,1,2,3);
	gan (t,2,a,4,5,6);
	gan (t,3,a,7,8,9);
	gan (t,4,a,1,4,7);
	gan (t,5,a,2,5,8);
	gan (t,6,a,3,6,9);
	gan (t,7,a,1,5,9);
	gan (t,8,a,3,5,7);	
	
	while (kthuc==0)
	{
		
		hien_thi (a);
		kt_kq (t);
		da_danh=0;
		printf ("\nBan danh o vi tri nao: "); scanf ("%d",&vtri);
		danh (vtri,1);
		hien_thi (a);
				//doc thong tin van dau
		for (int i=1;i<=8;i++)                         						
			{
				t[i].tong = tong_hang(a,t[i].x,t[i].y,t[i].z);
			}
				//ket qua
		kt_kq (t);
		
				//chan
		if (da_danh==0)
				if (a[5]==0) { danh (5,0); da_danh=1;}
		
				
		if (da_danh==0)
				for (int i=1;i<=8;i++)
				{
					if	(t[i].tong==2) {
					chon_danh (t,i,a);
					da_danh=1;tam=1;}
					if (tam==1) break;
				}
				
				
		if (da_danh==0)
			for (int i=1;i<=7;i++){
			
				for (int j=i+1;j<=8;j++)
				{
					if (t[i].tong== 1 && t[j].tong == 1 && kt(t,a,i,j)!=0)
					{
					danh (kt(t,a,i,j),0); da_danh=1; tam=2; }
					if (tam==2) break;
				}
				if (tam==2) break;
			}
				
				//tien
		if (da_danh==0)
			for (int i=1;i<=8;i++)
			{
				if (t[i].tong== -20) {
				chon_danh (t,i,a);
				da_danh=1;
				break;}
			}
		if (da_danh==0)
			for (int i=1;i<=8;i++)
			{
				if (t[i].tong== -10) {
				chon_danh (t,i,a);
				da_danh=1; break;}
			}
		if (da_danh==0)
			for (int i=1;i<=9;i++)
				if (a[i]==0) {
				danh (i,0); da_danh=1;break;}
					//ket qua
		for (int i=1;i<=8;i++)                         						
		{
			t[i].tong = tong_hang(a,t[i].x,t[i].y,t[i].z);
		}
		kt_kq (t);

		
		
	
		if (da_danh==0)
			{
			printf ("\t\t\t VAN CO DA HOA"); hien_thi(a);
			kthuc =1;
			}
	}	
	
}
