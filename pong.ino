#include <stdarg.h>
#include "LedControl.h"

LedControl lc=LedControl(12,11,10,1);

//All bat parameters are in arrays, where the first parameter is bat 0 and the secodn is bat 1
int aPin = A1
int bPin = A2
int batSize[]={3,3};
int batPos[]={0,0};
int height=8; //Height (and width) of the matrix


//Score for player 0 and 1
int score[]={0,0};


//Position of the ball as X,Y
int ballPos[]={random(4,4),random(2,5),random(4,6)};

//Direction of the ball as dX,dY
int ballVec[]={random(1,1),random(2,2),random(5,5)};

//Useful function for formatting strings
void p(char *fmt, ... ){
        char buf[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 128, fmt, args);
        va_end (args);
        Serial.print(buf);
}


int moveBat(int batNum, int dir){
   //moves a bat
   //batNum is 0 or 1, 0 for left bat, 1 for right
   //dir is a number. -1 or 1 will move the bat up or down. Other numbers will be ignored
   //Function returns -1 if the bat hit an edge and couldn't move the full distance
   //   0 on success
   //   1 when given an incorrect value for dir
   if(value<498) {dir = -1;}
   if(value>600) {dir = 1;}
   if(value<=507 && value>=498) {dir = 0}
        
   if(dir==-1 || dir==1){
     batPos[batNum]+=dir;
     if(batPos[batNum]<0){
       batPos[batNum]=0;
       return -1;
     }
     if(batPos[batNum]+batSize[batNum]>height){
       batPos[batNum]=height-batSize[batNum];  
       return -1;
     }
     return 0;
   }
   return 1;
  
}


//Move the ball one step, bouncing if necessary
//returns -1 unless the ball hits a left or right edge
//If it hits the left-hand edge it returns 0
//If it hits the right-hand edge it returns 1
//If it hits a bat, it returns -1
int ballStep(){
  int next[]={0,0};
  next[0]=ballPos[0]+ballVec[0];
  next[1]=ballPos[1]+ballVec[1];
  int edgeNum=-1;
  
  
  //Check top/bottom
  if(next[1]<0 || next[1]>=height){
    p("Hit top/bottom\n");
    ballVec[1]*=-1;
  }
  //Now check bats...
  if(next[0]==0 && ballPos[1]>=batPos[0] && ballPos[1]<(batPos[0]+batSize[0])){
    ballVec[0]*=-1;
    Serial.println("Hit bat 0");
  }else if(next[0] < 0){
    p("Left edge hit\n");
    ballVec[0]*=-1;
    edgeNum=0;
  }
  if(next[0]==height-1 && ballPos[1]>=batPos[1] && ballPos[1]<batPos[1]+batSize[1]){
    ballVec[0]*=-1;
    Serial.println("Hit bat 1");
  }else if(next[0] >= height){
    p("Right edge hit\n");
    ballVec[0]*=-1;
    edgeNum=1;
  }
   
  ballPos[0]+=ballVec[0];
  ballPos[1]+=ballVec[1];
  return edgeNum;;
}

void drawGame(){
 lc.clearDisplay(0);

 //Bats
 for(int i=0; i<2; i++)
   for(int j=0; j<batSize[i];j++)
     lc.setLed(0,i*(height-1),j+batPos[i],true);
 
  //Ball
  lc.setLed(0,ballPos[0],ballPos[1],true);

}

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,1);
  /* and clear the display */
  lc.clearDisplay(0);
  Serial.begin(9600);
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);
}


void loop(){
  drawGame();
  int result;
  result=ballStep();
  if(result==0)
    score[1]+=1;
  if(result==1)
   score[0]+=1;
  p("Score is [%d,%d]\n",score[0],score[1]);
  
  //Read inputs here and use the moveBat function to move the bat
  
  //Can you think of a good way to show the score?
  
  //How about adding a restart button?
  
  //Can you stop the game when someone gets a maximum score (3? 5?)
  
  //Can you randomise the starting position?
 
  delay(170);
  
}





