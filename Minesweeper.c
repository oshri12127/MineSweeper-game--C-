/*
osher abergil
204634539
SHULA game.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define AROUND_COORDINATE 8

typedef enum  {FALSE=0,TRUE=1} BOOLEAN;
typedef struct
{
    int minesAround;
    BOOLEAN mine;
    BOOLEAN show;
} point;


point **board;
int size;
int num_shows;
static int coordinateX[]= {-1,0,1,1,1,0,-1,-1} ;
static int coordinateY[]= {1,1,1,0,-1,-1,-1,0};

void RecursionExpose(int x,int y);
void coverWithMines();
void place_mines();
void print_board();
void start_game();
BOOLEAN cover_point(int x,int y);
void build_board();
void fill_in_board();
void putNumbersAround(int x,int y);
BOOLEAN in_board(int x,int y);

int main()
{
    int num_mines;
    int i;
    printf("Enter a number for the board size(greater than 1)\n");
    scanf("%d",&size);
    while(size<=1)
    {
        printf("try again!!\n");
        printf("Enter a number for the board size(greater than 1)\n");
        scanf("%d",&size);
    }
    printf("Select the number of mines\n");
    scanf("%d",&num_mines);
    build_board();
    place_mines(num_mines);
    num_shows=size*size-num_mines;
    start_game();
    for(i=0; i<size; i++)
    {
        free(board[i]);
    }
    free(board);
    return 0;
}


void fill_in_board()
{
    int i,j;
    point *pp;
    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
        {
            pp=*(board+i)+j;
            (pp->minesAround)=0;
            (pp->mine)=FALSE;
            (pp->show)=FALSE;
        }

}

BOOLEAN in_board(int x,int y)
{
    return (x<size && x>=0 && y<size && y>=0 );
}

void putNumbersAround(int x,int y)
{
    point *po;
    int i,tempX,tempY;
    for(i=0; i<AROUND_COORDINATE; i++)
    {
        tempX=x+coordinateX[i];
        tempY=y+coordinateY[i];
        if(in_board(tempX,tempY)==TRUE)
        {
            po=*(board+tempX)+tempY;
            (po->minesAround)++;
        }

    }
}

void place_mines(int num_mines)
{
    point *p;
    int i,x,y;
    srand(time(0));

    for(i=0; i<num_mines; i++)
    {
        x=rand()%size;
        y=rand()%size;
        p=*(board+x)+y;
        if((p->mine)==FALSE)
        {
            (p->mine)=TRUE;
            putNumbersAround(x,y);
        }
        else
            i--;
    }
}

void build_board()
{
    int i;
    board=(point **)malloc(size * sizeof(point *));
    if(board==NULL)
    {
        printf("The program fall\n");
        exit(1);
    }
    //lines
    for(i=0; i<size; i++)
    {
        board[i]=(point *)malloc(size * sizeof(point ));
        if(board[i]==NULL)
        {
            printf("The program fall\n");
            exit(1);
        }
    }
    fill_in_board();
}

BOOLEAN cover_point(int x,int y)
{
    point *pp=*(board+x)+y;
    if(pp->show==FALSE)//new place
    {
        if(pp->mine==TRUE)//up to mine
        {
            printf("\nGAME OVER!!!!");
            coverWithMines();
            print_board();
            return TRUE;
        }
        else//not mine
        {

            if((pp->minesAround)==0)
                RecursionExpose(x,y);//exposes the points on the board from (x,y) until (x,y) will be around by numbers.
            else
            {
                (pp->show)=TRUE;
                num_shows--;
            }
        }
    }
    return FALSE;
}
void start_game()
{
    int x,y;
    BOOLEAN boom=FALSE;
    while(boom==FALSE)
    {
        print_board();
        if (num_shows==0)
        {
            boom=TRUE;
            printf("\nYOU WIN!!!!!");
            coverWithMines();
            print_board();
        }

        else
        {
            printf("choose your step(x and y):\n");
            scanf("%d %d",&x,&y);
            if(in_board(x-1,y-1))
                boom=cover_point(x-1,y-1);
            else
                printf("your step is illegal \n choose 2 numbers between 1-%d\n",size);
        }
    }
}


void print_board()
{
    int i,j;
    char cNum;
    point *pp;
    for(i=0; i<size; i++)
    {
        printf("\n   +");
        for(j=0; j<size; j++)
        {

            printf("---+");
        }
        putchar('\n');
        printf(" %d",i+1);

        for(j=0; j<size+1; j++)
        {
            pp=*(board+i)+j;
            if(pp->show==TRUE)
            {

                if(pp->mine==TRUE)
                    cNum='X';

                else
                    cNum=pp->minesAround+'0';
            }
            else
                cNum=' ';
            if(j==size)
                cNum=' ';
            printf(" | %c",cNum);
        }
    }
    putchar('\n');
    printf("   +");
    for(i=0; i<size; i++)
    {
        printf("---+");
    }
    putchar('\n');
    printf("  ");
    for(i=0; i<size; i++)
    {
        printf("%4d",i+1);
    }
    putchar('\n');
}

void RecursionExpose(int x,int y)
{
    int i;
    point *pp=*(board+x)+y;
    if(in_board(x,y)==TRUE && (pp->show==FALSE))
    {
        pp->show=TRUE;
        num_shows--;
        if(pp->minesAround==0)
        {
            for(i=0; i<AROUND_COORDINATE; i++)
                RecursionExpose(coordinateX[i]+x,coordinateY[i]+y);
        }
    }

}
void coverWithMines()
{
    int i,j;
    point *pp;
    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
        {
            pp=*(board+i)+j;
            if((pp->mine)==TRUE)
            {
                (pp->show)=TRUE;
            }
        }

}

