#include <graphics.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>

// mouse handel function
union REGS in,out;
void status();
void position(int* ,int* ,int*);
void show();
void hide();
void setpos();

// main screen functions
void main_scr();
void show_hs(struct hscore);
void win_todo();

// score functions
void save_score();
void save_scr_scn();
char *char_inp(int []);

// game screen function
void game_scr();
void deselect();
void updirpt(int[],int);
void start();
float tarline(int ,int );
int dist(int,int);
void ball_throw();
void line_reset();
void xypt(int [],int,int);
int chack_ball();
void adjust(int,int);
void mark_delte(int,int);
void delet_bln();
void add_line();
void new_ball();
void win_or_lose();

void select_colors();

struct bulun
{
	int left;
	int top;
	int right;
	int bottum;
	int colr;

}bln[10][20],ball,selbln,sntr[10][20],temp[1][20];

struct gmdata
{
	struct bulun blns[10][20];
	struct bulun bal;
	int tlin;
	int use_ball;
}gt;

struct hscore
{
	char p_name[50];
	int scr;
}hs;

// some globle variable
int angl;
int tline=0;
int scount=0;
int to_tr_ball=0;
int colrs[6];

void main()
{

	FILE *f1;
	int px,py,x,y,m,tl,i,j,rs,se;

	char qu,pos[50];
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}

START_SCR:
{
	hide();
	cleardevice();
	main_scr();
	show();
	setpos();
	position(&x,&y,&m);
	while(1)
	{
		show();
		position(&x,&y,&m);

		if(x>=350 && x<=400 && y>=0 && y<=40)
		{
			if(m==1)
			{
				setcolor(RED);
				settextstyle(7,0,3);
				setfillstyle(SOLID_FILL,YELLOW);
				bar(20,150,380,300);
				outtextxy(200,225,"Do you want to exit (Y/N)?");
				qu=getch();
				if(qu=='y' || qu=='Y')
				{
					exit(0);
				}
				cleardevice();
				main_scr();
			}
		}
		if(x>=0 && x<=400 && y>60 && y<=160)
		{
			if(m==1)
			{
				goto RESUME_GAME;
			}
		}
		if(x>=0 && x<=400 && y>160 && y<=260)
		{
			if(m==1)
			{
				goto NEW_GAME;
			}
		}
		if(x>=0 && x<=400 && y>260 && y<=360)
		{
			if(m==1)
			{
				goto HEIGH_SCORE;
			}
		}
		if(x>=0 && x<=400 && y>360 && y<=460)
		{
			if(m==1)
			{
				setcolor(RED);
				settextstyle(7,0,3);
				setfillstyle(SOLID_FILL,YELLOW);
				bar(20,150,380,300);
				outtextxy(200,225,"Do you want to exit (Y/N)?");
				qu=getch();
				if(qu=='y' || qu=='Y')
				{
					exit(0);
				}
				cleardevice();
				main_scr();
			}
		}

	}
};

RESUME_GAME:
{
    FILE *f2;
	rs=0;
	if((f2=fopen("shooting\\game_data.dat","r"))==NULL)
	{
		cleardevice();
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(10,150,390,300);
		settextstyle(1,0,2);
		outtextxy(200,200,"FILE NOT FIND TO READ DATA");
		getch();
		exit(0);
	}
	else
	{
		rs=fread(&gt,sizeof(gt),1,f2);
		fclose(f2);
		if(rs==0)
		{
			cleardevice();
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(10,150,400,300);
			settextstyle(1,0,2);
			outtextxy(200,200,"FILE NOT READ");
			getch();
			goto RESTART;
		}
		else
		{

			for(i=0;i<10;i++)
			{
				for(j=0;j<20;j++)
				{
					bln[i][j]=gt.blns[i][j];
				}
			}
			ball=gt.bal;
			tline=gt.tlin;
			to_tr_ball=gt.use_ball;
		}
	}
	goto START;
};

