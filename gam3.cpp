#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <console.cpp>
#include <math.h>

#define Bienduoi 	25
#define Bientren 	0
#define Bienphai	20
#define Bientrai	0
#define Soxedich	6
#define Tiledanbandau	1

enum Trangthai {Left,Right
};

struct Toado {
	int x,y;
	
};

struct Xe {
	Toado td;
	int battu;
};

struct Xedich {
	Toado td;
	int bihu;

};

struct Game {
	int over;
	int diem;
	int nxd;
	Trangthai tt;
	int dan;
	char key;
	int tiledan;
	int sieunangluc;
	int noinang;
	
};

void Xulyban (Xe &xe, Xedich xedich[], Game &game)
{
	if (game.dan!=0)
	{
		for (int i=xe.td.y-2;i>=0;i--)
		{
			gotoXY (xe.td.x,i);
			putchar (177);
		}
		Sleep (100);
		for (int i=0;i<=game.nxd-1;i++)
		{
			if (xedich[i].td.x>=xe.td.x-1 && xedich[i].td.x<=xe.td.x+1)
				{xedich[i].bihu=1; if (game.noinang<10) game.noinang++;}
			
		}
		game.dan--;
		game.tiledan++;
		game.key='0';
	}
}


void Khoitao (Xe &xe, Xedich xedich[], Game &game )
{
	
	//---------------- xe
	xe.td.x=Bienphai/2;
	xe.td.y=Bienduoi-1;
	
	//-----------------xe dich
		xedich[0].td.x=2+rand()%(Bienphai-3);
		xedich[0].td.y=0;
		
	for (int i=1;i< game.nxd;i++)
	{
		xedich[i].td.x=2+rand()%(Bienphai-3);
		xedich[i].td.y=xedich[i-1].td.y-5-rand()%5;
	}
	
}

void Hienthixe (int x,int y)
{
	if (y>=1 && y<=Bienduoi)
	for (int i=-1;i<=1;i++)
		for (int j=-1;j<=1;j++)
		{
			if ((i+j==2||i+j==0||j+i==-2)&& i!=0 &&j!=0) {
			gotoXY (x+i,y+j);
			putchar (219);
			}
			else if(i==0&&j==0)
			{	gotoXY (x,y);
				putchar (179);
			}
			else if(i==0&&j==-1)
			{
				gotoXY (x,y+j);
				putchar (194);
			}
			else if(i==0&&j==1)
			{
				gotoXY (x,y+j);
				putchar (193);
			}
		}
	
	
}

void Hienthi (Xe xe, Xedich xedich[], Game game)
{
	clrscr ();
	
	//---------- bia
	for (int i=0;i<=Bienduoi;i++)
		printf ("%c\n",179);
	for (int i=0;i<=Bienduoi;i++)
	{
		gotoXY (Bienphai,i);
		putchar (179);
	}
	for (int i=0;i<=Bienduoi;i++)
	{
		gotoXY (Bienphai/2,i);
		putchar ('|');
	}
		
		
	//---------xe
	if (xe.battu>0) TextColor (rand()%16);
 	Hienthixe (xe.td.x,xe.td.y);
	TextColor (15);
	//----------xe dich
	for (int i=0;i< game.nxd;i++)
	if (xedich[i].bihu!=1)
	Hienthixe (xedich[i].td.x,xedich[i].td.y);
	//---------diem
	gotoXY (Bienphai+1,Bienduoi/2);
	
	printf ("%d Diem, %d Vien Dan, %d/10 Noi nang, ti le ra dan la 1/%d",game.diem,game.dan,game.noinang,game.tiledan);
	if (xe.battu!=0) {
		gotoXY (Bienphai/2,Bienduoi/2+1);
		printf ("DAN DANG BAT TU TRONG %d GIAY.........",xe.battu*20/1000);
	
		
	}
}

void Dieukhien (Xe &xe,Game &game)

{
	if (game.tt==Left&&xe.td.x>=3)
		xe.td.x--;
	else if (game.tt==Right&&xe.td.x<=Bienphai-3)
		xe.td.x++;
	
}

void Dieukhienxedich (Xedich xedich[],Game game)
{
	for (int i=0;i<game.nxd;i++)
		xedich[i].td.y++;
		
	
}

void Xuly (Xe &xe, Xedich xedich[], Game &game)
{
	//----------game over
	for (int i=0;i<game.nxd;i++)
	{
	int x= abs(xe.td.x-xedich[i].td.x);
	int y= abs(xe.td.y-xedich[i].td.y);
	if (x<=2 && y<=2 && xedich[i].bihu!=1) {game.over=1;}
	
	}
	
	//---------xe dich
	if (xedich[0].td.y>Bienduoi)
	{
	
		for (int i=0;i<=game.nxd-2;i++)
			{xedich[i]=xedich[i+1];
			}
		xedich[game.nxd-1].td.x=2+rand()%(Bienphai-3);
		xedich[game.nxd-1].td.y=-rand()%10;
		xedich[game.nxd-1].bihu=0;
		game.diem++;
		
		if (rand()%(game.tiledan)==0) game.dan++;
	}
	
}

int main ()
{
	Xe xe; Game game; game.dan=0;
	Xedich xedich[Soxedich]; 
	game.nxd = Soxedich;
	game.over =0;
	srand(time(NULL));
	game.tiledan=Tiledanbandau;
	game.noinang=0;
	game.sieunangluc=0;
	
	//khoi tao
	Khoitao (xe,xedich,game);
	while (1)
	{
		//hien thi
		Hienthi(xe,xedich,game);
		
		
		
		
		
		//dieu khien
		if (kbhit())
		{
			game.key=_getch ();
			if (game.key !='p'&&game.key!='o');
			{
				if (game.key=='a') { game.tt=Left; Dieukhien (xe,game);
				}
				else if (game.key=='d') { game.tt=Right; Dieukhien (xe,game);
				}
			}
		
		}
		
		if (game.key=='p')
		{
			Xulyban (xe,xedich,game);
		
		}
		if (game.key=='o')
		
		{
				if (game.noinang>=10)
				{
					xe.battu=200;
					game.noinang=0;
				}
	
		}
		
		Dieukhienxedich (xedich,game);
		
		//xu ly
		Xuly (xe,xedich,game);
		
		
		
		
		
		//game over
		if (game.over ==1 && xe.battu==0)
		{	
			gotoXY (Bienphai+1,Bienduoi/2+1);
			printf ("ban da thua roi--------DAT DUOC %d DIEM	-------- an Enter de THOAT GAME",game.diem);
			while (_getch()!=13);
			break;
		}
		if (xe.battu!=0) {game.over=0; xe.battu--;}
		
		if (xe.battu==0) Sleep (50); else Sleep (20);
	
	}
	
		
		
	}

