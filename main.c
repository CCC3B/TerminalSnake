#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
static signed int CURRPOS = 0; // 1 is RIGHHT, -1 is LEFT, 2 is UP, -2 is DOWN
static int currsize = 0;
static long double duration=0;
static struct Trophy Tj;
static int trophfoodx;
static int trophfoody;
int globalflag=0;
int globalbuff=0;

struct Trophy {
  int size;
  char symbol;

};
typedef struct Snakeparts {
  char symb;
  signed int x;
 signed  int y;
} Snakeparts;
 
void MakeFood() {

        srand(time(NULL));
  Tj.size = 1 + rand() % 10;
  
 duration = rand() % 10;
 duration *=1000000;
    trophfoodx= rand() % (COLS-2);//two minus the edge
  trophfoody= rand() % (LINES-2);  
  Tj.symbol = '0';
  move(trophfoody+1,trophfoodx+1);
  addch(Tj.symbol);
  refresh();
    
    

}
void removeTrophy(struct Trophy tt)
{
  if (duration <= 0)
  {
     move(trophfoody+1,trophfoodx+1);
     addch(' ');
     refresh();
     duration =0;
     MakeFood();

  }


}
int edges(Snakeparts *shape){
  if (shape[currsize-1].y == LINES-1 || shape[currsize-1].x == COLS-1 || shape[currsize-1].y == 1 || shape[currsize-1].x == 1)
    {
      return 1;
    }
    if (mvinch(shape[currsize-1].y,shape[currsize-1].x) == '*')
    {
      return 2;
    }
  return 0;
}

void startsnek(Snakeparts *shape) {
   // raw();
   nodelay(stdscr, TRUE);
        int i=currsize-1;
          srand(time(NULL));
              static signed int a=1,b=0; 
              int k=rand() & 3;
              switch(k)
              {
                case 0:
                a=1;
                b=0;
                break;
                case 1:
                a=-1;
                b=0;
                 break;
                case 2:
                a=0;
                b=-1;
                break;
                case 3:
                a=0;
                b=1;
                break;
              }

      int ch=getch();
   do {
       
      if (ch==KEY_DOWN)
      {
          if(CURRPOS==2)
          {
              break;
          }
          a=0;
          b=1;
          CURRPOS=-2;
      }
        if(ch==KEY_UP)
      {
        if(CURRPOS==-2)
          {
              break;
          }
          a=0;
          b=-1;
          CURRPOS=2;
      }
        if(ch==KEY_RIGHT)
      {     
          if(CURRPOS==-1)
          {
              break;
          }
          a=1;
          b=0;
          CURRPOS=1;
      }
            if(ch==KEY_LEFT)
      {     
          if(CURRPOS==1)
          {
              break;
          }
          a=-1;
          b=0;
          CURRPOS=-1;
      }   
      if (globalflag ==1)
        {
          ch =NULL;
          clear();

          move(LINES/2,(COLS/2)+10);
          addstr("      *");
          move((LINES/2)-5,(COLS/2)-10);
          addstr("*      ");
          move((LINES/2)-5,(COLS/2));
          addstr("G A M E    O V E R");
          move((LINES/2)-5,(COLS/2)+20);
          addstr("      *");
          move((LINES/2)-10,(COLS/2));
          addstr("*      ");
          refresh();
          sleep(10);
          endwin();
          break;
        }
        else if (globalflag ==2){
                    ch =NULL;
          clear();

          move(LINES/2,(COLS/2)+10);
          addstr("      *");
          move((LINES/2)-5,(COLS/2)-10);
          addstr("*      ");
          move((LINES/2)-5,(COLS/2));
          addstr("Y O U   W I N ?!");
          move((LINES/2)-5,(COLS/2)+20);
          addstr("      *");
          move((LINES/2)-10,(COLS/2));
          addstr("*      ");
          refresh();
          sleep(10);
          endwin();
          break;
        }

      while((ch = getch()) == ERR)
      {
           move(0,COLS/2);
          addstr("SCORE:");
          move(0,(COLS/2)+6);
          printw("%d",currsize);

           if(i<0)
        {
            i=currsize-1;
        }
          removeTrophy(Tj);
 double DELAY=currsize*10000;// is desired intial speed

        
        move(shape[currsize-1].y,shape[currsize-1].x);
        
        if(shape[currsize-1].y == trophfoody+1 && shape[currsize-1].x == trophfoodx+1)//food was reached
        {
          move(trophfoody+1,trophfoodx+1);
          addch(' ');
          for (int i=0;i<Tj.size;i++)
          {
          shape[currsize].symb='*';
          shape[currsize].y=0;
          shape[currsize].x=0;
        
          shape[currsize].y=shape[currsize-1].y+b;//logical or current y with 0 to see which way a new a character needs to be inserted
          shape[currsize].x=shape[currsize-1].x+a;//logical or current x with 0 to see which way a new a character needs to be inserted
          
          currsize++;
        }
    
          duration=0;
        }
             
        signed int tempx=shape[currsize-1].x;//original x location of head
        signed int tempy=shape[currsize-1].y;//original y location of head
        shape[currsize-1].x+=a;
        shape[currsize-1].y+=b; //add the proper direction combination
           if (edges(shape) != 0)
        {
          globalflag=1;
          break;
        }
        if (currsize >= COLS/2)
        {
           globalflag=2;
          break;
        }
        if(currsize>25)
        {
          globalbuff+=5;
          DELAY-=10000;
        }
        addch(shape[currsize-1].symb);
        refresh();
        usleep(DELAY);
        duration-=DELAY;
        move(shape[currsize-1-i].y,shape[currsize-1-i].x);//move to the tail
        addch(' ');
        refresh();
        shape[currsize-1-i].x=tempx;//assign the original location of the head to the tail
        shape[currsize-1-i].y=tempy;

        i--;//decrement through snake parts, once 0th part is reached, the counter must be reset to avoid populating other empty parts         
      }
    } while(1);

}
    
  
int losingcon(Snakeparts *snekpart){
}


void makestring(Snakeparts *snekpart, char str[]) {
  for (int i = 0; i < COLS; i++) {
    str[i] = (snekpart + i)->symb;
  }
}
WINDOW *InitializeWorld(bool end) {

  initscr();
  noecho();
 cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
  static struct Snakeparts *shape;
  shape = (Snakeparts *)malloc(COLS * sizeof(Snakeparts));
  box(stdscr, 0, 0);
  move(LINES / 2, COLS / 2);

  for (int i = 0; i < 5; i++) {
    shape[i].symb = '*';
    shape[i].x = (COLS / 2) + i;
    shape[i].y = (LINES / 2);
    currsize++;
  }
  char snakestring[COLS];
  Tj.symbol=' ';
  makestring(shape, snakestring);
  addstr(snakestring);
  refresh();
  startsnek(shape);
  return stdscr;
  
  // keep refereshing */
}

int main(int ac, char *av[]) {
  bool con = true;
  InitializeWorld(con);
}