NEW_GAME:
{
	goto RESTART;
};

HEIGH_SCORE:
{
    if((f1=fopen("shooting\\score.dat","r"))==NULL)
	{
		cleardevice();
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(10,150,400,300);
		settextstyle(7,0,2);
		outtextxy(200,200,"SCORE FILE NOT FOUND");
		getch();
	}
	else
	{
		fread(&hs,sizeof(hs),1,f1);
		fclose(f1);
		show_hs(hs);
	}
	goto START_SCR;
};

RESTART:
{
	
	tline=0;
	to_tr_ball=0;
	start();
	deselect();

};

START:
{
	hide();
	cleardevice();
	game_scr();
	show();
	while(1)
	{
		show();
		position(&x,&y,&m);
		if(x>=350 && x<=400 && y>=0 && y<=40)
		{
			if(m==1)
			{
				setcolor(RED);
				settextstyle(7,0,3);
				setfillstyle(SOLID_FILL,YELLOW);
				bar(20,150,380,300);
				outtextxy(200,225,"Do you want to exit (Y/N)?");
				qu=getch();
				if(qu=='y' || qu=='Y')
				{
					se=1;
					goto SAVE_EXIT;
				}
				hide();
				cleardevice();
				game_scr();
				show();
			}
		}
		if(x>=0 && x<=400 && y>=240 && y<=400)
		{
			if(m==1)
			{
				position(&x,&y,&m);
				hide();
				setcolor(ball.colr);
				angl=tarline(x,y);
				ball_throw();
				delet_bln();
				line_reset();
				to_tr_ball++;
				if(to_tr_ball>0)
				{
					tl=to_tr_ball%10;

					if(tl==0)
					{
						tline++;
						add_line();

						line_reset();
					}
				}
				win_or_lose();
				scount=0;
				deselect();
				new_ball();
				cleardevice();
				game_scr();
				m=0;
			}
			show();
		}
		if(x>40 && x<=60 && y>=0 && y<=100)
		{
			if(m==1)
			{
				goto TODO_COMM;
			}
		}
	}

};

TODO_COMM:
{
	hide();
	cleardevice();
	game_scr();
	win_todo();
	show();
	setpos();
	delay(100);
	while(1)
	{
		position(&x,&y,&m);
		if(x>=0 && x<=180 && y>60 && y<=100)
		{
			if(m==1)
			{
				goto RESTART;
			}
		}
		else if(x>=0 && x<=180 && y>100 && y<=140)
		{
			if(m==1)
			{
				se=1;
				goto SAVE_EXIT;
			}
		}
		else if(x>=0 && x<=180 && y>140 && y<=180)
		{
			if(m==1)
			{
				se=0;
				
				goto SAVE_EXIT;
			}
		}
		else
		{
			if(m==1)
			{
				goto START;
			}
		}
	}
};

SAVE_EXIT:
{
	struct gmdata gd;
	if((f1=fopen("shooting\\game_data.dat","w+"))==NULL)
	{
		hide();
		cleardevice();
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(10,150,500,300);
		settextstyle(7,0,3);
		outtextxy(150,225,"FILE NOT FIND TO SAVE DATA");
		show();
		getch();

	}
	else
	{
		for(i=0;i<10;i++)
		{
			for(j=0;j<20;j++)
			{
				gd.blns[i][j]=bln[i][j];
			}
		}
		gd.bal=ball;
		gd.tlin=tline;
		gd.use_ball=to_tr_ball;

		rs=fwrite(&gd,sizeof(gd),1,f1);
		if(rs==0)
		{
			hide();
			cleardevice();
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(10,150,500,300);
			settextstyle(7,0,3);
			outtextxy(150,225,"NO DATA WRITTEN TO FILE ");
			show();
			getch();

		}
		else
		{
			hide();
			cleardevice();
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(10,150,500,300);
			settextstyle(7,0,3);
			outtextxy(200,225,"DATA SAVE SUCCESSFULLY!!");
			show();
			getch();
		}
	}
	fclose(f1);
	if(se==1)
	{
		exit(0);
	}
	else
	{
		goto START_SCR;
	}
		
};

}

