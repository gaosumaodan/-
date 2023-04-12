#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")
#define EOF (-1)

void Start();
int Choose(int* ch,int* a);
void Drawgraph();
void Replay(char Re[][1000]);
void Setchess(int* a, int* V, int* W, int x, int y, int c[][32], char f[][1000]);
void AiChess(int* a, int* V, int* W, int c[][32], int d[][32], int e[][32], char f[][1000]);
void Stract(int* a, int X1, int X2, int Y1, int Y2, int c[][32], int d[][32]);
void JudgeVictory(int c[][32], int* a, int* V, int* W, int* A, FILE* pfile);

int c[32][32] = {};
int d[32][32] = {};
int e[32][32] = {};
char f[100][1000] = {};
int X1, X2, Y1, Y2, o=0;

int main()
{
	FILE* pfile;
	int num = 0, Ch = 1, judge = 0, v = 0, w = 0;
	int* a = &num,* ch = &Ch, *A = &judge, *V = &v, *W = &w;
	while (1) {
		Start();
		Ch = -1;
		Choose(ch, a);
		pfile = fopen("复盘.c", "a");
		if (Ch == 0) { // 人人对决
			Drawgraph();
			MOUSEMSG m;
			while (1) {
				m = GetMouseMsg();
				JudgeVictory(c, a, V, W, A, pfile);
				if (judge == 1) { // 退出人人对决
					*A = 0;
					fwrite(f[*W], sizeof(char), sizeof(f[0][0]) * (*V), pfile);
					fputc(97, pfile);
					fclose(pfile);
					*V = 0;
					*W += 1;
					break;
				}
				if (m.uMsg == WM_LBUTTONDOWN) {
					Setchess(a, V, W, m.x, m.y, c, f);
				}
			}
		}
		if (Ch == 1) { // 人机对决
			Drawgraph();
			MOUSEMSG m;
			while (1) {
				m = GetMouseMsg();
				JudgeVictory(c, a, V, W, A, pfile);
				if (judge == 1) { // 退出人机对决
					*A = 0;
					fwrite(f[*W], sizeof(char), sizeof(f[0][0]) * (*V), pfile);
					fputc(97, pfile);
					fclose(pfile);
					*V = 0;
					*W += 1;
					break;
				}
				if (*a == 0) {
					AiChess(a, V, W, c, d, e, f);
				}
				if (m.uMsg == WM_LBUTTONDOWN) {
					Setchess(a, V, W, m.x, m.y, c, f);
				}
				Stract(a, X1, X2, Y1, Y2, c, d);
			}
		}
		if (Ch == 2) { // 复盘
			Drawgraph();
			int a = 0, z = 0, i = 0;
			char R[100000]={};
			char Re[100][1000]={};
			FILE * pF;
			pF = fopen("复盘.c", "r");
			fscanf(pF, "%s", R);
			fclose(pF);
			while (R[i] != '\0') {
				Re[a][z] = R[i];
				z++, i++;
				if (R[i] == 'a') {
					z = 0;
					a++;
					i++;
				}
			}
			Replay(Re);
		}
		if (Ch == 3) {
			int ch1;
			initgraph(800, 800);
			IMAGE bk;
			loadimage(&bk, L"D:\\fb\\Visual Studio\\五子棋人机对决\\背景.png", 800, 800);
			putimage(0, 0, &bk);
			settextcolor(BLACK);
			settextstyle(40, 0, L"楷书", 0, 0, 1000, 0, 0, 0);
			setbkmode(TRANSPARENT);
			outtextxy(130, 500, L"复盘界面，帮助界面按esc键退出");
			outtextxy(215, 600, L"左右方向键切换对局");
			outtextxy(180, 700, L"人机对战ctrl+z撤回棋子");
			while (1) {
				if (_kbhit()) {
					if (ch1 = _getch()) {
						if (ch1 == 27) {
							HWND hnd = GetHWnd();
							int insok = MessageBox(hnd, TEXT("确定关闭帮助？"), TEXT(""), MB_OKCANCEL);
							if (insok == IDOK) {
								Start();
								break;
							}
							if (insok == IDCANCEL) {
								continue;
							}
						}
					}
				}
			}
		}
		if (Ch == 4) {
			Drawgraph();
			MOUSEMSG m;
			while (1) {
				m = GetMouseMsg();
				JudgeVictory(c, a, V, W, A, pfile);
				if (judge == 1) { // 退出机机对决
					*A = 0;
					fwrite(f[*W], sizeof(char), sizeof(f[0][0]) * (*V), pfile);
					fputc(97, pfile);
					fclose(pfile);
					*V = 0;
					*W += 1;
					break;
				}
				if (m.uMsg == WM_LBUTTONDOWN) {
					AiChess(a, V, W, c, d, e, f);
				}
			}
		}
	}
	return 0;
}

void Start() {
	initgraph(800, 800);
	setbkcolor(YELLOW);
	cleardevice();
	IMAGE bk, button;
	loadimage(&bk, L"D:\\fb\\Visual Studio\\五子棋人机对决\\背景.png", 800, 800);
	putimage(0, 0, &bk);
	setbkmode(TRANSPARENT);
	loadimage(&button, L"D:\\fb\\Visual Studio\\五子棋人机对决\\帮助.png", 50, 50);
	putimage(0, 0, &button);
	setlinecolor(BLACK);
	setlinestyle(0, 5);
	setfillcolor(RGB(242,229,76));
	fillrectangle(250, 400, 550, 465);
	fillrectangle(250, 505, 550, 570);
	fillrectangle(250, 610, 550, 675);
	fillrectangle(250, 715, 550, 780);
	setlinestyle(0, 2);
	fillrectangle(770, 770, 800, 800);
	settextcolor(BLACK);
	settextstyle(40, 0, L"楷书", 0, 0, 1000, 0, 0, 0);
	setbkmode(TRANSPARENT);
	outtextxy(320, 415, L"人人对决");
	outtextxy(320, 520, L"人机对决");
	outtextxy(360, 625, L"复盘");
	outtextxy(320, 730, L"结束游戏");
	settextstyle(20, 0, L"楷书", 0, 0, 1000, 0, 0, 0);
	outtextxy(770, 770, L"EVE");
}

