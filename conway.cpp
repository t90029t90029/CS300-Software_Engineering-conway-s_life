// CS300 Program 2 for build a conway's game of life
// Shang-Chun, Lin 2020
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

//max size (COLS-1,LINES-1)
long timing = 500000;	//0.5 s
int running = 1;	// q-switch
int paused = 1;		//1 = pausedd mode
int one_step = 0;	//1 = taking one step

//insertion cursor position
int px,py;

void init(char ** & table);
void make_table(char** & table);
void delete_table(char ** & table);
void process(char ** & table);
void event(char ** & table);
void refresh_screen(char ** table);

using namespace std;

int main(){
  char ** table = NULL;

  init(table);
  while(running){
    process(table);
    event(table);
    refresh_screen(table);
  }

  endwin();
  delete_table(table);  
  return 0;
}

void delete_table(char ** & table){
  if(!table){
    return;
  }

  for(int i=0;i<LINES;++i){
    delete []table[i];
    table[i] = NULL;
  }

  delete []table;
  table = NULL;

  return;
}

void make_table(char** & table){
  if(table){
    delete_table(table);
  }
  
  table = new char*[LINES];

  for(int i=0;i<LINES;++i){
    table[i] = new char[COLS];
  }

  return;
}

void init(char ** & table){
  initscr();
  noecho();
  raw();
  keypad(stdscr,TRUE);
  nodelay(stdscr,TRUE);

  //Alloc 
  make_table(table);

  for(int i=0;i<LINES;++i){
    for(int j=0;j<COLS;++j){
      table[i][j] = ' ';
    }
  }

  //Base position of cursor
  px = COLS/2;
  py = LINES/2;
  wmove(stdscr,py,px);

  refresh();
  return;
}

void process(char ** & table){
  int count = 0;
  char ** next = NULL;
  if(paused && !one_step){
    return;
  }

  make_table(next);

  for(int i=0;i<LINES;++i){
    for(int j=0;j<COLS;++j){

      //count the number of neighbor
      if(table[i][j] == 'X'){		//we don't count the cell itself
        --count;
      }
      
      //check the corner first
      if(i==0 && j==0){
        for(int a=0;a<2;++a){
          for(int b=0;b<2;++b){
	    if(table[i+a][j+b] == 'X'){
	      ++count;
	    }
	  }
        }
      }
      else if(i==LINES-1 && j==0){
        for(int a=-1;a<1;++a){
          for(int b=0;b<2;++b){
	    if(table[i+a][j+b] == 'X'){
	      ++count;
	    }
	  }
        }
      }
      else if(i==0 && j==COLS-1){
        for(int a=0;a<2;++a){
          for(int b=-1;b<1;++b){
	    if(table[i+a][j+b] == 'X'){
	      ++count;
	    }
	  }
        }
      }
      else if(i==LINES-1 && j==COLS-1){
        for(int a=-1;a<1;++a){
          for(int b=-1;b<1;++b){
	    if(table[i+a][j+b] == 'X'){
	      ++count;
	    }
	  }
        }
      }
      //check the edge
      else if(i==0){
        for(int a=0;a<2;++a){
          for(int b=-1;b<2;++b){
	    if(table[i+a][j+b] == 'X'){
	      ++count;
	    }
	  }
        }
      }
      else if(j==0){
        for(int a=-1;a<2;++a){
          for(int b=0;b<2;++b){
	    if(table[i+a][j+b] == 'X'){
	      ++count;
	    }
	  }
        }
      }
      else if(i==LINES-1){
        for(int a=-1;a<1;++a){
          for(int b=-1;b<2;++b){
	    if(table[i+a][j+b] == 'X'){
	      ++count;
	    }
	  }
        }
      }
      else if(j==COLS-1){
        for(int a=-1;a<2;++a){
          for(int b=-1;b<1;++b){
	    if(table[i+a][j+b] == 'X'){
	      ++count;
	    }
	  }
        }
      }
      //without boundary
      else{
        for(int a=-1;a<2;++a){
          for(int b=-1;b<2;++b){
	    if(table[i+a][j+b] == 'X'){
	      ++count;
	    }
	  }
        }
      }
      //generate the next universe
      if(count == 3){		//must be live
        next[i][j] = 'X';
      }
      else if(count == 2){		//stay the state
        next[i][j] = table[i][j];
      }
      else{
        next[i][j] = ' ';	//must be dead
      }
      count = 0;
    }
  }

  if(one_step){
    one_step = 0;
  }

  delete_table(table);
  table = next;

  usleep(timing);
  refresh_screen(table);
  return;
}

void event(char** & table){
  int key;
  key = getch();

  if(key == ERR){
    return;
  }

  switch((key)){

    case KEY_DOWN :
      if(paused && py<LINES-1){
        ++py;
	wmove(stdscr,py,px);
      }
      break;

    case KEY_UP :
      if(paused && py>0){
        --py;
	wmove(stdscr,py,px);
      }
      break;

    case KEY_LEFT :
      if(paused && px>0){
        --px;
	wmove(stdscr,py,px);
      }
      break;

    case KEY_RIGHT :
      if(paused && px<COLS-1){
        ++px;
	wmove(stdscr,py,px);
      }
      break;

    case 'q' :
    case 'Q' :
      running = 0;
      break;

    case 'p' :
    case 'P' :
      paused = !paused;
      break;
    
    case 'x' :
    case 'X' :
      if(paused){
	if(table[py][px] == ' '){
          table[py][px] = 'X';
	}
	else if(table[py][px] == 'X'){
          table[py][px] = ' ';
	}
	mvaddch(py,px,table[py][px]); 
      }
      refresh();
      break;

    case 'n' :
    case 'N' :
      if(paused){
        one_step = 1;
      }
      break;

    default:
      break;
  }
  return;
}

void refresh_screen(char ** table){
  for(int i=0;i<LINES;++i){
    for(int j=0;j<COLS;++j){
      mvaddch(i,j,table[i][j]);
    }
  }
  wmove(stdscr,py,px);
  refresh();
  return;
}
