#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <console.cpp>

#define 	chieungang 		20
#define		chieudoc		15
#define 	chieungangthuc 	chieungang*4+4
#define		chieudocthuc 	chieudoc*2+2
#define 	mautuong		11
#define 	mautuongmem		15
#define 	mauxeban		10
#define 	mauxedich1		14
#define 	mauxedich2		13
#define 	mauxedich3		12
#define 	maxai			8


/*
	ky tu: 
*/

enum	Trangthai 	{
	up,	down,	left,	right,	non
};	
enum	Tenai		{
	ai1,	ai2,	ai3
	
};


struct Dan 		{
	int		x,	y;
	Trangthai	tt;
};

struct Ao {
	char kytu;
	int mau;
};

struct 	Game 	{
	int 	tuong 		[chieungang + 1][chieudoc + 1]	;
	int 	tuongbv 	[chieungang + 1][chieudoc + 1]	;
	int 	tuongmem	[chieungang + 1][chieudoc + 1]	;
	Ao	ao 			[chieungangthuc+1][chieudocthuc+1];
	Ao	luu 	[chieungangthuc+1][chieudocthuc+1];
	char key;
	int lap;
	int delay;
	int stage;

};

struct 	Ai 	{ 
	Tenai		ten		;
	int			x, y	;
	int 		mau		;
	int 		tocdo	;
	Dan			dan		;
	int 		heath	;
	Trangthai 	tt		;
	int			buoc	;
	Trangthai 	face	;
};

struct You {
	int 	x,y;
	int		mau;
	int 	heath;
	int		tocdo;
	Dan		dan;
	Trangthai 	face;
	Trangthai tt;
	
};

void Clr (Game &game)
{
	for ( int i = 0; i <= chieungangthuc; i++)
		for ( int j = 0; j <= chieudocthuc; j++)
		{
			game.ao [i][j].kytu = ' ';
			game.ao [i][j].mau = 7;
		}
}

void Saoluu (Game &game) 
{
	for ( int i = 0; i <= chieungangthuc; i++)
		for ( int j = 0; j <= chieudocthuc; j++)
		{
			game.luu [i][j].kytu = game.ao [i][j].kytu;
			game.luu [i][j].mau = game.ao [i][j].mau;
		}
}

void Randomtt (Trangthai &tt)
{
	int rd = rand ()%4;
	if (rd == 0) 	tt = right;
	else if (rd == 1) 	tt =left;
	else if (rd == 2)	tt = up;
	else if (rd == 3) 	tt = down;
}

void Xulydan (Dan &dan)
{
		if (dan.tt == right) 	dan.x++;
		else if(dan.tt == left)	dan.x--;
		else if(dan.tt == up)	dan.y--;
		else if(dan.tt == down)	dan.y++;
}

void Vachamdan (int &x, int &y,int mau, Game &game, You &you, Ai ai[])
{
	if (game.ao[x][y].kytu == 'U' || game.ao[x][y].kytu == 'u') game.tuongmem [x/4][y/2] --;
	if (game.ao[x][y].kytu == 'K' ) game.tuong [x/4][y/2] --;
	
	for (int i=0; i<=3; i++)
		for (int j=0; j<=1; j++)
		{
			if (you.x + i == x && you.y +j == y && mau != mauxeban)
				you.heath --;
			for (int k=0; k<=10; k++)
			if (ai[k].x + i == x && ai[k].y + j == y && mau == mauxeban )
			ai[k].heath -- ;
		}
		
	x = 0;
	y = 0;
	
}

struct AA {
	int x;
	Trangthai tt;
};

void Randomtt2 (You &you, Ai &ai,Game &game)
{
	AA a[4]; AA  tg;
	a[0].x = you.x - ai.x ; a[0].tt = right;
	a[1].x = ai.x - you.x ; a[1].tt = left;
	a[2].x = ai.y - you.y ; a[2].tt = up;
	a[3].x = you.y - ai.y ; a[3].tt = down;
	
	for (int i =0; i<= 2; i++)
		for (int j=i+1; j<=3; j++)
			if (a[i].x < a[j].x)
			{
				tg = a[i];
				a[i] = a[j];
				a[j] = tg;
			}
		
	
	if (ai.ten == ai2 || game.stage <=2 )
	{
		if (rand()%10 <=3)  ai.tt = a[0].tt;
		else if (rand ()%6 <= 2) ai.tt = a[1].tt;
		else if (rand ()%3 <= 1) ai.tt = a[2].tt;
		else ai.tt = a[3].tt;
	}
	if (ai.ten == ai3 && game.stage >2)
	{
		if (rand()%5 <=2)  ai.tt = a[0].tt;
		else ai.tt = a[1].tt;
	}
	
}



