#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

//变量定义
int N,M,moveu[100]={0},mover[100]={0},movel[100]={0},moved[100]={0};

int CNT=0;

int jbq=0;

int jsqw,tc;
bool zq=0,BX=0;

struct mine_box {
	char type;
		// '*'代表地雷，n代表周围有地雷的地雷数（n=0-8）
	char bMarked,bOpened;
		// 是否被标记,是否被打开
}; //吉林路每一个的状态

mine_box mine_array[805][805];

int CurrentRow, CurrentCol;
// 记录当前光标的位置（分别代表行、列）

int openedBlank = 0;
// 记录被掀开的格子数

//函数声明



 /*将光标定位到屏幕上的某个指定位置的坐标上*/
void gotoxy(int x,int y){
    CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;
	HANDLE    hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}

/* 显示一个格子的内容*/
void printBox(struct mine_box mb){

 if(mb.bOpened == 0 && mb.bMarked == 0)printf(" □");
 // 格子没被掀开也没做标记

  else if(mb.bMarked == 1)printf("√ ");
 // 格子被标记一次

  else if(mb.bMarked == 2)printf("？ ");
 // 格子被标记两次

  else switch(mb.type) {
 // 格子被掀开，显示格子中的内容

    case '*':{
		if( !BX ){
			printf(" ⊕");
			zq=0;
		}
	}break;
   // 格子中有地雷

    case 0:printf("　 "),zq=1; break;
    // 格子没有地雷并且四周也没有地雷
	case 1:printf(" 1 "),zq=0; break;
	case 2:printf(" 2 "),zq=0; break;
	case 3:printf(" 3 "),zq=0; break;
	case 4:printf(" 4 "),zq=0; break;
	case 5:printf(" 5 "),zq=0; break;
	case 6:printf(" 6 "),zq=0; break;
	case 7:printf(" 7 "),zq=0; break;
	case 8:printf(" 8 "),zq=0; break;


	}
}

/* 刷新屏幕 */
void refreshScreen(int state){
	 int i, j;
	 gotoxy(0, 0);
	 for(int K = 0; K < 10; K++) printf("\t\t\t\t\t\t\t\t\t\t\n");
	 gotoxy(0, 0);
	 printf("┏ ━ ");
	 for(i = 1; i < N; i++) printf("┳ ━ ");
	     printf("┓\n");
	 for(i = 0; i < M; i++) {
	 	  printf("┃");

		    for(j = 0; j < N; j++) {
	          if(state == -1 && mine_array[i][j].bMarked == 1 && mine_array[i][j].type != '*') {
			  printf("¤ ");
			  // 标记错了地雷
			  continue;
		    }

		  if(state != 0) {
              // 游戏结束，将所有的盒子掀开显示其中内容
      		  mine_array[i][j].bOpened = 1;
				mine_array[i][j].bMarked = 0;
	      }
		  printBox(mine_array[i][j]);
		  printf("┃");
     }
	    if(i < M-1) {
	     printf("\n┣ ");
	     for(j = 1; j < N; j++) {
	       printf("━ ╋ ");
	     }
	     printf("━ ┫\n");
         }
	    else {
	   printf("\n┗ ");
	      for(j = 1; j < N; j++) {
  	       printf("━ ┻ ");
	     }
	   printf("━ ┛\n");
	   }
      }
	 printf("按键指南：A左移，D右移，W上移，S下移，X翻开，C标记，Q退出\n");
}


/* 将光标移动到第row行第col列的格子上 */
void MoveTo(int row, int col){
	 CurrentRow = row;CurrentCol = col;
	 gotoxy(CurrentCol*4+2,CurrentRow*2+1);
}

/*将光标位置向上移动一格*/
void MoveUp(){
    if(CurrentRow > 0) {
	    CurrentRow --;
		MoveTo(CurrentRow, CurrentCol);
		moveu[jbq]=1;
    }
    else moveu[jbq]=0;
}

/*将光标位置向下移动一格*/
void MoveDown(){
    if(CurrentRow < M-1) {
	    CurrentRow ++;
		MoveTo(CurrentRow, CurrentCol);
		moved[jbq]=1;
    }
    else moved[jbq]=0;
}

/*将光标位置向左移动一格*/
void MoveLeft(){
    if(CurrentCol > 0) {
	    CurrentCol--;
		MoveTo(CurrentRow, CurrentCol);
		movel[jbq]=1;
    }
    else movel[jbq]=0;
}

/*将光标位置向右移动一格*/
void MoveRight(){
    if(CurrentCol < N-1) {
	    CurrentCol ++;
		MoveTo(CurrentRow, CurrentCol);
		mover[jbq]=1;
    }
    else mover[jbq]=0;
}



