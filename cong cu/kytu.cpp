#include <stdio.h>
#include <console.cpp>

int main ()
{
	for (int i=1; i<=50;i++)
	printf ("%d  %c \n",i,i);
	gotoXY (20,0);
		for (int i=51; i<=100;i++)
	{gotoXY (40,i-50);
	printf ("%d  %c \n\n",i,i);
	}
	
		for (int i=101; i<=150;i++)
	{gotoXY (60,i-100);
	printf ("%d  %c \n\n",i,i);
	}
		for (int i=151; i<=200;i++)
	{gotoXY (80,i-150);
	printf ("%d  %c \n\n",i,i);
	}
		for (int i=200; i<=256;i++)
	{gotoXY (100,i-200);
	printf ("%d  %c \n\n",i,i);
	}
	while (_getch ()!=13);
}