void Khoitaoai (Ai &ai)
{
	switch (ai.ten)
	{
		case ai1: ai.x = 4; 				ai.y = chieudocthuc-2; 	ai.tocdo = 1; 	ai.heath = 2;  	break;
		case ai2: ai.x = chieungangthuc-4; 	ai.y = 2;  				ai.tocdo = 2;  	ai.heath = 3;  	break;
		case ai3: ai.x = chieungangthuc-4; 	ai.y = chieudocthuc-2;	ai.tocdo = 3;  	ai.heath = 5;  	break;
	}
	if (ai.ten == ai1) ai.mau = mauxedich1; else if (ai.ten == ai2) ai.mau = mauxedich2; else ai.mau = mauxedich3;
	ai.dan.x = 0; 
	ai.dan.y = 0;
	Randomtt (ai.tt);
	ai.face = ai.tt;
}

void Khoitao (Game &game, You &you, Ai ai[])
{
	// ----------------------- you
	you.x = 4;
	you.y = 2;
	you.mau = mauxeban;
	you.tocdo = 2;
	you.face = right;
	you.tt= non;
	you.dan.tt = non;
	you.dan.x = 0;
	you.dan.y = 0;
	you.heath = 3;
	
	//-------------------------- ai
	for (int i=0; i<=2; i++)
		ai[i].ten = ai1;
	for (int i=3; i<=5; i++)
		ai[i].ten = ai2;
	ai[6].ten = ai3;
	ai[7].ten = ai3;
	
	for (int i=0; i<=7; i++)
	Khoitaoai (ai[i]);

	
	
	//----------------------- game
	game.key = '0';
	game.delay = 0;
	
	// ------------------------ tuong 
	for (int i = 1; i <= chieungang; i++)
		for (int j = 1; j<= chieudoc; j++)
		{
			if (rand()% 8 == 0)		game.tuong [i][j] = 30; 	else game.tuong [i][j] = 0;
			if (rand()% 6 == 0 && game.tuong [i][j] == 0)	game.tuongmem [i][j] = 2; 	else game.tuongmem [i][j] = 0;
		}
	game.tuong[1][1] = game.tuongmem [1][1] = game.tuong[1][chieudoc] = game.tuongmem[1][chieudoc] = game.tuong [chieungang][1] = game.tuongmem [chieungang][1] =0;
	game.tuong[chieungang][chieudoc] = game.tuongmem [chieungang][chieudoc] = 0;
}

void Ino4x2 (int x, int y,char kytu, int mau, Game &game)
{
	for (int i=0; i<=3; i++)
		for (int j=0; j<=1; j++)
		{
			game.ao[x*4+i][y*2+j].kytu = kytu;
			game.ao[x*4+i][y*2+j].mau = mau;
		}
}

void Hienthixe (int x, int y, int mau, Game &game, Trangthai face)
{	//-------------------------- sung
	
	switch ( face){
		case right : game.ao[x+3][y].kytu = 196;
		game.ao[x+3][y+1].kytu = 196;
		break;
		
		case left : game.ao[x][y].kytu = 196;
		game.ao[x][y+1].kytu = 196;
		break;
		
		case up : game.ao[x+1][y].kytu = 179;
		game.ao[x+2][y].kytu = 179;
		break;
		
		case down : game.ao[x+1][y+1].kytu = 179;
		game.ao[x+2][y+1].kytu = 179;
		break;
	}
	//-------------------- banh xe
	for (int i = 0; i <= 3; i ++)
		for ( int j = 0; j <= 1; j++)
		{
			game.ao [x+i][y+j].mau = mau;
			if (game.ao[x+i][y+j].kytu == ' ')
			game.ao [x+i][y+j].kytu = 'O';
		}
	
}

void Xulyhienthi (Game &game, You &you, Ai ai[])
{
	//----------------- khung 
	TextColor (7) ;
	for (int i=1; i<= chieudocthuc; i++ )
		game.ao[3][i]. kytu = 179;
	for (int i=1; i<= chieudocthuc; i++ )
		game.ao[chieungangthuc][i]. kytu = 179;
	for (int i=3; i<= chieungangthuc; i++ )
		game.ao[i][1]. kytu = 196;
	for (int i=3; i<= chieungangthuc; i++ )
		game.ao[i][chieudocthuc]. kytu = 196;
		
	//----------------- you
	Hienthixe (you.x, you.y, you.mau, game, you.face );
	
	//--------------------- ai
	for (int i=0; i<=10; i++ )
	if (Hienthixe != 0) Hienthixe (ai[i].x, ai[i].y, ai[i].mau, game, ai[i].face);
	
	//----------------- tuong
	for (int i = 1; i<= chieungang; i++)
		for (int j=1; j<=chieudoc; j++)
		{
			if (game.tuong[i][j] != 0) 	Ino4x2 (i, j, 'K', mautuong, game);
			else if (game.tuongmem [i][j] == 2) 	Ino4x2 (i, j, 'U', mautuongmem, game);
			else if (game.tuongmem [i][j] == 1) 	Ino4x2 (i, j, 'u', mautuongmem, game);
		}
	
	//-------------------- dan cua ban
	if (you.dan.x != 0)		
	{
		game.ao[ you.dan.x] [ you.dan.y].kytu = 'x';
		game.ao[ you.dan.x] [ you.dan.y].mau = you.mau;
	}
	
	//---------------------- dan cua ai
	for (int i=0; i<=10; i++)
	{
		if (ai[i].dan.x != 0)		
		{
			game.ao[ ai[i].dan.x] [ ai[i].dan.y].kytu = 'x';
			game.ao[ ai[i].dan.x] [ ai[i].dan.y].mau = ai[i].mau;
		}
	}
}