int Choose(int* ch,int* a) {
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x > 250 && m.x < 550 && m.y>400 && m.y < 465) {
				*a = 0;
				return *ch = 0;
			}
			if (m.x > 250 && m.x < 550 && m.y>505 && m.y < 570) {
				*a = 0;
				return *ch = 1;
			}
			if (m.x > 250 && m.x < 550 && m.y>610 && m.y < 675) {
				return *ch = 2;
			}
			if (m.x > 0 && m.x < 50 && m.y > 0 && m.y < 50) {
				return *ch = 3;
			}
			if (m.x > 770 && m.x < 800 && m.y>770 && m.y < 800) {
				return *ch = 4;
			}
			if (m.x > 250 && m.x < 550 && m.y>715 && m.y < 780) {
				exit(0);
			}
		}
	}
}

void Drawgraph() {
	initgraph(800, 800);	// 初始化1000×1000的画布
	HWND hnd = GetHWnd();
	SetWindowText(hnd, L"五子棋");
	setbkcolor(YELLOW);
	cleardevice();
	setlinestyle(PS_SOLID, 4); //设置实线
	setlinecolor(BLACK); //设置线颜色
	int i, j, k;
	line(50, 50, 50, 750);
	line(50, 50, 750, 50);
	line(50, 750, 750, 750);
	line(750, 50, 750, 750);
	setlinestyle(PS_SOLID, 2);
	for (i = 2; i <= 14; i++)
	{
		line(50 * i, 50, 50 * i, 750);
		line(50, 50 * i, 750, 50 * i);
	}
	for (k = 1; k <= 3; k++) {
		for (j = 1; j <= 3; j++) {
			setfillcolor(BLACK);
			solidcircle(200 * j, 200 * k, 5);
		}
	}
}

void Replay(char Re[][1000]) {
	int i = 0, j = 0, x = 0, y = 0, a = 0, ch1 = 0, ch2 = 0;
	settextcolor(RED);
	settextstyle(40, 0, L"楷书", 0, 0, 1000, 0, 0, 0);
	setbkmode(TRANSPARENT);
	MOUSEMSG n;
	while (1) {
		n = GetMouseMsg();
		if (n.uMsg == WM_LBUTTONDOWN) {
			x = (Re[i][j] - 48) * 10 + Re[i][j + 1] - 48;
			y = (Re[i][j+2] - 48) * 10 + Re[i][j + 3] - 48;
			j += 4;
			a++;
			a = a % 2;
			if (a == 1) {
				setfillcolor(BLACK);
				fillcircle(x * 25, y * 25, 24);
			}
			else if (a == 0) {
				setfillcolor(WHITE);
				fillcircle(x * 25, y * 25, 24);
			}
		}
		if (_kbhit()) {
			if (ch1 = _getch()){
				if(ch1==27) {
					Start();
					return;
				HWND hnd = GetHWnd();
				int insok = MessageBox(hnd, TEXT("确定关闭复盘？"), TEXT("复盘结束"), MB_OKCANCEL);
				if (insok == IDOK) {
					Start();
					break;
				}
				if (insok == IDCANCEL) {
					continue;
				}
				}
				ch2 = _getch();//第一次调用getch()，返回值224
				switch (ch2)//第二次调用getch()，即为对应键
				{
				case 77:
					i++;
					j = 0;
					a = 0;
					Drawgraph();
					break;
				case 75:
					if (i > 0) {
						i--;
						j = 0;
						a = 0;
						Drawgraph();
					}
					break;
				}
			}
		}
	}
}

