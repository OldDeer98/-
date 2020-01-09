#include<stdio.h>	
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

int position_x,position_y;
int high,width;
int bullet_x,bullet_y;
int enemy_x,enemy_y; 
int speed;
int score;

 void startup()
 {
 	high=20;
	width=30;
	position_x=high/2;
	position_y=width/2;
	enemy_x=0;
	enemy_y=0;
	bullet_x=-2;
	bullet_y=position_y;
	speed=0;
	score=0;
 }

 void gotoxy(int x,int y)
 {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(handle,pos);
 }
 
 void HideCursor()
 {
 	CONSOLE_CURSOR_INFO cursor_info={1,0};
 	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
 }
 
 void show()
 {
 	gotoxy(0,0);
 	int i,j;
 	for(i=0;i<=high;i++)
 	{
 		for(j=0;j<=width;j++)
 		{
 			if(i==position_x&&j==position_y)
 			{
 				printf("*");
			 }
			 else if(i==enemy_x&&j==enemy_y)
			 {
			 	printf("@");
			 }
			 else if(i==bullet_x&&j==bullet_y)
			 {
			 	printf("|");
			 }
			 else if(j==width)
			 {
			 	printf("|");
			 }
			 else
			 {
			 	printf(" ");
			 }
		 }
		 printf("\n");
	 }
	 for(j=0;j<=width;j++)
	 {
	 	printf("-");
	 }
	 printf("\n");
	 printf("µÃ·Ö£º%d",score);
 }
 
 void updatewithoutinput()
 {
 	if(bullet_x>-1)
 	{
 		bullet_x--;
	 }
	 
	 if(bullet_x==enemy_x&&bullet_y==enemy_y)
	 {
	 	score++;
	 	bullet_x=-2;
	 	enemy_y=rand()%width;
	 	enemy_x=-1;
	 }
	 
	 if(enemy_x>high)
	 {
	 	enemy_y=rand()%width;
	 	enemy_x=-1;
	 }
	 
	 if(speed<10)
	 {
	 	speed++;
	 }
	 if(speed==10)
	 {
	 	enemy_x++;
	 	speed=0;
	 }
	 
 }
 
 void updatewithinput()
 {
 	char input;
 	if(kbhit())
 	{
 		input=getch();
 		if(input=='w'&&position_x>0)
 		{
 			position_x--;
		 }
		 else if(input=='s'&&position_x<high)
		 {
		 	position_x++;
		 }
		 else if(input=='a'&&position_y>0)
		 {
		 	position_y--;
		 }
		 else if(input=='d'&&position_y<width)
		 {
		 	position_y++;
		 }
		 else if(input==' ')
		 {
		 	bullet_x=position_x-1;
		 	bullet_y=position_y;
		 }
	 }
 }
 
 int main()
 {
 	startup();
 	while(1)
 	{
 		HideCursor();
 		show();
 		updatewithoutinput();
 		updatewithinput();
	 }
	 return 0;
 }
