#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <console.cpp>

#define chieungang 	70	
#define chieudoc 	30
#define xchim		(chieungang)/2
#define dode		7



struct Chim {
	int 	y;
	int 	tt; // max = 5;
	
};

struct Game {
	char 	key;
	char 	ao[chieungang+1] [chieudoc+1];
	char 	luu [chieungang+1] [chieudoc+1];
	int 	over;
};

struct Ong {
	int 	x;
	int 	z;
	
	
};

void Clr (Game &game)
{
	for (int i=0; i<= chieungang; i++)
		for (int j =0; j<= chieudoc; j++)
		game.ao [i][j] = ' ';
}
void Hienthi (Game &game)
{
	for (int i=0; i<= chieungang; i++)
		for (int j =0; j<= chieudoc; j++)
		if (game.ao[i][j] != game.luu [i][j])
		{
			gotoXY (i,j );
			putchar (game.ao[i][j]);
		}
}

void Khoitao (Chim &chim, Game &game, Ong ong[])
{
	chim.y = chieudoc / 2;
	game.key = '0';
	game.over = 0;
	chim.tt = 1;
	ong[0].x = chieungang;
	ong[0].z = dode + rand ()% ((chieudoc)/2 - dode);
	for (int i=1; i<10 ;i++)
	{
		ong[i].x = ong[i-1].x + 8 + rand()%4;
		ong[i].z = dode + rand ()% ((chieudoc)/2 - dode);
		
	}
}

void Saoluu (Game &game)
{
	for (int i=0; i<= chieungang; i++)
		for (int j =0; j< chieudoc; j++)
		if (game.luu [i][j] != game.ao[ i] [j])
			game.luu [i][j] = game.ao[ i] [j];		
	
}

void Dieukhien (Chim &chim, Game &game)
{
	game.key = _getch ();
	
	//---------------------------- nhay
	if (game.key == ' ')
	{
		chim.tt = 6;		
	}
	game.key = 0;
}

void Xulyhienthi (Chim &chim, Game &game, Ong ong[])
{
	//-------- chim
	game.ao [xchim] [chim.y] = '>';
	
	//------------ ong khoi 
	for (int i=0; i< 10; i++)
	{
		if (ong[i].x >=0 && ong[i].x < (chieungang))
		{
				for (int j = 0; j<= ong[i].z; j++)
			{
				game.ao[ong[i].x][j] = 'M';
				game.ao[ong[i].x+1][j] = 'M';
			}
			for (int j = ong[i].z+5; j<=chieudoc; j++)
			{
				game.ao[ong[i].x][j] = 'M';
				game.ao[ong[i].x+1][j] = 'M';
			}
		}
		
	}
	
	//------------- bien
	for (int i=0; i<=chieungang; i++)
	game.ao[i][chieudoc] = 196;
	
	for (int i=0; i<=chieudoc; i++)
	game.ao[chieungang][i] = 179;
	
	
	
}

void Xuly (Chim &chim, Game &game, Ong ong[])
{
	//------------------------ chim
	if (chim.tt > 3 )
	chim.y--;
	else if (chim.tt < 2 )
	chim.y++;
	chim.tt--;
	
	//--------- ong khoi
	for (int i=0; i<10; i++)
	{
		ong[i].x --;
	}
	if (ong[0].x <0)
	{
		for (int i=0; i<9; i++)
		{
			ong [i] = ong [i+1];
		}
		ong[9].x = ong[8].x + 8 + rand()%4;
		ong[9].z = dode + rand ()% ((chieudoc)/2 - dode);
	}
	
	// ------------Va cham
	if (game.ao[xchim+1][chim.y] == 'M' || chim.y <0 || chim.y > chieudoc)
	game.over = 1;
}

int main ()

{
	srand (time (NULL));
	Game game;
	Chim chim;
	Ong ong [10];
	// khoi tao 
	Khoitao (chim, game, ong);
	
	while (1)
	{
		// Hienthi
		Clr (game);
		Xulyhienthi (chim, game, ong);
		Hienthi (game);
		Saoluu (game);
		
		
		// Dieu khien
		if (kbhit())
		Dieukhien (chim, game);
		
		//Xu ly
	
		Xuly (chim, game, ong);
		
		// Over
		if (game.over == 1)
		{
			gotoXY (chieungang +1, (chieudoc)/2);
			printf ("ban da thua, an Enter de out game");
			while (_getch ()!= 13);
			break;
			
		}
		
		//Sleep
		Sleep (50);
	}
	
	
}