void AiChess(int* a, int* V, int* W, int c[][32], int d[][32], int e[][32] , char f[][1000]) {
	int m1;
	if (*a == 0) {
		*a = (*a + 1) % 2;
		setfillcolor(BLACK);
		m1 = -2;
	}
	else {
		*a = (*a + 1) % 2;
		setfillcolor(WHITE);
		m1 = 2;
	}
		srand((unsigned)time(0));
		int i, j, n=0, n1=0, n2=0, m, max = 0, random[1000] = { 0 }, r = 0;
		m = 0;
		for (i = 2; i < 32; i += 2) {
			for (j = 2; j < 32; j += 2) {
				if (d[i][j] == 0) {
					d[i][j] = c[i][j];
				}
			}
			j = 2;
		}
		for (i = 2; i < 32; i += 2) {
			for (j = 2; j < 32; j += 2) {
				if (d[i][j] != 0) {
					m = 1;
				}
			}
			j = 2;
		}
		if (m) {
			for (i = 2; i < 32; i += 2) {
				for (j = 2; j < 34; j += 2) {
					if (c[i][j] == 2) {
						if (i - 2 > 0 && j - 2 > 0 && i + 2 < 32 && j + 2 < 32) {
							e[i - 2][j - 2] += 2, e[i][j - 2] += 2, e[i + 2][j - 2] += 2, e[i - 2][j] += 2, e[i + 2][j] += 2, e[i - 2][j + 2] += 2, e[i][j + 2] += 2, e[i + 2][j + 2] += 2;
						}
					}
				}
				j = 2;
			}
			for (i = 2; i < 32; i += 2) {
				for (j = 2; j < 32; j += 2) {
					if (i - 6 > 0) {
						if (c[i - 2][j] == 2 && c[i-4][j] == 2 && c[i - 6][j] != -2) {
							e[i][j] += 4;
						}
					}
					if (i + 6 < 32) {
						if (c[i + 2][j] == 2 && c[i + 4][j] == 2 && c[i + 6][j] != -2) {
							e[i][j] += 4;
						}
					}
					if (j - 6 > 0) {
						if (c[i][j - 2] == 2 && c[i][j - 4] == 2 && c[i][j - 6] != -2) {
							e[i][j] += 4;
						}
					}
					if (j + 6 < 32) {
						if (c[i][j + 2] == 2 && c[i][j + 4] == 2 && c[i][j + 6] != -2) {
							e[i][j] += 4;
						}
					}
					if (i - 6 > 0 && j - 6 > 0) {
						if (c[i - 4][j - 4] == 2 && c[i - 2][j - 2] == 2 && c[i - 6][j - 6] != -2) {
							e[i][j] += 4;
						}
					}
					if (i + 6 < 32 && j + 6 < 32) {
						if (c[i + 4][j + 4] == 2 && c[i + 2][j + 2] == 2 && c[i + 6][j + 6] != -2) {
							e[i][j] += 4;
						}
					}
					if (i - 6 > 0 && j + 6 < 32) {
						if (c[i - 2][j + 2] == 2 && c[i - 4][j + 4] == 2 && c[i - 6][j + 6] != -2) {
							e[i][j] += 4;
						}
					}
					if (i + 6 < 32 && j - 6 > 0) {
						if (c[i + 2][j - 2] == 2 && c[i + 4][j - 4] == 2 && c[i + 6][j - 6] != -2) {
							e[i][j] += 4;
						}
					}
					if (i - 4 > 0 && i + 4 < 32 && j - 4 > 0 && j + 4 < 32) {
						if (c[i - 2][j - 2] == 2 && c[i + 2][j + 2] == 2 && c[i - 4][j - 4] != -2 && c[i + 4][j + 4] != -2) {
							e[i][j] += 4;
						}
					}
					if (i - 4 > 0 && i + 4 < 32 && j - 4 > 0 && j + 4 < 32) {
						if (c[i + 2][j - 2] == 2 && c[i - 2][j + 2] == 2 && c[i + 4][j - 4] != -2 && c[i - 4][j + 4] != -2) {
							e[i][j] += 4;
						}
					}
					if (i - 4 > 0 && i + 4 < 32) {
						if (c[i + 2][j] == 2 && c[i - 2][j] == 2 && c[i-4][j] != -2 && c[i+4][j] != -2) {
							e[i][j] += 4;
						}
					}
					if (j - 4 > 0 && j + 4 < 32) {
						if (c[i][j + 2] == 2 && c[i][j - 2] == 2 && c[i][j - 4] != -2 && c[i][j + 4] != -2) {
							e[i][j] += 4;
						}
					} // 判断活二
					if (i - 8 > 0) {
						if (c[i - 2][j] == 2 && c[i - 4][j] == 2 && c[i - 6][j] == 2 && c[i - 8][j] != -2) {
							e[i][j] += 100;
						}
					}
					if (i + 8 < 32) {
						if (c[i + 2][j] == 2 && c[i + 4][j] == 2 && c[i + 6][j] == 2 && c[i + 8][j] != -2) {
							e[i][j] += 100;
						}
					}
					if (j - 8 > 0) {
						if (c[i][j - 2] == 2 && c[i][j - 4] == 2 && c[i][j - 6] == 2 && c[i][j - 8] != -2) {
							e[i][j] += 100;
						}
					}
					if (j + 8 < 32) {
						if (c[i][j + 2] == 2 && c[i][j + 4] == 2 && c[i][j + 6] == 2 && c[i][j + 8] != -2) {
							e[i][j] += 100;
						}
					}
					if (i + 8 < 32 && j + 8 < 32) {
						if (c[i + 2][j + 2] == 2 && c[i + 4][j + 4] == 2 && c[i + 6][j + 6] == 2 && c[i + 8][j + 8] != -2) {
							e[i][j] += 100;
						}
					}
					if (i + 8 < 32 && j - 8 > 0) {
						if (c[i + 2][j - 2] == 2 && c[i + 4][j - 4] == 2 && c[i + 6][j - 6] == 2 && c[i + 8][j - 8] != -2) {
							e[i][j] += 100;
						}
					}
					if (i - 8 > 0 && j + 8 < 32) {
						if (c[i - 2][j + 2] == 2 && c[i - 4][j + 4] == 2 && c[i - 6][j + 6] == 2 && c[i - 8][j + 8] != -2) {
							e[i][j] += 100;
						}
					}
					if (i - 8 > 0 && j - 8 > 0) {
						if (c[i - 2][j - 2] == 2 && c[i - 4][j - 4] == 2 && c[i - 6][j - 6] == 2 && c[i - 8][j - 8] != -2) {
							e[i][j] += 100;
						}
					}
					if (i - 6 > 0 && i + 4 < 32) {
						if (c[i - 4][j] == 2 && c[i - 2][j] == 2 && c[i + 2][j] == 2 && c[i - 6][j] != -2 && c[i + 4][j] != -2) {
							e[i][j] += 100;
						}
					}
					if (i - 4 > 0 && i + 6 < 32) {
						if (c[i + 4][j] == 2 && c[i + 2][j] == 2 && c[i - 2][j] == 2 && c[i + 6][j] != -2 && c[i - 4][j] != -2) {
							e[i][j] += 100;
						}
					}
					if (j - 6 > 0 && j + 4 < 32) {
						if (c[i][j - 4] == 2 && c[i][j - 2] == 2 && c[i][j + 2] == 2 && c[i][j - 6] != -2 && c[i][j + 4] != -2) {
							e[i][j] += 100;
						}
					}
					if (j - 4 > 0 && j + 6 < 32) {
						if (c[i][j + 4] == 2 && c[i][j + 2] == 2 && c[i][j - 2] == 2 && c[i][j + 6] != -2 && c[i][j - 4] != -2) {
							e[i][j] += 100;
						}
					}
					if (i - 6 > 0 && i + 4 < 32 && j - 6 > 0 && j + 4 < 32) {
						if (c[i - 4][j - 4] == 2 && c[i - 2][j - 2] == 2 && c[i + 2][j + 2] == 2 && c[i - 6][j - 6] != -2 && c[i + 4][j + 4] != -2) {
							e[i][j] += 100;
						}
					}
					if (i - 4 > 0 && i + 6 < 32 && j - 4 > 0 && j + 6 < 32) {
						if (c[i + 4][j + 4] == 2 && c[i + 2][j + 2] == 2 && c[i - 2][j - 2] == 2 && c[i + 6][j + 6] != -2 && c[i - 4][j - 4] != -2) {
							e[i][j] += 100;
						}
					}
					if (i - 6 > 0 && i + 4 < 32 && j - 4 > 0 && j + 6 < 32) {
						if (c[i - 4][j + 4] == 2 && c[i - 2][j + 2] == 2 && c[i + 2][j - 2] == 2 && c[i - 6][j + 6] != -2 && c[i + 4][j - 4] != -2) {
							e[i][j] += 100;
						}
					}
					if (i - 4 > 0 && i + 6 < 32 && j - 6 > 0 && j + 4 < 32) {
						if (c[i + 4][j - 4] == 2 && c[i + 2][j - 2] == 2 && c[i - 2][j + 2] == 2 && c[i + 6][j - 6] != -2 && c[i - 4][j + 4] != -2) {
							e[i][j] += 100;
						}
					} // 判断活三
					if (i - 8 > 0) {
						if (c[i - 8][j] == 2 && c[i - 6][j] == 2 && c[i - 4][j] == 2 && c[i - 2][j] == 2) {
							e[i][j] += 2000;
						}
					}
					if (i + 8 < 32) {
						if (c[i + 8][j] == 2 && c[i + 6][j] == 2 && c[i + 4][j] == 2 && c[i + 2][j] == 2) {
							e[i][j] += 2000;
						}
					}
					if (j - 8 > 0) {
						if (c[i][j - 8] == 2 && c[i][j - 6] == 2 && c[i][j - 4] == 2 && c[i][j - 2] == 2) {
							e[i][j] += 2000;
						}
					}
					if (j + 8 < 32) {
						if (c[i][j + 8] == 2 && c[i][j + 6] == 2 && c[i][j + 4] == 2 && c[i][j + 2] == 2) {
							e[i][j] += 2000;
						}
					}
					if (i - 8 > 0 && j - 8 > 0) {
						if (c[i - 8][j - 8] == 2 && c[i - 6][j - 6] == 2 && c[i - 4][j - 4] == 2 && c[i - 2][j - 2] == 2) {
							e[i][j] += 2000;
						}
					}
					if (i + 8 < 32 && j + 8 < 32) {
						if (c[i + 8][j + 8] == 2 && c[i + 6][j + 6] == 2 && c[i + 4][j + 4] == 2 && c[i + 2][j + 2] == 2) {
							e[i][j] += 2000;
						}
					}
					if (i - 8 > 0 && j + 8 < 32) {
						if (c[i - 8][j + 8] == 2 && c[i - 6][j + 6] == 2 && c[i - 4][j + 4] == 2 && c[i - 2][j + 2] == 2) {
							e[i][j] += 2000;
						}
					}
					if (i + 8 < 32 && j - 8 > 0) {
						if (c[i + 8][j - 8] == 2 && c[i + 6][j - 6] == 2 && c[i + 4][j - 4] == 2 && c[i + 2][j - 2] == 2) {
							e[i][j] += 2000;
						}
					}
					if (i - 6 > 0 && j - 6 > 0 && i + 2 < 32 && j + 2 < 32) {
						if (c[i - 6][j - 6] == 2 && c[i - 4][j - 4] == 2 && c[i - 2][j - 2] == 2 && c[i + 2][j + 2] == 2) {
							e[i][j] += 2000;
						}
					}
					if (i + 6 < 32 && j + 6 < 32 && i - 2 > 0 && j - 2 > 0) {
						if (c[i + 6][j + 6] == 2 && c[i + 4][j + 4] == 2 && c[i + 2][j + 2] == 2 && c[i - 2][j - 2] == 2) {
							e[i][j] += 2000;
						}
					}
					if (i - 6 > 0 && j + 6 < 32 && i + 2 < 32 && j - 2 > 0) {
						if (c[i - 6][j + 6] == 2 && c[i - 4][j + 4] == 2 && c[i - 2][j + 2] == 2 && c[i + 2][j - 2] == 2) {
							e[i][j] += 2000;
						}
					}
					if (i + 6 < 32 && j - 6 > 0 && i - 2 > 0 && j + 2 < 32) {
						if (c[i + 6][j - 6] == 2 && c[i + 4][j - 4] == 2 && c[i + 2][j - 2] == 2 && c[i - 2][j + 2] == 2) {
							e[i][j] += 2000;
						}
					}
					if (i + 4 < 32 && i - 4 > 0) {
						if (c[i + 4][j] == 2 && c[i + 2][j] == 2 && c[i - 2][j] == 2 && c[i - 4][j] == 2) {
							e[i][j] += 2000;
						}
					}
					if (j + 4 < 32 && j - 4 > 0) {
						if (c[i][j + 4] == 2 && c[i][j + 2] == 2 && c[i][j - 2] == 2 && c[i][j - 4] == 2) {
							e[i][j] += 2000;
						}
					}
					if (i + 4 < 32 && i - 4 > 0 && j + 4 < 32 && j - 4 > 0) {
						if (c[i + 4][j + 4] == 2 && c[i + 2][j + 2] == 2 && c[i - 2][j - 2] == 2 && c[i - 4][j - 4] == 2) {
							e[i][j] += 2000;
						}
					}
					if (i + 4 < 32 && i - 4 > 0 && j + 4 < 32 && j - 4 > 0) {
						if (c[i - 4][j + 4] == 2 && c[i - 2][j + 2] == 2 && c[i + 2][j - 2] == 2 && c[i + 4][j - 4] == 2) {
							e[i][j] += 2000;
						}
					} // 判断四子相连
				}
				j = 2;
			} // 防守判分
			for (i = 2; i < 32; i += 2) {
				for (j = 2; j < 32; j += 2) {
					if (c[i][j] == -2) {
						if (i - 2 > 0 && j - 2 > 0 && i + 2 < 32 && j + 2 < 32) {
							e[i - 2][j - 2] += 2, e[i][j - 2] += 2, e[i + 2][j - 2] += 2, e[i - 2][j] += 2, e[i + 2][j] += 2, e[i - 2][j + 2] += 2, e[i][j + 2] += 2, e[i + 2][j + 2] += 2;
						}
					}
					if (d[i][j] == 0) {
						if (i - 4 > 0 && i + 2 < 32) {
							if (c[i - 2][j] == -2 && c[i - 4][j] != 2 && c[i + 2][j] != 2) {
								e[i][j] += 2;
							}
						}
						if (i - 2 > 0 && i + 4 < 32) {
							if (c[i + 2][j] == -2 && c[i + 4][j] != 2 && c[i - 2][j] != 2) {
								e[i][j] += 2;
							}
						}
						if (j - 4 > 0 && j + 2 < 32) {
							if (c[i][j - 2] == -2 && c[i][j - 4] != 2 && c[i][j + 2] != 2) {
								e[i][j] += 2;
							}
						}
						if (j - 2 > 0 && j + 4 < 32) {
							if (c[i][j + 2] == -2 && c[i][j + 4] != 2 && c[i][j - 2] != 2) {
								e[i][j] += 2;
							}
						}
						if (i - 4 > 0 && i + 2 < 32 && j - 4 > 0 && j + 2 < 32) {
							if (c[i - 2][j - 2] == -2 && c[i - 4][j - 4] != 2 && c[i + 2][j + 2] != 2) {
								e[i][j] += 2;
							}
						}
						if (i - 2 > 0 && i + 4 < 32 && j - 2 > 0 && j + 4 < 32) {
							if (c[i + 2][j + 2] == -2 && c[i + 4][j + 4] != 2 && c[i - 2][j - 2] != 2) {
								e[i][j] += 2;
							}
						}
						if (i - 4 > 0 && i + 2 < 32 && j - 2 > 0 && j + 4 < 32) {
							if (c[i - 2][j + 2] == -2 && c[i - 4][j + 4] != 2 && c[i + 2][j - 2] != 2) {
								e[i][j] += 2;
							}
						} // 冲活二
						if (i - 2 > 0 && i + 4 < 32 && j - 4 > 0 && j + 2 < 32) {
							if (c[i + 2][j - 2] == -2 && c[i + 4][j - 4] != 2 && c[i - 2][j + 2] != 2) {
								e[i][j] += 2;
							}
						}
						if (i - 6 > 0 && i + 2 < 32) {
							if (c[i - 4][j] == -2 && c[i - 2][j] == -2 && c[i - 6][j] != 2 && c[i + 2][j] != 2) {
								e[i][j] += 4;
							}
						}
						if (i - 2 > 0 && i + 6 < 32) {
							if (c[i + 4][j] == -2 && c[i + 2][j] == -2 && c[i + 6][j] != 2 && c[i - 2][j] != 2) {
								e[i][j] += 4;
							}
						}
						if (j - 6 > 0 && j + 2 < 32) {
							if (c[i][j - 4] == -2 && c[i][j - 2] == -2 && c[i][j - 6] != 2 && c[i][j + 2] != 2) {
								e[i][j] += 4;
							}
						}
						if (j - 2 > 0 && j + 6 < 32) {
							if (c[i][j + 4] == -2 && c[i][j + 2] == -2 && c[i][j + 6] != 2 && c[i][j - 2] != 2) {
								e[i][j] += 4;
							}
						}
						if (i - 6 > 0 && j - 6 > 0 && i + 2 < 32 && j + 2 < 32) {
							if (c[i - 4][j - 4] == -2 && c[i - 2][j - 2] == -2 && c[i - 6][j - 6] != 2 && c[i + 2][j + 2] != 2) {
								e[i][j] += 4;
							}
						}
						if (i - 6 > 0 && j - 2 > 0 && i + 2 < 32 && j + 6 < 32) {
							if (c[i - 4][j + 4] == -2 && c[i - 2][j + 2] == -2 && c[i - 6][j + 6] != 2 && c[i + 2][j - 2] != 2) {
								e[i][j] += 4;
							}
						}
						if (i - 2 > 0 && j - 6 > 0 && i + 6 < 32 && j + 2 < 32) {
							if (c[i + 4][j - 4] == -2 && c[i + 2][j - 2] == -2 && c[i + 6][j - 6] != 2 && c[i - 2][j + 2] != 2) {
								e[i][j] += 4;
							}
						}
						if (i - 2 > 0 && j - 2 > 0 && i + 6 < 32 && j + 6 < 32) {
							if (c[i + 4][j + 4] == -2 && c[i + 2][j + 2] == -2 && c[i + 6][j + 6] != 2 && c[i - 2][j - 2] != 2) {
								e[i][j] += 4;
							}
						}
						if (i - 4 > 0 && j - 4 > 0 && i + 4 < 32 && j + 4 < 32) {
							if (c[i - 2][j - 2] == -2 && c[i + 2][j + 2] == -2 && c[i - 4][j - 4] != 2 && c[i + 4][j + 4] != 2) {
								e[i][j] += 4;
							}
						}
						if (i - 4 > 0 && j + 4 > 0 && i + 4 < 32 && j - 4 < 32) {
							if (c[i - 2][j + 2] == -2 && c[i + 2][j - 2] == -2 && c[i - 4][j + 4] != 2 && c[i + 4][j - 4] != 2) {
								e[i][j] += 4;
							}
						}
						if (i - 4 > 0 && i + 4 < 32) {
							if (c[i - 2][j] == -2 && c[i + 2][j] == -2 && c[i + 4][j] != 2 && c[i - 4][j] != 2) {
								e[i][j] += 4;
							}
						}
						if (j - 4 > 0 && j + 4 < 32) {
							if (c[i][j - 2] == -2 && c[i][j + 2] == -2 && c[i][j + 4] != 2 && c[i][j - 4] != 2) {
								e[i][j] += 4;
							}
						} // 冲活三
						if (i - 8 > 0 && i + 2 <32) {
							if (c[i - 6][j] == -2 && c[i - 4][j] == -2 && c[i - 2][j] == -2 && (c[i - 8][j] != 2 || c[i + 2][j] != 2)) {
								e[i][j] += 100;
							}
						}
						if (i - 2 > 0 && i + 8 < 32) {
							if (c[i + 6][j] == -2 && c[i + 4][j] == -2 && c[i + 2][j] == -2 && (c[i + 8][j] != 2 || c[i - 2][j] != 2)) {
								e[i][j] += 100;
							}
						}
						if (j - 2 > 0 && j + 8 < 32) {
							if (c[i][j + 6] == -2 && c[i][j + 4] == -2 && c[i][j + 2] == -2 && (c[i][j + 8] != 2 || c[i][j - 2] != 2)) {
								e[i][j] += 100;
							}
						}
						if (j - 8 > 0 && j + 2 < 32) {
							if (c[i][j - 6] == -2 && c[i][j - 4] == -2 && c[i][j - 2] == -2 && (c[i][j - 8] != 2 || c[i][j + 2] != 2)) {
								e[i][j] += 100;
							}
						}
						if (i - 8 > 0 && j - 8 > 0 && i + 2 < 32 && j + 2 < 32) {
							if (c[i - 6][j - 6] == -2 && c[i - 4][j - 4] == -2 && c[i - 2][j - 2] == -2 && (c[i - 8][j - 8] != 2 || c[i + 2][j + 2] != 2)) {
								e[i][j] += 100;
							}
						}
						if (i - 8 > 0 && j - 2 > 0 && i + 2 < 32 && j + 8 < 32) {
							if (c[i - 6][j + 6] == -2 && c[i - 4][j + 4] == -2 && c[i - 2][j + 2] == -2 && (c[i - 8][j + 8] != 2 || c[i + 2][j - 2] != 2)) {
								e[i][j] += 100;
							}
						}
						if (i - 2 > 0 && j - 2 > 0 && i + 8 < 32 && j + 8 < 32) {
							if (c[i + 6][j + 6] == -2 && c[i + 4][j + 4] == -2 && c[i + 2][j + 2] == -2 && (c[i + 8][j + 8] != 2 || c[i - 2][j - 2] != 2)) {
								e[i][j] += 100;
							}
						}
						if (i - 2 > 0 && j - 8 > 0 && i + 8 < 32 && j + 2 < 32) {
							if (c[i + 6][j - 6] == -2 && c[i + 4][j - 4] == -2 && c[i + 2][j - 2] == -2 && (c[i + 8][j - 8] != 2 || c[i - 2][j + 2] != 2)) {
								e[i][j] += 100;
							}
						}
						if (i - 6 > 0 && i + 4 < 32) {
							if (c[i - 4][j] == -2 && c[i - 2][j] == -2 && c[i + 2][j] == -2 && (c[i - 6][j] != 2 || c[i + 4][j] != 2)) {
								e[i][j] += 100;
							}
						}
						if (i - 4 > 0 && i + 6 < 32) {
							if (c[i + 4][j] == -2 && c[i + 2][j] == -2 && c[i - 2][j] == -2 && (c[i + 6][j] != 2 || c[i - 4][j] != 2)) {
								e[i][j] += 100;
							}
						}
						if (j - 6 > 0 && j + 4 < 32) {
							if (c[i][j - 4] == -2 && c[i][j - 2] == -2 && c[i][j + 2] == -2 && (c[i][j - 6] != 2 || c[i][j + 4] != 2)) {
								e[i][j] += 100;
							}
						}
						if (j - 4 > 0 && j + 6 < 32) {
							if (c[i][j + 4] == -2 && c[i][j + 2] == -2 && c[i][j - 2] == -2 && (c[i][j + 6] != 2 || c[i][j - 4] != 2)) {
								e[i][j] += 100;
							}
						}
						if (i - 6 > 0 && j - 6 > 0 && i + 4 < 32 && j + 4 < 32) {
							if (c[i - 4][j - 4] == -2 && c[i - 2][j - 2] == -2 && c[i + 2][j + 2] == -2 && (c[i - 6][j - 6] != 2 || c[i + 2][j + 2] != 2)) {
								e[i][j] += 100;
							}
						}
						if (i - 4 > 0 && j - 4 > 0 && i + 6 < 32 && j + 6 < 32) {
							if (c[i + 4][j + 4] == -2 && c[i + 2][j + 2] == -2 && c[i - 2][j - 2] == -2 && (c[i + 6][j + 6] != 2 || c[i - 2][j - 2] != 2)) {
								e[i][j] += 100;
							}
						}
						if (i - 4 > 0 && j - 6 > 0 && i + 6 < 32 && j + 4 < 32) {
							if (c[i + 4][j - 4] == -2 && c[i + 2][j - 2] == -2 && c[i - 2][j + 2] == -2 && (c[i + 6][j - 6] != 2 || c[i - 2][j + 2] != 2)) {
								e[i][j] += 100;
							}
						}
						if (i - 6 > 0 && j - 4 > 0 && i + 4 < 32 && j + 6 < 32) {
							if (c[i - 4][j + 4] == -2 && c[i - 2][j + 2] == -2 && c[i + 2][j - 2] == -2 && (c[i - 6][j - 6] != 2 || c[i + 2][j - 2] != 2)) {
								e[i][j] += 100;
							}
						} // 冲四
						if (i - 8 > 0) {
							if (c[i - 8][j] == -2 && c[i - 6][j] == -2 && c[i - 4][j] == -2 && c[i - 2][j] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i + 8 < 32) {
							if (c[i + 8][j] == -2 && c[i + 6][j] == -2 && c[i + 4][j] == -2 && c[i + 2][j] == -2) {
								e[i][j] += 8000;
							}
						}
						if (j - 8 > 0) {
							if (c[i][j - 8] == -2 && c[i][j - 6] == -2 && c[i][j - 4] == -2 && c[i][j - 2] == -2) {
								e[i][j] += 8000;
							}
						}
						if (j + 8 < 32) {
							if (c[i][j + 8] == -2 && c[i][j + 6] == -2 && c[i][j + 4] == -2 && c[i][j + 2] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i - 8 > 0 && j - 8 > 0) {
							if (c[i - 8][j - 8] == -2 && c[i - 6][j - 6] == -2 && c[i - 4][j - 4] == -2 && c[i - 2][j - 2] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i + 8 < 32 && j + 8 < 32) {
							if (c[i + 8][j + 8] == -2 && c[i + 6][j + 6] == -2 && c[i + 4][j + 4] == -2 && c[i + 2][j + 2] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i - 8 > 0 && j + 8 < 32) {
							if (c[i - 8][j + 8] == -2 && c[i - 6][j + 6] == -2 && c[i - 4][j + 4] == -2 && c[i - 2][j + 2] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i + 8 < 32 && j - 8 > 0) {
							if (c[i + 8][j - 8] == -2 && c[i + 6][j - 6] == -2 && c[i + 4][j - 4] == -2 && c[i + 2][j - 2] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i - 6 > 0 && i + 2 < 32) {
							if (c[i - 6][j] == -2 && c[i - 4][j] == -2 && c[i - 2][j] == -2 && c[i + 2][j] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i - 2 > 0 && i + 6 < 32) {
							if (c[i + 6][j] == -2 && c[i + 4][j] == -2 && c[i + 2][j] == -2 && c[i - 2][j] == -2) {
								e[i][j] += 8000;
							}
						}
						if (j - 6 > 0 && j + 2 < 32) {
							if (c[i][j - 6] == -2 && c[i][j - 4] == -2 && c[i][j - 2] == -2 && c[i][j + 2] == -2) {
								e[i][j] += 8000;
							}
						}
						if (j - 2 > 0 && j + 6 < 32) {
							if (c[i][j + 6] == -2 && c[i][j + 4] == -2 && c[i][j + 2] == -2 && c[i][j - 2] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i - 4 > 0 && i + 4 < 32) {
							if (c[i - 4][j] == -2 && c[i - 2][j] == -2 && c[i + 2][j] == -2 && c[i + 4][j] == -2) {
								e[i][j] += 8000;
							}
						}
						if (j - 4 > 0 && j + 4 < 32) {
							if (c[i][j - 4] == -2 && c[i][j - 2] == -2 && c[i][j + 2] == -2 && c[i][j + 4] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i - 6 > 0 && j - 6 > 0 && i + 2 < 32 && j + 2 < 32) {
							if (c[i - 6][j - 6] == -2 && c[i - 4][j - 4] == -2 && c[i - 2][j - 2] == -2 && c[i + 2][j + 2] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i - 2 > 0 && j - 2 > 0 && i + 6 < 32 && j + 6 < 32) {
							if (c[i + 6][j + 6] == -2 && c[i + 4][j + 4] == -2 && c[i + 2][j + 2] == -2 && c[i - 2][j - 2] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i - 6 > 0 && j - 2 > 0 && i + 2 < 32 && j + 6 < 32) {
							if (c[i - 6][j + 6] == -2 && c[i - 4][j + 4] == -2 && c[i - 2][j + 2] == -2 && c[i + 2][j - 2] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i - 2 > 0 && j - 6 > 0 && i + 6 < 32 && j + 2 < 32) {
							if (c[i + 6][j - 6] == -2 && c[i + 4][j - 4] == -2 && c[i + 2][j - 2] == -2 && c[i - 2][j + 2] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i - 4 > 0 && j - 4 > 0 && i + 4 < 32 && j + 4 < 32) {
							if (c[i - 4][j - 4] == -2 && c[i - 2][j - 2] == -2 && c[i + 2][j + 2] == -2 && c[i + 4][j + 4] == -2) {
								e[i][j] += 8000;
							}
						}
						if (i - 4 > 0 && j - 4 > 0 && i + 4 < 32 && j + 4 < 32) {
							if (c[i - 4][j + 4] == -2 && c[i - 2][j + 2] == -2 && c[i + 2][j - 2] == -2 && c[i + 4][j - 4] == -2) {
								e[i][j] += 8000;
							}
						}
					}
				}
				j = 2;
			}
			e[8][30] += 5, e[18][30] += 5, e[28][30] += 5;
			e[2][28] += 5, e[12][28] += 5, e[22][28] += 5;
			e[6][26] += 5, e[16][26] += 5, e[26][26] += 5;
			e[10][24] += 5, e[20][24] += 5, e[30][24] += 5;
			e[4][22] += 5, e[14][22] += 10, e[24][22] += 5;
			e[8][20] += 5, e[18][20] += 10, e[28][20] += 5;
			e[2][18] += 5, e[12][18] += 10, e[22][18] += 10;
			e[6][16] += 5, e[16][16] += 10, e[26][16] += 5;
			e[10][14] += 10, e[20][14] += 10, e[30][14] += 5;
			e[4][12] += 5, e[14][12] += 10, e[24][12] += 5;
			e[8][10] += 5, e[18][10] += 10, e[28][10] += 5;
			e[2][8] += 5, e[12][8] += 5, e[22][8] += 5;
			e[6][6] += 5, e[16][6] += 5, e[26][6] += 5;
			e[10][4] += 5, e[20][4] += 5, e[30][4] += 5;
			e[4][2] += 5, e[14][2] += 5, e[24][2] += 5;
			for (i = 2; i < 32; i += 2) {
				for (j = 2; j < 32; j += 2) {
					if (c[i][j] == 2 || c[i][j] == -2) {
						e[i][j] = 0;
					}
				}
				j = 2;
			}
			for (i = 2; i < 32; i += 2) {
				for (j = 2; j < 32; j += 2) {
					if (e[i][j] > max) {
						max = e[i][j];
					}
				}
				j = 2;
			}
			for (i = 2; i < 32; i += 2) {
				for (j = 2; j < 32; j += 2) {
					if (e[i][j] == max) {
						r++;
						random[r] = i * 100 + j;
					}
				}
				j = 2;
			}
			n = random[rand() % r + 1];
			i=n / 100, j=n % 100;
			fillcircle(i * 25, j * 25, 24);
			c[n / 100][n % 100] = m1;
			d[n / 100][n % 100] = -2;
			X1 = i, Y1 = j;
			f[*W][*V] = X1/10 + 48, f[*W][*V + 1] = X1%10 + 48, f[*W][*V + 2] = Y1/10 + 48, f[*W][*V + 3] = Y1%10 + 48;
			*V += 4;
		}
		else {
			fillcircle(400, 400, 24);
			c[16][16] = m1;
			d[16][16] = -2;
			f[*W][*V] = 1 + 48, f[*W][*V+1] = 6 + 48, f[*W][*V+2] = 1 + 48, f[*W][*V+3] = 6 + 48;
			*V += 4;
		}
		for (i = 2; i < 32; i += 2) {
			for (j = 2; j < 32; j += 2) {
				e[i][j] = 0;
			}
			j = 2;
		}
	}

void Setchess(int* a, int* V, int* W, int x, int y, int c[][32], char f[][1000]) {
	int m;
	if (*a == 0) {
		setfillcolor(BLACK);
		m = -2;
	}
	else {
		setfillcolor(WHITE);
		m = 2;
	}
	if (x >= 25 && x < 775 && y >= 25 && y < 775) {
		x = x / 25;
		if (x % 2 == 1) {
			x += 1;
		}
		y = y / 25;
		if (y % 2 == 1) {
			y += 1;
		}
		if (c[x][y] == 0) {
			c[x][y] = m;
			fillcircle(x * 25, y * 25, 24);
			*a = (*a + 1) % 2;
			X2 = x, Y2 = y;
			f[*W][*V] = X2 / 10 + 48, f[*W][*V + 1] = X2 % 10 + 48, f[*W][*V + 2] = Y2 / 10 + 48, f[*W][*V + 3] = Y2 % 10 + 48;
			*V += 4;
		}
	}
}

void Stract(int* a, int X1, int X2, int Y1, int Y2, int c[][32], int d[][32]) {
	if (_kbhit()) {
		int key = _getch();
		switch (key) {
		case 26:
			o = 1;
			break;
		}
		if (o) {
			setfillcolor(YELLOW);
			setlinecolor(YELLOW);
			fillcircle(X1 * 25, Y1 * 25, 24);
			fillcircle(X2 * 25, Y2 * 25, 24);
			setlinecolor(BLACK);
			line(X1 * 25, Y1 * 25 - 25, X1 * 25, Y1 * 25 + 25);
			line(X1 * 25 - 25, Y1 * 25, X1 * 25 + 25, Y1 * 25);
			line(X2 * 25, Y2 * 25 - 25, X2 * 25, Y2 * 25 + 25);
			line(X2 * 25 - 25, Y2 * 25, X2 * 25 + 25, Y2 * 25);
			c[X1][Y1] = 0;
			d[X2][Y2] = 0;
			c[X2][Y2] = 0;
			d[X1][Y1] = 0;
			o = 0;
		}
	}
}

void JudgeVictory(int c[][32], int* a, int* V, int* W, int* A, FILE * pfile) {
	HWND hnd = GetHWnd();
	int m, n, b = 0, sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
	for (m = 2; m < 24; m = m + 2) {
		for (n = 2; n < 34; n = n + 2) {
			sum1 = c[m][n] + c[m + 2][n] + c[m + 4][n] + c[m + 6][n] + c[m + 8][n];
			if (fabs(sum1) > fabs(b)) {
				b = sum1;
			}
		}
		n = 2;
	}
	for (m = 2; m < 34; m = m + 2) {
		for (n = 2; n < 26; n = n + 2) {
			sum2 = c[m][n] + c[m][n + 2] + c[m][n + 4] + c[m][n + 6] + c[m][n + 8];
			if (fabs(sum2) > fabs(b)) {
				b = sum2;
			}
		}
		n = 2;
	}
	for (m = 2; m < 26; m = m + 2) {
		for (n = 2; n < 26; n = n + 2) {
			sum3 = c[m][n] + c[m + 2][n + 2] + c[m + 4][n + 4] + c[m + 6][n + 6] + c[m + 8][n + 8];
			if (fabs(sum3) > fabs(b)) {
				b = sum3;
			}
		}
		n = 2;
	}
	for (m = 10; m < 34; m = m + 2) {
		for (n = 2; n < 26; n = n + 2) {
			sum4 = c[m][n] + c[m - 2][n + 2] + c[m - 4][n + 4] + c[m - 6][n + 6] + c[m - 8][n + 8];
			if (fabs(sum4) > fabs(b)) {
				b = sum4;
			}
		}
	}
	if (b == 10) {
		int insok=MessageBox(hnd, TEXT("White win\n再来一局"), TEXT("游戏结束"), MB_OKCANCEL);
		if (insok == IDCANCEL) {
			Start();
			for (m = 2; m < 32; m += 2) {
				for (n = 2; n < 32; n += 2) {
					c[m][n] = 0;
					d[m][n] = 0;
				}
				n = 2, * a = 0;
			}
			*A = 1;
		}
		if (insok == IDOK) {
			Drawgraph();
			for (m = 2; m < 32; m += 2) {
				for (n = 2; n < 32; n += 2) {
					c[m][n] = 0;
					d[m][n] = 0;
				}
				n = 2, * a = 0;
			}
			pfile = fopen("复盘.c", "a");
			fwrite(f[*W], sizeof(char), sizeof(f[0][0]) * (*V), pfile);
			fputc(97, pfile);
			fclose(pfile);
			*V = 0, * W += 1;
		}
	}
	else if (b == -10) {
		int insok=MessageBox(hnd, TEXT("Black win\n再来一局"), TEXT("游戏结束"), MB_OKCANCEL);
		if (insok == IDCANCEL) {
			for (m = 2; m < 32; m += 2) {
				for (n = 2; n < 32; n += 2) {
					c[m][n] = 0;
					d[m][n] = 0;
				}
				n = 2 ,* a = 0;
			}
			*A = 1;
		}
		if (insok == IDOK) {
			Drawgraph();
			for (m = 2; m < 32; m += 2) {
				for (n = 2; n < 32; n += 2) {
					c[m][n] = 0;
					d[m][n] = 0;
				}
				n = 2, * a = 0;
			}
			pfile = fopen("复盘.c", "a");
			fwrite(f[*W], sizeof(char), sizeof(f[0][0]) * (*V), pfile);
			fputc(97, pfile);
			fclose(pfile);
			*V = 0, * W += 1;
		}
	}
}