void new_ball()
{
	int q,tr=0;
	select_colors();
	randomize();
	ball.left=240;
	ball.top=450;
	ball.bottum=470;
	ball.right=260;
	while(tr==0)
	{
		q=random(6)+1;
		for(int i=0;i<6;i++)
		{
			if(q==colrs[i])
			{
				ball.colr=q;
				tr=1;
				return;
			}
		}
	}
}

void select_colors()
{
	int i,j,t,l=0,u=0;
	for(i=0;i<6;i++)
	{
		colrs[i]=0;
	}
	for(i=0;i<10;i++)
	{
		for(j=0;j<20;j++)
		{
			for(t=0;t<6;t++)
			{
				if(bln[i][j].colr==colrs[t] || bln[i][j].top==-10)
				{
					u=0;
					break;
				}
				else
				{
					u=1;
				}
			}
			if(u==1)
			{
				colrs[l]=bln[i][j].colr;
				l++;
			}
			if(l==6)
			{
				return;
			}
		}
	}
}

void win_todo()
{
	setfillstyle(SOLID_FILL,WHITE);
	bar(0,60,180,180);
	setcolor(BLUE);
	settextstyle(1,0,2);
	line(0,100,180,100);
	line(0,140,180,140);

	outtextxy(90,80,"RESTART");
	outtextxy(90,120,"SAVE & EXIT");
	outtextxy(90,160,"MAIN MENU");
}


void main_scr()
{
	setbkcolor(CYAN);
	setfillstyle(SOLID_FILL,9);
	bar(0,0,400,460);

	//title bar
	setcolor(getmaxcolor());
	settextjustify(1,1);
	settextstyle(7,0,4);
	setfillstyle(SOLID_FILL,8);
	bar(0,0,400,40);
	outtextxy(200,15,"SHOOTING GAME");
	setfillstyle(SOLID_FILL,RED);
	settextstyle(0,0,4);
	bar(350,0,400,40);
	setcolor(GREEN);
	outtextxy(375,20,"X");
	//main menu bar

	setfillstyle(SOLID_FILL,WHITE);
	settextstyle(7,0,3);
	bar(0,40,400,60);

	// menus list
	setcolor(RED);
	line(0,160,400,160);
	line(0,260,400,260);
	line(0,360,400,360);
	setcolor(10);
	settextstyle(7,0,5);
	outtextxy(200,110,"RESUME GAME");
	outtextxy(200,210,"NEW GAME");
	outtextxy(200,310,"HEIGH SCORE");
	outtextxy(200,410,"EXIT");

}

void status()
{
	in.x.ax=0;
	int86(51,&in,&out);
}
void hide()
{
	in.x.ax=2;
	int86(51,&in,&out);
}
void show()
{
	in.x.ax=1;
	int86(51,&in,&out);
}
void setpos()
{
	in.x.ax=4;
	in.x.cx=0;
	in.x.dx=0;
	in.x.bx=0;
	int86(0x33,&in,&out);
}
void position(int *x,int *y,int *m)
{
	in.x.ax=3;
	int86(0x33,&in,&out);
	*m=out.x.bx;
	*x=out.x.cx;
	*y=out.x.dx;
}

void line_reset()
{
	int i,j,t;
	for(i=tline-1;i>=0;i--)
	{
		for(j=0;j<20;j++)
		{
			if(bln[i][j].colr==0)
			{
				t=0;
			}
			else
			{
				t=1;
				return;
			}
		}
		if(t==0)
		{
			tline--;
		}
	}
}