void Hienthiao (Game &game, You &you)
{
	gotoXY (0, 0);
	for (int i=0; i<= chieudocthuc; i++)
		{
			for (int j =0; j<= chieungangthuc; j++)
			if (game.luu [j][i].kytu != game.ao[j][i].kytu )
			{
			gotoXY (j,i);
				TextColor (game.ao[j][i].mau);
				putchar (game.ao[j][i].kytu);
			}
//			printf ("\n");
		}
	gotoXY (chieungangthuc+1, 1);
	printf ("Heath: %d ; Stage: %d", you.heath,game.stage);
	
}

void Dieukhien (Game &game, You &you)
{ 
	//-------------------- you
	
	game.key = _getch ();
	if (game.key != 'p' || game.key != 'j') 
	{
		if (game.key == 'd') 	you.tt = right; 
		else if (game.key == 'a') 	you.tt = left; 
		else if (game.key == 's')  	you.tt = down; 
		else if (game.key == 'w')  	you.tt = up; 
		if (you.tt != non) you.face = you.tt;
	}
	
	
	//--------------------- pause
	if (game.key == 'p')
	{
		TextColor (7);
		gotoXY (chieungangthuc+1, (chieudocthuc) /2);
		printf ("Tam dung game, an 'p' de tiep tuc ");
		while (_getch () != 'p');
		gotoXY (chieungangthuc+1, (chieudocthuc)/2);
		printf ("                                  ");
		you.tocdo ++;
	}
	
	// -------------------- dan
	if (game.key == 'j' && you.dan.x == 0)
	{
		if (you.face == right)	
		{
			you.dan.x = you.x +4;
			you.dan.y = you.y + rand()%2;
			you.dan.tt = you.face;
		}
			if (you.face == left)	
		{
			you.dan.x = you.x -1;
			you.dan.y = you.y + rand()%2;
			you.dan.tt = you.face;
		}
			if (you.face == up)	
		{
			you.dan.x = you.x + 1+ rand()%2;
			you.dan.y = you.y - 1;
			you.dan.tt = you.face;
		}
			if (you.face == down)	
		{
			you.dan.x = you.x + 1+ rand()%2 ;
			you.dan.y = you.y + 2;
			you.dan.tt = you.face;
		}
	}
	
	//------------------------- phanh
	if (game.key == 'k')
	{
		you.tt = non;
	}
	
	//--------------------- reset game.key
//	game.key = '0';
}

void Xulyai (You &you,Ai &ai, Game &game)
{
	if (game.lap <= ai.tocdo)
	if (ai.tt != non)
	{
		switch (ai.tt) 
		{
			case right: 
				if (game.ao [ai.x+4][ai.y].kytu == ' ' && game.ao [ai.x+4][ai.y+1].kytu == ' ' )
				ai.x++; else ai.buoc = 1; break;
			case left: 
				if (game.ao [ai.x-1][ai.y].kytu == ' ' && game.ao [ai.x-1][ai.y+1].kytu == ' ' )
				ai.x--; else ai.buoc = 1; break;
			case up: 
				if (game.ao [ai.x][ai.y-1].kytu == ' ' && game.ao [ai.x+3][ai.y-1].kytu == ' ' )
				ai.y--; else ai.buoc = 1; break;
			case down: 
				if (game.ao [ai.x][ai.y+2].kytu == ' ' && game.ao [ai.x+3][ai.y+2].kytu == ' ' )
				ai.y++; else ai.buoc = 1; break;
		} 
		ai.buoc -- ;
	}
	if (ai.buoc == 0) 
	{
		ai.buoc = 4;
		if (ai.ten == ai1) Randomtt (ai.tt);
		if (ai.ten == ai2 || ai.ten == ai3) Randomtt2 (you, ai,game);
		ai.face = ai.tt ;
	}
	
}

