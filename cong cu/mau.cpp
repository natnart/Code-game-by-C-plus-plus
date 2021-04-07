#include <stdio.h>
#include <console.cpp>


int main ()
{
	for (int i=0;i<=255;i++)
	{	TextColor (i);
		printf ("%d\n",i);
	 } 
	getch ();
	
}