void add_line()
{
	int i,j,t;
	randomize();
	for(i=tline;i>=0;i--)
	{
		for(j=0;j<20;j++)
		{
			if(i==0)
			{
				t=random(4);
				if(t==0)
				{
					bln[i][j].left=-10;
					bln[i][j].top=-10;
					bln[i][j].bottum=-10;
					bln[i][j].right=-10;
					bln[i][j].colr=0;
				}
				else
				{
					bln[i][j].left=0+(j*20);
					bln[i][j].top=60+(i*20);
					bln[i][j].bottum=80+(i*20);
					bln[i][j].right=20+(j*20);
					bln[i][j].colr=random(6)+1;
				}
			}
			else
			{
				if(bln[i-1][j].colr!=0)
				{
					bln[i][j].left=0+(j*20);
					bln[i][j].top=60+(i*20);
					bln[i][j].bottum=80+(i*20);
					bln[i][j].right=20+(j*20);
					bln[i][j].colr=bln[i-1][j].colr;
				}
			}
		}
	}
}

void start()
{
	randomize();
	int i,j,t;
	for(i=0;i<6;i++)
	{
		colrs[i]=0;
	}
	for(i=0;i<10;i++)
	{
		for(j=0;j<20;j++)
		{
			t=random(4);
			if(t==0 || i>=1)
			{
				bln[i][j].left=-10;
				bln[i][j].top=-10;
				bln[i][j].bottum=-10;
				bln[i][j].right=-10;
				bln[i][j].colr=0;
			}
			else
			{

				bln[i][j].left=0+(j*20);
				bln[i][j].top=60+(i*20);
				bln[i][j].bottum=80+(i*20);
				bln[i][j].right=20+(j*20);
				bln[i][j].colr=random(6)+1;
			}
		}
	}
	
	new_ball();
	tline=1;
}

void game_scr()
{
	int dir[8],pt[4];
	int x,y,i,j,l;
	setbkcolor(CYAN);
	setfillstyle(SOLID_FILL,9);
	bar(0,0,400,460);

	//title bar
	setcolor(getmaxcolor());
	settextjustify(1,1);
	settextstyle(7,0,4);
	setfillstyle(SOLID_FILL,8);
	bar(0,0,400,40);
	outtextxy(200,15,"SHOOTING GAME");
	setfillstyle(SOLID_FILL,RED);
	settextstyle(0,0,4);
	bar(350,0,400,40);
	setcolor(GREEN);
	outtextxy(375,20,"X");
	//main menu bar

	setfillstyle(SOLID_FILL,WHITE);
	settextstyle(7,0,3);
	bar(0,40,400,60);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(0,40,100,60);
	setcolor(BLUE);
	outtextxy(50,45,"ToDo");

	for(i=0;i<=tline;i++)
	{
		for(j=0;j<20;j++)
		{
			setcolor(bln[i][j].colr);
			setfillstyle(SOLID_FILL,bln[i][j].colr);
			x=(bln[i][j].left+bln[i][j].right)/2;
			y=(bln[i][j].top+bln[i][j].bottum)/2;
			fillellipse(x,y,10,10);
		}
	}
	setcolor(GREEN);
	setfillstyle(SOLID_FILL,YELLOW);
	sector(200,460,0,180,30,30);
	setfillstyle(SOLID_FILL,YELLOW);

	setcolor(ball.colr);
	setfillstyle(SOLID_FILL,ball.colr);
	sector(200,460,0,180,10,10);

	setlinestyle(2,0,3);
	setcolor(RED);
	line(0,260,400,260);
	line(0,400,400,400);
	setlinestyle(0,0,1);

	setfillstyle(SOLID_FILL,YELLOW);
	settextstyle(7,0,3);
	bar(405,0,635,460);
	setcolor(RED);
	outtextxy(520,30,"TOTAL BAll USED :");
	char trb[10];
	sprintf(trb,"%d",to_tr_ball);
	outtextxy(520,60,trb);
	outtextxy(520,90,"TOTAL LINE :");
	//char trb[10];
	sprintf(trb,"%d",tline);
	outtextxy(520,120,trb);

	setcolor(GREEN);
}