void Xuly (Game &game, You &you, Ai ai[])
{
	//----------------------------- lap
	if (game.lap >= 4) game.lap = 1; else game.lap ++ ;
	
	//--------------------------- you
	if (game.lap <= you.tocdo)
	if (you.tt != non)
	{
		switch (you.tt) 
		{
			case right: 
				if (game.ao [you.x+4][you.y].kytu == ' ' && game.ao [you.x+4][you.y+1].kytu == ' ' )
				you.x++; break;
			case left: 
				if (game.ao [you.x-1][you.y].kytu == ' ' && game.ao [you.x-1][you.y+1].kytu == ' ' )
				you.x--; break;
			case up: 
				if (game.ao [you.x][you.y-1].kytu == ' ' && game.ao [you.x+3][you.y-1].kytu == ' ' )
				you.y--; break;
			case down: 
				if (game.ao [you.x][you.y+2].kytu == ' ' && game.ao [you.x+3][you.y+2].kytu == ' ' )
				you.y++; break;
		}
//			you.tt = non;
	}	
	
	//---------------------------- dan cua ban
	if (you.dan.x != 0) 	Xulydan (you.dan);
	if (you.dan.x != 0) 
		if ( game.ao[ you.dan.x ][ you.dan.y ].kytu != ' ')
		{
			Vachamdan ( you.dan.x, you.dan.y,mauxeban, game, you, ai);	
		}
	//------------------------------ Ai
	for (int i=0; i<=10; i++)
	if (ai[i].x != 0) Xulyai (you, ai[i], game);
	
	
	//-------------------------- dan AI
	for (int i=0; i<=10; i++)
	{
		if (ai[i].dan.x != 0) 	
		{
			Xulydan (ai[i].dan);
			if ( game.ao[ ai[i].dan.x ][ ai[i].dan.y ].kytu != ' ')
				Vachamdan ( ai[i].dan.x, ai[i].dan.y,ai[i].mau, game,you, ai);	
		}
		//---------------------- tao dan ai
		else if ((rand()% 40 == 0 || (ai[i].ten == ai3 && rand()%4 == 0)) && ai[i].x != 0 )
		{
			if (ai[i].face == right)	
			{
				ai[i].dan.x = ai[i].x +4;
				ai[i].dan.y = ai[i].y + rand()%2;
				ai[i].dan.tt = ai[i].face;
			}
				if (ai[i].face == left)	
			{
				ai[i].dan.x = ai[i].x -1;
				ai[i].dan.y = ai[i].y + rand()%2;
				ai[i].dan.tt = ai[i].face;
			}
				if (ai[i].face == up)	
			{
				ai[i].dan.x = ai[i].x + 1+ rand()%2;
				ai[i].dan.y = ai[i].y - 1;
				ai[i].dan.tt = ai[i].face;
			}
				if (ai[i].face == down)	
			{
				ai[i].dan.x = ai[i].x + 1+ rand()%2 ;
				ai[i].dan.y = ai[i].y + 2;
				ai[i].dan.tt = ai[i].face;
			}
		}
	}
	// --------------- diet ai
	for (int i =0; i<=10; i++)
		if (ai[i].heath <= 0)
		ai[i].x = ai[i].y = 0;
	
}


int main ()
{
	// --------------------------- khai bao	
	srand (time (NULL));
	You	you;
	Game game;
	Ai ai[11];
	game.stage =3;
	
	//-------------------------- khoi tao
Batdau :
	Khoitao (game, you, ai);

	//----------------------------game
	while (1)
	{
		//--------------- hien thi
		Clr (game);
		Xulyhienthi (game, you, ai);
		
		
		Hienthiao (game,you);
		Saoluu (game);
		
		
		
		// --------------- dieu khien
		if (kbhit())
		{
			Dieukhien (game, you); 
		
		}
	
	
		
		
		// ---------------- xu ly
		Xuly (game, you, ai);
	
		
		// ------------------ over
		if (you.heath <= 0)
		{
			gotoXY ((chieungangthuc+1), (chieudocthuc)/2 + 2);
			printf ("ban da THUA cmnr; enter: out");
			while (_getch ()!= 13);	
			break;
		}
		
		for (int i=0; i<=maxai-1; i++)
		{
			if (ai[i].x > 0)
			break;
			if (i== maxai -1)
			{
				
				game.stage ++;
				gotoXY ((chieungangthuc+1),(chieudocthuc)/2 + 2);
				printf ("Ban da qua ban, an enter de tiep tuc");
				while (_getch()!=13);		
				goto Batdau;
			}
		}
		
		// ----------------- sleep
		
		Sleep (30);
	
		
	}
	
}
