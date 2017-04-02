/********************************************
*			   SNAKE   V1.0			  2017  *
*										    *
*										    *							
* Plateform : Linux		   DEV:  LoganDC	*
* Tested on Ubuntu 16.04                    *
*********************************************/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stddef.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <sgtty.h>
#include <termios.h>
#include <sys/ioctl.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/* Key defines */
#define UP    56
#define DOWN  50
#define LEFT  52
#define RIGHT 54

/* Loaction Defines */
#define NUM_SECS 10
#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))

/* Colour Defines*/
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void goUp(void);
void Food(void);
void Reset(void);
void goRight(void);
void goDown(void);
void goLeft(void);
void Boarder(void);
void print_menu(void);
void print_score(void);
void initProgress(void);
void force_exit(int);
void my_wait(size_t);
void walkSnake(int);
void initlocations(void);
void addnode(void);
void printsnake(void);
void progressBar(size_t count, size_t max);


bool checkselfpunch();
int init_snake(void);
int mygetch(void);
int kbhit(void);
int delay(void);


typedef struct snake_cord
{
	int x;
	int y;
	int d;
} cord;

typedef struct snakebody
{
	int number;
	cord location;	
	struct snakebody *next;
	struct snakebody *prev;	
}SNODE;


cord FOOD;
SNODE *Snakehead = NULL;
SNODE *NEW = NULL;
int SCORE = 0;
int LIFE = 2;

int main()
{
	//system("setterm -cursor off");         // to disable the cursor // put on to enable  or we can use OR we can use
	fputs("\e[?25l", stdout);                /* hide the cursor */
	signal(SIGINT,force_exit);       
	system("clear");
	print_menu();
	system("clear");
	initlocations();
	init_snake();
	system("stty echo");                    // enable echo before exit 
	fputs("\e[?25h", stdout);                /* unhide the cursor */
	return 0;
}

void print_menu()
{

	printf("***************************************************************************\n");
	printf("*          __________  ___________  __________  __   __  _________        *\n");
	printf("*         |          ||       |   ||          ||  | /  ||         |       *\n");
	printf("*         |   _______||	      |   ||   ____   ||  |/   ||  _______|       *\n");
	printf("*         |	         ||   |   |   ||  |____|  ||      / |         |       *\n");
	printf("*         |_______   ||   |   |   ||   ____   ||      \\ |  _______|       *\n");
	printf("*         |          ||   |       ||  |    |  ||  |\\   ||         |       *\n");
	printf("*         |__________||___|_______||__|    |__||__| \\__||_________|       *\n");
	printf("*                                                                         *\n");
	printf("*                                               v1.1       LoganDC        *\n");
	printf("***************************************************************************\n\n\n");
	printf(ANSI_COLOR_GREEN);
	initProgress();
	printf(ANSI_COLOR_YELLOW);
	printf("\n****************** INSTRUCTIONS ******************\n\n\n");
	printf("=> Use Number keys to control snake \n");
	printf("=> Here you are provided with three lives.\n");
	printf("=> Press SPACE key to pause or resume the Game.\n");
	printf("=> Press ESC to exit the game.\n\n\n");
	printf(ANSI_COLOR_RESET); 
	printf("\n\nPress any key to continue .. .. .. .. \n\n\n\n");
	mygetch();	
}

