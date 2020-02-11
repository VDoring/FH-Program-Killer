#include <stdio.h>
#include <Windows.h>
#include <conio.h>

/* 키보드 키 */
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4
#define KEY_ENTER 5

gotoxy(int x, int y) { //글자위치 조정 함수
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

textcolor(int color_num) { //글자색 설정 함수
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_num);
}


//메인메뉴
int Menu() {
	int x = 47, y = 4; //gotoxy용 변수
	int keynum; //키보드 키값 저장
	int menu = 1; //몇번 메뉴를 선택했는지 알기위한 변수

	system("mode con cols=128 lines=24");
	system("title Program Shutdown v0.1");

	gotoxy(50, 1); textcolor(11); printf("Process Killer");
	gotoxy(x - 2, y); textcolor(15); printf("> 1.Search / Run");
	gotoxy(x, y + 1); textcolor(15); printf("2.Search");

	while (1) {
		keynum = keyControl();

		switch (keynum) {
		case KEY_UP:
			if (y > 4) {
				gotoxy(x - 2, y); printf(" ");
				gotoxy(x - 2, --y); printf(">");
				menu--;
			}
			break;
		case KEY_DOWN:
			if (y < 5) {
				gotoxy(x - 2, y); printf(" ");
				gotoxy(x - 2, ++y); printf(">");
				menu++;
			}
			break;
		case KEY_ENTER:
			switch (menu) {
			case 1:
				return 1;
				break;
			case 2:
				return 2;
				break;
			default:
				return -1; //에러
			}
		}
	}
}

//메뉴에서 입력한 키보드키 반환
int keyControl() {
	char keytemp;

	keytemp = getch();
	if (keytemp == 13)
		return KEY_ENTER;
	switch (keytemp) {
	case 72:
		return KEY_UP;
	case 80:
		return KEY_DOWN;
	case 75:
		return KEY_LEFT;
	case 77:
		return KEY_RIGHT;
	default:
		return -1; //에러 or 다른 키보드값 입력
	}
}

void Menu_1() {
	gotoxy(10, 10); printf("1111111111");
	return 0;
}

void Menu_2() {
	gotoxy(10, 10); printf("2222222222");
	return 0;
}

int main() {
	int menu_select_num = 0;

	menu_select_num = Menu();
	switch (menu_select_num) {
	case 1:
		Menu_1();
		break;
	case 2:
		Menu_2();
		break;
	default:
		return -1; //에러
	}
}