void updirpt(int pts[4],int ang)
{
	float th1;
	float k1,l1;
	th1=((270+ang)*3.1416)/180;
	k1=cos(th1);
	l1=sin(th1);
	pts[0]=240+(60*k1);
	pts[1]=460+(60*l1);
	pts[2]=pts[0]+20;
	pts[3]=pts[1];
}

int dist(int x,int y)
{
	long dt,xp,yp,xl,yl;
	int a;
	xl=(200-x);
	xp=xl*xl;
	yl=(460-y);
	yp=yl*yl;
	dt=xp+yp;
	a=sqrt(dt);
	return a;
}

float tarline(int x,int y)
{
	int dt,a;
	float th,ac,vv,tt;
	int aa;
	setbkcolor(CYAN);
	setcolor(YELLOW);
	a=dist(x,y);
	tt=(200-x);
	tt=tt/a;
	vv=acos(tt);
	ac=vv*(180/3.1416);
	aa=ceil(ac);
	th=((180+aa));
	return th;

}

void ball_throw()
{
	int bx=200,by=460,px=200,py=460;
	int pt[2],rs=0;
	int i,j,ll;
	while(ball.top>60)
	{

		px=bx;
		py=by;
		xypt(pt,bx,by);
		
		bx=pt[0];
		by=pt[1];
		ball.top=by-10;
		ball.left=bx-10;
		ball.right=bx+10;
		ball.bottum=by+10;
		setcolor(ball.colr);
		setfillstyle(SOLID_FILL,ball.colr);
		fillellipse(bx,by,10,10);
		if(by<=260)
		{
			rs=chack_ball();
			if(rs==1)
			{
				break;
			}
		}
		if(bx<=0)
		{
			angl=angl+90;
		}
		if(bx>=400)
		{
			angl=angl-90;
		}
		delay(100);
		
		setcolor(9);
		setfillstyle(SOLID_FILL,9);
		fillellipse(px,py,10,10);
	}
	if(ball.top<=60)
	{
		ll=bx%20;
		if(ll<10)
		{
			bx=bx-ll;
		}
		else
		{
			bx=bx+ll;
		}
		j=bx/20;
		i=0;
		adjust(i,j);

	}
}

int chack_ball()
{
	int i,j,t=0;
	float dt,tt,ll;
	for(i=0;i<10;i++)
	{
		for(j=0;j<20;j++)
		{
			if(ball.top<=bln[i][j].bottum)
			{
				dt=ball.left-bln[i][j].left;
				tt=abs(dt);
				if(tt<=20)
				{
					if(dt<=0)
					{
						if(tt>=9)
						{
							if(bln[i][j-1].top==-10)
							{
								adjust(i,j-1);
								mark_delte(i,j-1);
								return 1;
							}
							else
							{
								adjust(i+1,j);
								mark_delte(i+1,j);
								if(tline==i+1)
								{
									tline++;
								}
								return 1;
							}
						}
						else
						{
							adjust(i+1,j);
							mark_delte(i+1,j);
							if(tline==i+1)
							{
								tline++;
							}
							return 1;
						}
					}
					else
					{
						if(tt>=9)
						{
							if(bln[i][j+1].top==-10)
							{
								adjust(i,j+1);
								mark_delte(i,j+1);
								return 1;
							}
							else
							{
								adjust(i+1,j);
								mark_delte(i+1,j);
								if(tline==i+1)
								{
									tline++;
								}
								return 1;
							}
						}
						else
						{
							adjust(i+1,j);
							mark_delte(i+1,j);
							if(tline==i+1)
							{
								tline++;

							}
							return 1;
						}

					}
				}
			}
			
			t=0;

		}
	}
	return t;
}

void xypt(int pts[2],int x,int y)
{
	int ch=0,dt=10;
	float th1;
	float k1,l1;
	th1=((0+angl)*3.1416)/180;
	k1=cos(th1);
	l1=sin(th1);
	while(ch==0)
	{
		pts[0]=x+(dt*k1);
		pts[1]=y+(dt*l1);
		if(pts[0]<0 || pts[0]>400)
		{
			dt=dt/2;
		}
		else
		{
			ch=1;
		}
	}
}