int mygetch ( void ) 
{
	int ch;
	struct termios oldt, newt;

	tcgetattr ( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
	system("stty -echo");
	ch = getchar();
	system("stty echo");	
	tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}
/* Simulate progress bar */
void progressBar(size_t count, size_t max)
{  
	const char prefix[] = "Progress: [";
	const char suffix[] = "]";
	const size_t prefix_length = sizeof(prefix) - 1;
	const size_t suffix_length = sizeof(suffix) - 1;
	char *buffer = calloc(max + prefix_length + suffix_length + 3, 1 ); // +1 for \0
	size_t i = 0;

	strcpy(buffer, prefix);
	for (; i < max; ++i)
	{
		buffer[prefix_length + i] = i < count ? '=' : ' ';
	}

	strcpy(&buffer[prefix_length + i], suffix);
	printf("\b%c[2K\r%s", 27, buffer);                              // Print the Buffer bar
	printf(" %d %%",(int)count*2);                                  // Print the % count in progress
	fflush(stdout);
	free(buffer);
}

void initlocations(void)
{
	Snakehead = (SNODE*)malloc(sizeof(SNODE));
	Snakehead->location.x = 10;
	Snakehead->location.y = 10;
	Snakehead->next = NULL;
	Snakehead->prev = NULL;
	Snakehead->location.d = RIGHT;
	gotoxy(Snakehead->location.x,Snakehead->location.y);
	system("clear");
	FOOD.x = 0;
	FOOD.y = 0;
}

/* initialize Progress bar */
void initProgress(void)
{
	size_t num_secs = 1, max_secs = 50;
	printf("%s\n", "");
	progressBar(0, max_secs);
	for (; num_secs <= max_secs; ++num_secs)
	{
		my_wait(1);
		printf("%c[2K", 27);                                     // clear the line
		progressBar(num_secs, max_secs);

	}
	printf("\n\n");
}

void my_wait(size_t secs)
{
#ifdef _WIN32
	Sleep(1000 * secs);
#else
	for(int i=0;i<9999999;i++);
#endif
}

void force_exit(int sig)
{
	system("stty echo");                    // enable echo before exit 
	//system("setterm -cursor on");         // to enable the cursor  or we can use
	fputs("\e[?25h", stdout);                /* unhide the cursor */
	system("clear");
	exit(0);
}

/* main snake algoInit*/
int init_snake()
{
	int dir;
	bool flag = true;
	while(1)
	{ 
		system("stty -echo");           // to desable input echo to screen
		fflush(stdout);
		if(kbhit()) 
		{  
			dir = mygetch();        	    
			if((dir == RIGHT && Snakehead->location.d != LEFT) || (dir == DOWN && Snakehead->location.d != UP) || 
					(dir == LEFT  && Snakehead->location.d != RIGHT)|| (dir == UP  && Snakehead->location.d != DOWN )) 
				Snakehead->location.d = dir;  
		}

		if ( dir == 27 )   Reset();                                                              /* leave if ECS is pressed */
		if ( dir == ' ' )  { printf("\n\n     PAUSED .. ... ....  \n\n");  dir += mygetch(); }   /* Pause if pace is pressed */
		fflush(stdout);
		if(Snakehead->location.d == RIGHT)         goRight(); 	
		else if(Snakehead->location.d == DOWN)     goDown();
		else if(Snakehead->location.d == LEFT)     goLeft(); 
		else if(Snakehead->location.d == UP)       goUp();
		else ;
		system("clear");
		Boarder();
		print_score();
		Food();	
	}
}
/* User defined kbhit as Unix not have own kbhit function*/
int kbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}
	return 0;
}

void Food()
{
	if(Snakehead->location.x==FOOD.x&&Snakehead->location.y==FOOD.y)
	{   
		SCORE++;
		time_t a;
		a=time(0);
		srand(a);
		FOOD.x=rand()%24;
		if(FOOD.x<=10)
			FOOD.x+=11;
		FOOD.y=rand()%60;
		if(FOOD.y<=10)
			FOOD.y+=11;
		addnode();
	}
	else if(FOOD.x==0)       /*to create food for the first time coz global variable are initialized with 0*/
	{
		FOOD.x=rand()%24;
		if(FOOD.x<=10)
			FOOD.x+=11;
		FOOD.y=rand()%60;
		if(FOOD.y<=10)
			FOOD.y+=11;

	}
	gotoxy(FOOD.x,FOOD.y);
	printf("@");
}
/* Border mapping*/
void Boarder(void)
{
	int i;	
	system("clear");
	printf(ANSI_COLOR_CYAN);
	for(i=0;i<25;i++)
	{
		gotoxy(i,0);
		printf("║");
		gotoxy(i,60);
		printf("║");
	}
	for(i=0;i<61;i++)
	{
		gotoxy(0,i);
		printf("═");
		gotoxy(25,i);
		printf("═");
	}
	gotoxy(0,0);  printf("╔");
	gotoxy(0,60); printf("╗");
	gotoxy(25,0); printf("╚");
	gotoxy(25,60); printf("╝");		
	printf(ANSI_COLOR_RESET);
}

