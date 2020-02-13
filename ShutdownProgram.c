#include <stdio.h>
#include <Windows.h>
#include <conio.h>

/* 키보드 키 */
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4
#define KEY_ENTER 5

int Menu(); //메인메뉴
int keyControl(); //메뉴에서 입력한 키보드키 반환
void Menu_1(); //1.Run
void Menu_2(); //2.Search

//글자위치 조정 함수
gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//글자색 설정 함수
textcolor(int color_num) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_num);
}

//메인메뉴
int Menu() {
	int x = 10, y = 4; //gotoxy용 변수
	int keynum; //키보드 키값 저장
	int menu = 1; //몇번 메뉴를 선택했는지 알기위한 변수

	system("mode con cols=34 lines=10");
	system("title Process Killer v1.0");

	gotoxy(10, 1); textcolor(11); printf("Process Killer");
	gotoxy(x - 2, y); textcolor(15); printf("> 1.Run");
	gotoxy(x, y + 1); textcolor(15); printf("2.Search");

	while (1) {
		keynum = keyControl();

		switch (keynum) { //키 누름에 따라 표시되는 화살표가 바뀜
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

	keytemp = _getch();
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

// 1.Run
void Menu_1() {
	const char taskkill_command[16] = { "taskkill /F /IM" };
	char process_name[100] = { 0, }; //유저가 입력
	char final_taskkill_command[120] = { 0, }; //최종 명령어

	system("mode con cols=50 lines=10");
	
	gotoxy(2, 2); printf("Please enter the name of the program to exit");
	gotoxy(7, 3); printf("(Please put an '.exe' on the end)");
	gotoxy(3, 5); printf("->");
	gotoxy(6, 5); scanf_s("%s", process_name, sizeof(process_name));

	sprintf_s(final_taskkill_command, sizeof(final_taskkill_command), "%s %s", taskkill_command, process_name);
	system(final_taskkill_command);

	system("cls");
	gotoxy(20, 2); textcolor(10); printf("Executed!"); Sleep(800);

	return;
}

// 2.Search
void Menu_2() {
	const char tasklist_imagename_command_start[28] = { "tasklist /FI \"IMAGENAME eq "};
	const char tasklist_imagename_command_end[2] = { "\"" };
	char process_name[100] = { 0, }; //유저가 입력
	char final_tasklist_command[140] = { 0, }; //최종 명령어

	system("mode con cols=50 lines=10");
	gotoxy(2, 2); printf("Please enter the name of the program to search");
	gotoxy(7, 3); printf("(Please put an '.exe' on the end)");
	gotoxy(3, 5); printf("->");
	gotoxy(6, 5); scanf_s("%s", process_name, sizeof(process_name));

	sprintf_s(final_tasklist_command, sizeof(final_tasklist_command), "%s%s%s", tasklist_imagename_command_start, process_name, tasklist_imagename_command_end);
	system("mode con cols=100 lines=35");
	system(final_tasklist_command);

	system("pause");

	return;
}

int main() {
	int menu_select_num = 0;
	while (1) {
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
}