void adjust(int i,int j)
{

		bln[i][j].left=0+(j*20);
		bln[i][j].top=60+(i*20);
		bln[i][j].bottum=80+(i*20);
		bln[i][j].right=20+(j*20);
		bln[i][j].colr=ball.colr;
		selbln=bln[i][j];
	
}

void mark_delte(int i,int j)
{
	if(bln[i][j].colr!=ball.colr)
	{
		return;
	}
	else
	{
		if(bln[i][j-1].colr==ball.colr && sntr[i][j-1].left==-10)
		{

			sntr[i][j-1]=bln[i][j-1];
			scount++;
			mark_delte(i,j-1);
		}
		if(bln[i][j+1].colr==ball.colr && sntr[i][j+1].left==-10)
		{


			sntr[i][j+1]=bln[i][j+1];
			scount++;
			mark_delte(i,j+1);

		}
		if(bln[i-1][j].colr==ball.colr && sntr[i-1][j].left==-10)
		{


			sntr[i-1][j]=bln[i-1][j];
			scount++;
			mark_delte(i-1,j);

		}
		if(bln[i+1][j].colr==ball.colr && sntr[i+1][j].left==-10)
		{

			sntr[i+1][j]=bln[i+1][j];
			scount++;
			mark_delte(i+1,j);

		}

	}
}

void delet_bln()
{
	int i,j;
	if(scount>=3)
	{
		for(i=0;i<10;i++)
		{
			for(j=0;j<20;j++)
			{
				if(sntr[i][j].left!=-10)
				{
					bln[i][j].left=-10;
					bln[i][j].top=-10;
					bln[i][j].bottum=-10;
					bln[i][j].right=-10;
					bln[i][j].colr=0;
				}
			}
		}
	}
}

void deselect()
{
	int i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<20;j++)
		{
			sntr[i][j].left=-10;
			sntr[i][j].top=-10;
			sntr[i][j].bottum=-10;
			sntr[i][j].right=-10;
			sntr[i][j].colr=0;
		}
	}
}

void win_or_lose()
{
	int i,j,rs=1;
	if(tline==9)
	{
		setcolor(RED);
		settextstyle(7,0,3);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(20,150,380,300);
		outtextxy(200,225,"YOU LOSE ");
		getch();
		exit(0);
	}
	for(i=0;i<10;i++)
	{
		for(j=0;j<20;j++)
		{
			if(bln[i][j].left==-10 )	
			{
				rs=0;
			}
			else
			{
				rs=1;
				return;
			}
		}
	}
	if(rs==0)
	{
		save_score();
		setcolor(RED);
		settextstyle(7,0,3);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(20,150,380,300);
		outtextxy(200,225,"YOU WIN ");
		getch();
		exit(0);
	}
}

void show_hs(struct hscore th)
{
	char tm[10],tmt[10],p_n[50];
	hide();
	cleardevice();
	setbkcolor(CYAN);
	setcolor(GREEN);
	settextjustify(1,1);
	setfillstyle(SOLID_FILL,BROWN);
	settextstyle(7,0,3);
	bar(100,20,500,70);
	outtextxy(300,30,"HIGH SCORE");
	settextjustify(0,2);
	setfillstyle(SOLID_FILL,BLUE);
	settextstyle(7,0,3);
	bar(100,70,500,310);
	outtextxy(110,70,"PLAYER NAME : ");
	strcpy(p_n,th.p_name);
	outtextxy(110,110,p_n);
	sprintf(tmt,"%d",th.scr);
	outtextxy(110,150,"TOTAL USED BALL : ");
	outtextxy(110,190,tmt);
	settextjustify(1,1);
	show();
	getch();
}