void goRight() 
{ 
	walkSnake(RIGHT);	
	Snakehead->location.x += 0;
	Snakehead->location.y += 1;
	Snakehead->location.d = RIGHT;	
	gotoxy(Snakehead->location.x,Snakehead->location.y);	
	printsnake();	
	fflush(stdout);
	delay();
	if(Snakehead->location.y == 60) { LIFE --; Snakehead->location.y = 1; }
	if(checkselfpunch()) 
	{  
		initlocations();
		printf(ANSI_COLOR_GREEN);
		printf("OOPPS .. ..  snake got crashed with ownself .."); 
		initProgress();
		printf(ANSI_COLOR_YELLOW); 
	}
	if(LIFE == -1) Reset();
}
void goDown()  
{
	walkSnake(DOWN);	
	Snakehead->location.x += 1;
	Snakehead->location.y += 0;
	Snakehead->location.d = DOWN;	
	gotoxy(Snakehead->location.x,Snakehead->location.y);
	printsnake();	
	fflush(stdout);
	delay();
	if(Snakehead->location.x == 25) { LIFE --; Snakehead->location.x = 1; }
	if(checkselfpunch()) 
	{  	
		initlocations();
		printf(ANSI_COLOR_GREEN);
		printf("OOPPS .. ..  snake got crashed with ownself ..");                
		initProgress();
		printf(ANSI_COLOR_YELLOW); 
	}
	if(LIFE == -1) Reset();
}
void goLeft()  
{
	walkSnake(LEFT);	
	Snakehead->location.x += 0;
	Snakehead->location.y -= 1;
	Snakehead->location.d = LEFT;	
	gotoxy(Snakehead->location.x,Snakehead->location.y);
	printsnake();
	fflush(stdout);
	delay();
	if(Snakehead->location.y == 0) { LIFE --; Snakehead->location.y = 59; }
	if(checkselfpunch()) 
	{  
		initlocations();
		printf(ANSI_COLOR_GREEN);
		printf("OOPPS .. ..  snake got crashed with ownself .."); 
		initProgress();
		printf(ANSI_COLOR_YELLOW); 
	}
	if(LIFE == -1) Reset();
}
void goUp()    
{
	walkSnake(UP);
	Snakehead->location.x -= 1;
	Snakehead->location.y += 0;
	Snakehead->location.d = UP;	
	gotoxy(Snakehead->location.x,Snakehead->location.y);
	printsnake();
	fflush(stdout);
	delay();
	if(Snakehead->location.x == 0) { LIFE --; Snakehead->location.x = 25; }
	if(checkselfpunch()) 
	{  
		initlocations();
		printf(ANSI_COLOR_GREEN);
		printf("OOPPS .. ..  snake got crashed with ownself .."); 
		initProgress();
		printf(ANSI_COLOR_YELLOW); 
	}
	if(LIFE == -1) Reset();
}

int delay()
{
	for(long int i = 0 ; i<80066660; i++);
}
/* upadate snake location for motion*/
void walkSnake(int dir)
{
	SNODE* hex = (SNODE*)malloc(sizeof(SNODE));
	hex = Snakehead;
	while(hex->next)
	{ 
		hex = hex->next;	
	} 
	while(hex->prev)
	{
		hex->location.x = hex->prev->location.x;
		hex->location.y = hex->prev->location.y; 		
		hex = hex->prev;
	}
}

void addnode(void)
{

	NEW = (SNODE*)malloc(sizeof(SNODE));
	SNODE *temp = (SNODE*)malloc(sizeof(SNODE));  
	if(Snakehead->next)
	{	
		NEW->prev = Snakehead;
		NEW->next = Snakehead->next; 
		Snakehead->next->prev = NEW;
		Snakehead->next = NEW;	
		Snakehead->next->location.x = Snakehead->location.x;
		Snakehead->next->location.y = Snakehead->location.y;
	}
	else
	{
		Snakehead->next = NEW;
		Snakehead->next->location.x = Snakehead->location.x;
		Snakehead->next->location.y = Snakehead->location.y;
		NEW->prev = Snakehead;
		NEW->next = NULL;
	}		
}
/* print snake body*/
void printsnake(void)
{
	SNODE* hex = (SNODE*)malloc(sizeof(SNODE));
	hex = Snakehead;
	printf(ANSI_COLOR_YELLOW);
	while(hex)
	{ 
		gotoxy(hex->location.x,hex->location.y);
		if(hex == Snakehead)
		{
			printf("0");
		}
		else
		{
			printf("X");
		}	
		hex = hex->next;	
	}	 
	printf(ANSI_COLOR_RESET);
}
/* Check either snake head touches its own body */
bool checkselfpunch(void)
{

	bool i = false;
	SNODE* hex = (SNODE*)malloc(sizeof(SNODE));
	hex = Snakehead;
	if(Snakehead->next == NULL || Snakehead->next->next == NULL)
	{
		return i;
	}
	else
	{
		hex = hex->next->next;
		while(hex)
		{
			if((Snakehead->location.x == hex->location.x) && (Snakehead->location.y == hex->location.y))	
			{ i =true; break; }	
			hex= hex->next;	
		}
	}
	return i;
}

void Reset()
{

	system("clear");
	printf("\n\n\n\n\n\n\n\n	ALL LIFES ARE GONE .. .. .. .. \n\n\n\n");
	printf("\n\n		THANK YOU FOR PLAYING .. .. YOUR SCORE : %d \n\n\n",SCORE);
	printf("\n\n			Press any key to continue .. .. .. .. \n\n\n\n");
	mygetch();
	system("clear");
	system("stty echo");                    // enable echo before exit 
	//system("setterm -cursor on");         // to enable the cursor  or we can use
	fputs("\e[?25h", stdout);               /* unhide the cursor */
	exit(0);
}

void print_score()
{
	gotoxy(26,10);
	printf("SCORE:  %d                   LIFE : %d",SCORE,LIFE);
}

/* End of File*/