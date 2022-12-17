#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <cstring>
#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;
using namespace cv;

int N, M, num, moveu[505] = { 0 }, mover[505] = { 0 }, movel[505] = { 0 }, moved[505] = { 0 }, CNT = 0, jbq = 0, jsqw, tc;
int Lv_P1 = 0, Life = 3;
bool zq = 0, BX = 0;
int openedBlank = 0;

int CurrentRow, CurrentCol;//记录光标 

struct mine_box {
	char type;//*为地雷，数字为周边地雷的数目 
	char be_Marked, be_Opened;

};
mine_box mine_array[505][505];

void Init_Fd(int lf, int lv, int nn, int mm, int nu);//操作核心函数
void MoveTo(int row, int col);//游戏内光标引导函数
void MoveUp();
void MoveDown();
void MoveLeft();
void MoveRight();
int openMine();
void markMine();//其他操作函数(上下左右开标）
void Auto();//自动搜索（仍有bug）
void _Goto(int x, int y);//菜单界面坐标引导
void refreshScreen(int state);//屏幕图像更新
void printBox(struct mine_box mb);//图像信息翻译
void  successpic();//成功后弹出图片
void  failpic();//失败后弹出图片
void _Goto(int x, int y) {
	CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;
	HANDLE    hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void printBox(struct mine_box mb) {

	if (mb.be_Opened == 0 && mb.be_Marked == 0)printf(" □");
	// 格子没被掀开也没做标记

	else if (mb.be_Marked == 1)printf("√ ");
	// 格子被标记一次

	else if (mb.be_Marked == 2)printf("？ ");
	// 格子被标记两次

	else switch (mb.type) {
		// 格子被掀开，显示格子中的内容 

	case '*': {
		if (!BX) {
			cout << " ⊕";
			zq = 0;
		}
	}break;
		// 格子中有地雷

	case 0:printf("　 "), zq = 1; break;
		// 格子没有地雷并且四周也没有地雷
	case 1:printf(" 1 "), zq = 0; break;
	case 2:printf(" 2 "), zq = 0; break;
	case 3:printf(" 3 "), zq = 0; break;
	case 4:printf(" 4 "), zq = 0; break;
	case 5:printf(" 5 "), zq = 0; break;
	case 6:printf(" 6 "), zq = 0; break;
	case 7:printf(" 7 "), zq = 0; break;
	case 8:printf(" 8 "), zq = 0; break;


	}
}
void refreshScreen(int state) {
	int i, j;
	_Goto(0, 0);
	for (int K = 0; K < 100; K++) cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n";
	_Goto(0, 0);
	cout << "┏ ━ ";
	for (i = 1; i < N; i++) cout << "┳ ━ ";
	cout << "┓\n";
	for (i = 0; i < M; i++) {
		cout << "┃";

		for (j = 0; j < N; j++) {
			if (state == -1 && mine_array[i][j].be_Marked == 1 && mine_array[i][j].type != '*') {
				cout << "¤ ";
				continue;
			}

			if (state != 0) {
				// 游戏结束，将所有的盒子掀开显示其中内容
				mine_array[i][j].be_Opened = 1;
				mine_array[i][j].be_Marked = 0;
			}
			printBox(mine_array[i][j]);
			cout << "┃";
		}
		if (i < M - 1) {
			cout << "\n┣ ";
			for (j = 1; j < N; j++) {
				cout << "━ ╋ ";
			}
			cout << "━ ┫\n";
		}
		else {
			cout << "\n┗ ";
			for (j = 1; j < N; j++) {
				cout << "━ ┻ ";
			}
			cout << "━ ┛\n";
		}
	}
	cout << "操作指南：8上移，2下移，4左移，6右移" << endl << "          5翻开，0标记当前格，*键退出" << endl;
	if (Lv_P1 != 0) cout << "当前难度：LV" << Lv_P1 << "(大小：" << M << '*' << N << "雷数：" << num << ')' << "防爆服剩余：" << Life-1 << endl;
}

void MoveTo(int row, int col) {
	CurrentRow = row; CurrentCol = col;
	_Goto(CurrentCol * 4 + 2, CurrentRow * 2 + 1);
}

//光标操作 
void MoveUp() {
	if (CurrentRow > 0) {
		CurrentRow--;
		MoveTo(CurrentRow, CurrentCol);
		moveu[jbq] = 1;
	}
	else moveu[jbq] = 0;
}

void MoveDown() {
	if (CurrentRow < M - 1) {
		CurrentRow++;
		MoveTo(CurrentRow, CurrentCol);
		moved[jbq] = 1;
	}
	else moved[jbq] = 0;
}

void MoveLeft() {
	if (CurrentCol > 0) {
		CurrentCol--;
		MoveTo(CurrentRow, CurrentCol);
		movel[jbq] = 1;
	}
	else movel[jbq] = 0;
}

void MoveRight() {
	if (CurrentCol < N - 1) {
		CurrentCol++;
		MoveTo(CurrentRow, CurrentCol);
		mover[jbq] = 1;
	}
	else mover[jbq] = 0;
}

int openMine() {
	int saveRow = CurrentRow, saveCol = CurrentCol;
	if (mine_array[CurrentRow][CurrentCol].be_Opened || mine_array[CurrentRow][CurrentCol].be_Marked) return 0;
	mine_array[CurrentRow][CurrentCol].be_Opened = 1;
	mine_array[CurrentRow][CurrentCol].be_Marked = 0;
	if (mine_array[CurrentRow][CurrentCol].type == '*' && !BX) {
		refreshScreen(-1);
		MoveTo(M + 1, 0);
		if (Life > 1) {
			Life--;
			cout << "失败，按任意键重新挑战";//加图 
			failpic();
			system("pause");
			Init_Fd(Life, Lv_P1, N, M, num);
			exit(0);
		}
		else {
			cout << "失败！游戏结束\n";//加图
			failpic();
			system("pause");
			exit(0);
		}
	}
	printBox(mine_array[CurrentRow][CurrentCol]);
	MoveTo(CurrentRow, CurrentCol);
	return 1;
}

void markMine() {
	if (mine_array[CurrentRow][CurrentCol].be_Opened == 1) return;

	if (mine_array[CurrentRow][CurrentCol].be_Marked == 0) mine_array[CurrentRow][CurrentCol].be_Marked = 1;

	else if (mine_array[CurrentRow][CurrentCol].be_Marked == 1) mine_array[CurrentRow][CurrentCol].be_Marked = 2;

	else if (mine_array[CurrentRow][CurrentCol].be_Marked == 2) mine_array[CurrentRow][CurrentCol].be_Marked = 0;

	printBox(mine_array[CurrentRow][CurrentCol]);
	MoveTo(CurrentRow, CurrentCol);
}

void Auto() {
	jbq++;
	if (zq == 1) {
		BX = 1;

		MoveLeft(); if (openMine() == 1) openedBlank++, Auto(), jbq--;

		MoveDown(); if (openMine() == 1) openedBlank++, Auto(), jbq--;

		if (movel[jbq] == 1) { MoveRight(); if (openMine() == 1) openedBlank++, Auto(), jbq--; }

		MoveRight(); if (openMine() == 1) openedBlank++, Auto(), jbq--;

		if (moved[jbq] == 1) { MoveUp();   if (openMine() == 1) openedBlank++, Auto(), jbq--; }

		MoveUp();   if (openMine() == 1) openedBlank++, Auto(), jbq--;

		if (mover[jbq] == 1) { MoveLeft(); if (openMine() == 1) openedBlank++, Auto(), jbq--; }

		MoveLeft(); if (openMine() == 1) openedBlank++, Auto(), jbq--;

		if (moveu[jbq] == 1) { MoveDown(); if (openMine() == 1) openedBlank++, Auto(), jbq--; }

		MoveRight();

	}

}
void Init_Fd(int lf, int lv, int nn, int mm, int nu) {
	CNT = 0;
	jbq = 0;
	openedBlank = 0;
	memset(moveu, 0, 505 * sizeof(int));
	memset(moved, 0, 505 * sizeof(int));
	memset(mover, 0, 505 * sizeof(int));
	memset(movel, 0, 505 * sizeof(int));
	BX = 0;
	zq = 0;
	int i, j, row, col;
	memset((void*)mine_array, 0, N * M * sizeof(struct mine_box));
	for (i = 0; i < mm; i++) {
		for (j = 0; j < nn; j++) {
			mine_array[i][j].be_Marked = 0;
			mine_array[i][j].be_Opened = 0;
			mine_array[i][j].type = 0;
		}
	}//初始化

	srand((unsigned)time(NULL));
	for (i = 0; i < nu; i++) {
		row = rand() % mm;
		col = rand() % nn;
		if (mine_array[row][col].type == 0)mine_array[row][col].type = '*';
		else i--;
	}//随机地雷 

	for (row = 0; row < M; row++) {
		for (col = 0; col < N; col++) {
			if (mine_array[row][col].type == '*') {
				for (i = row - 1; i <= row + 1; i++) {
					for (j = col - 1; j <= col + 1; j++) {
						if (i >= 0 && j >= 0 && i < M && j < N && mine_array[i][j].type != '*') mine_array[i][j].type++;
					}
				}
			}
		}
	}//其他格子设置 

	refreshScreen(0);
	MoveTo(M / 2, N / 2);

	do {
		switch (_getch()) {
		case '4':MoveLeft();
			break;
		case '2':MoveDown();
			break;
		case '6':MoveRight();
			break;
		case '8':MoveUp();
			break;
		case '5':if (openMine() == 1) {
			Auto();
			openedBlank++;
			if (openedBlank >= nn * mm - nu) {
				//所有的空格都被掀开
				refreshScreen(-1);
				MoveTo(M + 1, 0);
				BX = 1;
				if (lv == 0) { printf("成功！游戏结束。\n"); successpic(); }//加图 
				else if (lv == 1) {
					{printf("成功！按任意键进入下一关\n"); successpic(); }//加图
					system("pause");
					Lv_P1++;
					N = 16;
					M = 16;
					num = 40;
					Init_Fd(Life, Lv_P1, 16, 16, 40);
				}
				else if (lv == 2) {
					{printf("成功！按任意键进入下一关\n"); successpic(); }//加图
					system("pause");
					Lv_P1++;
					N = 30;
					M = 16;
					num = 99;
					Init_Fd(Life, Lv_P1, 30, 16, 99);
				}
				else {
					printf("成功！\n");//加图
					successpic();
				}
				_Goto(0, 0);
				for (int K = 0; K < 100; K++) printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n");
				CNT++;
				//游戏成功 
				system("pause");
				exit(0);
			}
		}
				break;
		case '0':markMine();
			break;
		case '*': {
			MoveTo(M + 1, 0);
			cout << "\n是否退出？(1确认0取消)";
			if (_getch() == '1') {
				return;
			}
		}
				break;
		}
		BX = 0;
	} while (1);
}

void successpic()
{
	Mat image = imread("C:\\Users\\As\\Desktop\\homework2\\success.jpg");//读取图片
	imshow("恭喜！！！", image);//弹出图片
	waitKey(0);
}

void failpic()
{
	Mat image = imread("C:\\Users\\As\\Desktop\\homework2\\fail.jpg");//读取图片
	imshow("再接再厉！！！", image);//弹出图片
	waitKey(0);
}
int main() {
	cout << "C语言大作业二——扫雷闯关小游戏\n\n";
	cout << "作者：王偲怡";
	cout << "\n操作指南：8上移，2下移，4左移，6右移\n          5翻开，0标记当前格，*键退出\n\n\n";
	cout << "注意：推荐使用小键盘以确保完美的游戏体验\n\n";

	int count;
	char Name_P1[20], Cho;
	printf("输入昵称:     2~15个字符\n");
	cin >> Name_P1;
	getchar();
	printf("玩家创建成功\n");
	printf("模式选择（按键）：\n1.闯关模式      2.自定义训练\n");
	Cho = getchar();
	if (Cho == '1') {
		Life = 3;
		Lv_P1 = 1;
		N = M = 10;
		num = 10;
		Init_Fd(Life, Lv_P1, N, M, num);
	}
	else {
		while (1) {
			cout << "输入长宽：\n";
			cin >> N >> M;
			cout << "输入雷数：\n";
			cin >> num;
			if (num > N* M) {
				printf("非法雷数，请重新输入\n");
			}
			else {
				break;
			}
		}
		Life = 1;
		Lv_P1 = 0;
		Init_Fd(Life, Lv_P1, N, M, num);
	}
	cout << Name_P1 << "结束游戏";
	return 0;
}