/*检测当前位置是否合法*/
int openMine(){
    int saveRow = CurrentRow, saveCol = CurrentCol;
	if(mine_array[CurrentRow][CurrentCol].bOpened) return 0;
	mine_array[CurrentRow][CurrentCol].bOpened = 1;
	mine_array[CurrentRow][CurrentCol].bMarked = 0;
	if(mine_array[CurrentRow][CurrentCol].type == '*' && !BX ) {
	    refreshScreen(-1);
		MoveTo(M+1, 0);
		printf("失败！游戏结束\n");
		system("pause");
		exit(0);
	}
	printBox(mine_array[CurrentRow][CurrentCol]);
	MoveTo(CurrentRow,CurrentCol);
	//进一步要做的是当掀开一个type=0的空格子时，将其周围没有地雷的空格子自动掀开
	return 1;
}

/*插旗子标注*/
void markMine(){
    if(mine_array[CurrentRow][CurrentCol].bOpened == 1) return;

	if(mine_array[CurrentRow][CurrentCol].bMarked == 0) mine_array[CurrentRow][CurrentCol].bMarked = 1;

	else if(mine_array[CurrentRow][CurrentCol].bMarked == 1)mine_array[CurrentRow][CurrentCol].bMarked = 2;

	else if(mine_array[CurrentRow][CurrentCol].bMarked ==2)mine_array[CurrentRow][CurrentCol].bMarked = 0;

    printBox(mine_array[CurrentRow][CurrentCol]);
	MoveTo(CurrentRow, CurrentCol);
}

/*自动开启0格*/
void search(){
	jbq++;
	if(zq==1){
		BX=1;

        MoveLeft(); if(openMine()==1) openedBlank++,search(),jbq--;

        MoveDown(); if(openMine()==1) openedBlank++,search(),jbq--;

		if(movel[jbq]==1) {MoveRight();if(openMine()==1) openedBlank++,search(),jbq--;}

		MoveRight();if(openMine()==1) openedBlank++,search(),jbq--;

		if(moved[jbq]==1) {MoveUp();   if(openMine()==1) openedBlank++,search(),jbq--;}

		MoveUp();   if(openMine()==1) openedBlank++,search(),jbq--;

		if(mover[jbq]==1) {MoveLeft(); if(openMine()==1) openedBlank++,search(),jbq--;}

		MoveLeft(); if(openMine()==1) openedBlank++,search(),jbq--;

		if(moveu[jbq]==1) {MoveDown(); if(openMine()==1) openedBlank++,search(),jbq--;}

		MoveRight();

    }

}

int main(){
	printf("C程序设计大作业二——基于图形设备接口函数库的winmine游戏\n\n");
	printf("学生信息：\n姓名:王偲怡\n学号：2018301332\n班号：sc011801");
    printf("程序操作简介：\n");
    printf("按键指南：A左移，D右移，W上移，S下移\nX翻开，C标记，Q退出\n\n");
    printf("注意事项：\n");
    printf("请将输入法置为英文模式\n\n");

    int num, i, j, row, col, count;
    printf("输入长宽: ");
    scanf("%d%d",&N,&M);
	printf("输入地雷数: ");
	scanf("%u", &num);
	if(num > N*M) {
	    printf("地雷数超限\n");
	    return -1;
	}
	memset((void*)mine_array, 0, N*M*sizeof(struct mine_box));
	//随机设置num个地雷的位置
	srand((unsigned)time(NULL));
	for(i=0; i<num; i++) {
	row = rand()%M;
	col = rand()%N;
	if(mine_array[row][col].type == 0)mine_array[row][col].type = '*';
	else
	 // 已经有雷了，重新取下一个格子
	 i--;}
	 // 计算每个非雷格子周围的地雷数
	 for(row=0; row<M; row++){
         for(col = 0; col < N; col++) {
             if(mine_array[row][col].type == '*') {
			     for(i = row-1; i <= row+1; i++) {
				     for(j = col-1; j <= col+1; j++) {
					     if(i >= 0 && j >= 0 && i < M && j < N && mine_array[i][j].type != '*') mine_array[i][j].type ++;
					 }
				 }
			 }
		 }
	 }
	 refreshScreen(0);
	 MoveTo(M/2, N/2);
     // 将光标移到中央的位置
	 do {
	   switch(getch()) {
	     case 'a':case 'A':MoveLeft();
	     break;
	     case 's':case 'S':MoveDown();
	     break;
	     case 'd':case 'D':MoveRight();
	     break;
	     case 'w':case 'W':MoveUp();
		 break;
	     case 'x':case 'X':if(openMine() == 1) {
     	   search();
     	   openedBlank++;
	       if(openedBlank >= N*M-num) {
	        //所有的空格都被掀开
	         refreshScreen(-1);
			 MoveTo(M+1, 0);
			 BX=1;
	         printf("成功！游戏结束。\n");
	         if(getch() == 'y') {
	         	gotoxy(0, 0);
				for(int K = 0; K < 10; K++) printf("\t\t\t\t\t\t\t\t\t\t\n");
			    CNT++;

			 }
	         system("pause");
		     exit(0);
           }
         }
	     break;
	     case 'c':case 'C':markMine();
	     break;
         case 'q':case 'Q':{
		 	MoveTo(M+1, 0);
	     	printf("是否退出？(y/n)");
	     	if(getch() == 'y'){
				return 0;
			}
		 }
		 break;
       }
       BX = 0;
	 }
	 while(1);
}

