#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

//��������
int N,M,moveu[100]={0},mover[100]={0},movel[100]={0},moved[100]={0};

int CNT=0;

int jbq=0;

int jsqw,tc;
bool zq=0,BX=0;

struct mine_box {
	char type;
		// '*'������ף�n������Χ�е��׵ĵ�������n=0-8��
	char bMarked,bOpened;
		// �Ƿ񱻱��,�Ƿ񱻴�
}; //����·ÿһ����״̬

mine_box mine_array[805][805];

int CurrentRow, CurrentCol;
// ��¼��ǰ����λ�ã��ֱ�����С��У�

int openedBlank = 0;
// ��¼���ƿ��ĸ�����

//��������



 /*����궨λ����Ļ�ϵ�ĳ��ָ��λ�õ�������*/
void gotoxy(int x,int y){
    CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;
	HANDLE    hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}

/* ��ʾһ�����ӵ�����*/
void printBox(struct mine_box mb){

 if(mb.bOpened == 0 && mb.bMarked == 0)printf(" ��");
 // ����û���ƿ�Ҳû�����

  else if(mb.bMarked == 1)printf("�� ");
 // ���ӱ����һ��

  else if(mb.bMarked == 2)printf("�� ");
 // ���ӱ��������

  else switch(mb.type) {
 // ���ӱ��ƿ�����ʾ�����е�����

    case '*':{
		if( !BX ){
			printf(" ��");
			zq=0;
		}
	}break;
   // �������е���

    case 0:printf("�� "),zq=1; break;
    // ����û�е��ײ�������Ҳû�е���
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

/* ˢ����Ļ */
void refreshScreen(int state){
	 int i, j;
	 gotoxy(0, 0);
	 for(int K = 0; K < 10; K++) printf("\t\t\t\t\t\t\t\t\t\t\n");
	 gotoxy(0, 0);
	 printf("�� �� ");
	 for(i = 1; i < N; i++) printf("�� �� ");
	     printf("��\n");
	 for(i = 0; i < M; i++) {
	 	  printf("��");

		    for(j = 0; j < N; j++) {
	          if(state == -1 && mine_array[i][j].bMarked == 1 && mine_array[i][j].type != '*') {
			  printf("�� ");
			  // ��Ǵ��˵���
			  continue;
		    }

		  if(state != 0) {
              // ��Ϸ�����������еĺ����ƿ���ʾ��������
      		  mine_array[i][j].bOpened = 1;
				mine_array[i][j].bMarked = 0;
	      }
		  printBox(mine_array[i][j]);
		  printf("��");
     }
	    if(i < M-1) {
	     printf("\n�� ");
	     for(j = 1; j < N; j++) {
	       printf("�� �� ");
	     }
	     printf("�� ��\n");
         }
	    else {
	   printf("\n�� ");
	      for(j = 1; j < N; j++) {
  	       printf("�� �� ");
	     }
	   printf("�� ��\n");
	   }
      }
	 printf("����ָ�ϣ�A���ƣ�D���ƣ�W���ƣ�S���ƣ�X������C��ǣ�Q�˳�\n");
}


/* ������ƶ�����row�е�col�еĸ����� */
void MoveTo(int row, int col){
	 CurrentRow = row;CurrentCol = col;
	 gotoxy(CurrentCol*4+2,CurrentRow*2+1);
}

/*�����λ�������ƶ�һ��*/
void MoveUp(){
    if(CurrentRow > 0) {
	    CurrentRow --;
		MoveTo(CurrentRow, CurrentCol);
		moveu[jbq]=1;
    }
    else moveu[jbq]=0;
}

/*�����λ�������ƶ�һ��*/
void MoveDown(){
    if(CurrentRow < M-1) {
	    CurrentRow ++;
		MoveTo(CurrentRow, CurrentCol);
		moved[jbq]=1;
    }
    else moved[jbq]=0;
}

/*�����λ�������ƶ�һ��*/
void MoveLeft(){
    if(CurrentCol > 0) {
	    CurrentCol--;
		MoveTo(CurrentRow, CurrentCol);
		movel[jbq]=1;
    }
    else movel[jbq]=0;
}

/*�����λ�������ƶ�һ��*/
void MoveRight(){
    if(CurrentCol < N-1) {
	    CurrentCol ++;
		MoveTo(CurrentRow, CurrentCol);
		mover[jbq]=1;
    }
    else mover[jbq]=0;
}



/*��⵱ǰλ���Ƿ�Ϸ�*/
int openMine(){
    int saveRow = CurrentRow, saveCol = CurrentCol;
	if(mine_array[CurrentRow][CurrentCol].bOpened) return 0;
	mine_array[CurrentRow][CurrentCol].bOpened = 1;
	mine_array[CurrentRow][CurrentCol].bMarked = 0;
	if(mine_array[CurrentRow][CurrentCol].type == '*' && !BX ) {
	    refreshScreen(-1);
		MoveTo(M+1, 0);
		printf("ʧ�ܣ���Ϸ����\n");
		system("pause");
		exit(0);
	}
	printBox(mine_array[CurrentRow][CurrentCol]);
	MoveTo(CurrentRow,CurrentCol);
	//��һ��Ҫ�����ǵ��ƿ�һ��type=0�Ŀո���ʱ��������Χû�е��׵Ŀո����Զ��ƿ�
	return 1;
}

/*�����ӱ�ע*/
void markMine(){
    if(mine_array[CurrentRow][CurrentCol].bOpened == 1) return;

	if(mine_array[CurrentRow][CurrentCol].bMarked == 0) mine_array[CurrentRow][CurrentCol].bMarked = 1;

	else if(mine_array[CurrentRow][CurrentCol].bMarked == 1)mine_array[CurrentRow][CurrentCol].bMarked = 2;

	else if(mine_array[CurrentRow][CurrentCol].bMarked ==2)mine_array[CurrentRow][CurrentCol].bMarked = 0;

    printBox(mine_array[CurrentRow][CurrentCol]);
	MoveTo(CurrentRow, CurrentCol);
}

/*�Զ�����0��*/
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
	printf("C������ƴ���ҵ����������ͼ���豸�ӿں������winmine��Ϸ\n\n");
	printf("ѧ����Ϣ��\n����:������\nѧ�ţ�2018301332\n��ţ�sc011801");
    printf("���������飺\n");
    printf("����ָ�ϣ�A���ƣ�D���ƣ�W���ƣ�S����\nX������C��ǣ�Q�˳�\n\n");
    printf("ע�����\n");
    printf("�뽫���뷨��ΪӢ��ģʽ\n\n");

    int num, i, j, row, col, count;
    printf("���볤��: ");
    scanf("%d%d",&N,&M);
	printf("���������: ");
	scanf("%u", &num);
	if(num > N*M) {
	    printf("����������\n");
	    return -1;
	}
	memset((void*)mine_array, 0, N*M*sizeof(struct mine_box));
	//�������num�����׵�λ��
	srand((unsigned)time(NULL));
	for(i=0; i<num; i++) {
	row = rand()%M;
	col = rand()%N;
	if(mine_array[row][col].type == 0)mine_array[row][col].type = '*';
	else
	 // �Ѿ������ˣ�����ȡ��һ������
	 i--;}
	 // ����ÿ�����׸�����Χ�ĵ�����
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
     // ������Ƶ������λ��
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
	        //���еĿո񶼱��ƿ�
	         refreshScreen(-1);
			 MoveTo(M+1, 0);
			 BX=1;
	         printf("�ɹ�����Ϸ������\n");
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
	     	printf("�Ƿ��˳���(y/n)");
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