char *char_inp(int cor[5])
{
	int h,q,l,i,t,cr;
	char inp[50];
	char chp[50],*endptr;
	char ch='0';
	char ap[50]="",bp[50],cp[50],dp[50];
	h=cor[0]+10;
	i=cor[1]+10;
	settextstyle(1,HORIZ_DIR,2);

	while(ch!='\r')
	{

		save_scr_scn();
		setcolor(YELLOW);
		setfillstyle(1,RED);
		h=cor[0]+10;
		i=cor[1]+10;
		settextstyle(1,HORIZ_DIR,2);
		bar(cor[0],cor[1],cor[2],cor[3]);
		outtextxy(h,i,ap);
		ch=getch();

			if(ch=='\b')
			{
				strcpy(bp,ap);
				strrev(bp);
				q=strlen(bp)-1;
				i=0;
				while(q>0)
				{
					cp[i]=bp[q];
					i++;
					q--;
				}
				cp[i]='\0';
				strcpy(ap,cp);
			}

			if(ch=='a' || ch=='b'|| ch=='c'|| ch=='d' || ch=='e' || ch=='f'|| ch=='g' || ch=='h'|| ch=='i'|| ch=='j' || ch=='k' || ch=='l' || ch=='m' || ch=='n'|| ch=='o'|| ch=='p' || ch=='q' || ch=='r'|| ch=='s' || ch=='t'|| ch=='u'|| ch=='v' || ch=='w' || ch=='x' || ch=='y' || ch=='z')
			{
				sprintf(chp,"%c",ch);
				strcat(ap,chp);
			}
			if(ch==' ' || ch=='A' || ch=='B'|| ch=='C'|| ch=='D' || ch=='E' || ch=='F'|| ch=='G' || ch=='H'|| ch=='I'|| ch=='J' || ch=='K' || ch=='L' || ch=='M' || ch=='N'|| ch=='O'|| ch=='P' || ch=='Q' || ch=='R'|| ch=='S' || ch=='T'|| ch=='U'|| ch=='V' || ch=='W' || ch=='X' || ch=='Y' || ch=='Z')
			{
				sprintf(chp,"%c",ch);
				strcat(ap,chp);
			}


	 }
	 strcpy(dp,ap);
	 return(dp);
}

void save_scr_scn()
{
		cleardevice();
		settextjustify(0,2);
		setbkcolor(CYAN);
		setcolor(GREEN);
		setfillstyle(SOLID_FILL,BLUE);
		settextstyle(7,0,3);
		bar(100,100,500,300);
		outtextxy(110,130,"ENTER THE PLAYER NAME : ");
		bar(100,200,500,300);

}

void save_score()
{
	struct hscore ohs;
	FILE *f1,*f2;
	int cr[5],l;
	if((f1=fopen("shooting\\score.dat","r+"))==NULL)
	{
		l=0;
	}
	else
	{
		fread(&ohs,sizeof(ohs),1,f1);
		if(ohs.scr>to_tr_ball)
		{
			l=0;
		}
		else
		{
			l=1;
		}
	}
	fclose(f1);
	if((f1=fopen("shooting\\score.dat","w+"))==NULL)
	{
		hide();
		cleardevice();
		setbkcolor(CYAN);
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(100,150,500,300);
		settextstyle(7,0,3);
		outtextxy(300,200,"FILE NOT FIND TO WRITE DATA");
		show();
		getch();

	}
	else
	{
		if(l==0)
		{
			cr[0]=100;
			cr[1]=200;
			cr[2]=500;
			cr[3]=300;
			cr[4]=0;
			strcpy(hs.p_name,char_inp(cr));
			hs.scr=to_tr_ball;
			fwrite(&hs,sizeof(hs),1,f1);
			fclose(f1);
			hide();
			cleardevice();
			setbkcolor(CYAN);
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(100,150,500,300);
			settextstyle(7,0,3);
			outtextxy(200,200,"SCORE SAVE ");
			show();
			getch();
			settextjustify(1,1);
		}
	}
}


