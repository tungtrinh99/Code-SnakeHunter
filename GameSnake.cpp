// GameSnake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string.h>
#include "kmin_console.h"
#include <ctime>
#include<conio.h>
#include <fstream>
#include<time.h>
#include<cstdio>



using namespace std;

#define DOT_RAN 254 // khời tạo hình ảnh của một đốt rắn
#define Max 100	// số đốt rắn tối đa
#define Len 1	// mã hướng lên
#define Xuong 2 // mã hướng xuống
#define Trai 3	//mã sang trái	
#define Phai 4	//mã sang phải	
#define tuongTren 1 // vị trí của tường trên trong console
#define tuongDuoi 13	// vị trí của tường dưới trong console	
#define tuongTrai 3	//vị trí của tường trái trong console
#define tuongPhai 53	//vị trí của tường phải trong console
#define MAUNEN 176 //màu nền của bảng lựa chọn
#define MAUCHU 9//màu chữ của bảng lựa chọn

typedef char str[31];
str thaotac[4] = { "NEW GAME","HIGHSCORE","ABOUT","QUIT"};//khai báo mảng thaotac chứa 4 lựa chọn cua menu chinh
str thaotac8[2] = { "MORDEN" ,"CLASSIC" };// 2 lua chon phu
str level[3] = { "DE","TRUNG BINH","KHO" };
str yesno[2] = { "YES","NO" };
struct toaDo {
	int x;
	int y;
};

toaDo snake[Max]; // tọa độ của các đốt rắn
int soDot = 3;// so lượng đốt rắn khởi tạo
int doKho = 100;
int diem = 0;
void khoitaoRan();
void hienthiRan(toaDo dotCuoicu);
toaDo diChuyen(int huong);
void batsuKien(int& huong);
void veTuong();
bool kiemtraThua();
void xulyThua();
toaDo hienthiMoi();
bool kiemtradaanMoi(toaDo moi);
void themDot();
void diemCao();
void classic();
void morden();
void inmenu();
void menu();
void mnuu();
void menu8();
void inmenu8();
void mnu();
void about();
int docdiemCao();
void run();
void menuyesno();
void inmenuyesno(int vt);
void mnuyn();
int clock1();
void menulevel();
void inmenulevel();
void mnulevel();
void reset();
int ghidiemCao();
int ghidiemCao();
//khởi tạo 3 đốt đầu tiên của rắn
void khoitaoRan()
{
	snake[0].x = tuongTrai+3;
	snake[1].x = tuongTrai+2;
	snake[2].x = tuongTrai+1;
	snake[0].y = tuongTren+2;
	snake[1].y = tuongTren+2;
	snake[2].y = tuongTren+2;

}
// hiển thị rắn theo tọa độ đã lưu trong mảng
void hienthiRan(toaDo dotCuoicu)
{
	setTextColor(10);
	//hiển thị vị trí rắn theo tọa độ
	for (int i = 0;i < soDot;i++)
	{
		gotoXY(snake[i].x, snake[i].y);
		cout << char(DOT_RAN);
	}
	gotoXY(dotCuoicu.x, dotCuoicu.y);
	cout << " ";
}
//chuyển động của rắn
toaDo diChuyen(int huong)
{
	toaDo dotCuoicu = snake[soDot - 1];
	//hiển thị đốt mới
	for (int i = soDot - 1;i >= 1;i--)
	{
		snake[i] = snake[i - 1];
	}
	//xóa đốt cuối theo hướng di chuyển của rắn
	switch (huong)
	{
	
	case Len:
		snake[0].y--;
		break;
	case Xuong:
		snake[0].y++;
		break;
	case Trai:
		snake[0].x--;
		break;
	case Phai:
		snake[0].x++;
		break;

	}
	return dotCuoicu;
	
}
//bắt sự kiện di chuyển
void batsuKien(int& huong)
{
	int key = inputKey();

	if (key == 'w' || key == 'W' || key == KEY_UP && huong != Xuong) {
		huong = Len;
		PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);

	}
	else if (key == 's' || key == 'S' || key == KEY_DOWN && huong != Len)
	{
		huong = Xuong;
		PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
	}
	else if (key == 'a' || key == 'A' || key == KEY_LEFT && huong != Phai)
	{
		huong = Trai;
		PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
	}
	else if (key == 'd' || key == 'D' || key == KEY_RIGHT && huong != Trai)
	{
		huong = Phai;
		PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC);
	}
	else if (key == 112)
	{
		gotoXY(1, 21);
		printf("                 ");
		while (1)
		{
			if (_kbhit())
			{
				int p = _getch();
				if (p == 112)
					break;
				if (p == 27)
				{
					clrscr();
					reset();
					mnuu();
				}
			}
			gotoXY(27, 21);
			Sleep(200);
			printf("DANG TAM DUNG BAM p DE TIEP TUC -- BAM ESC DE QUAY LAI MENU");
			gotoXY(27, 21);
			Sleep(200);
			printf("                                                           ");

		}

	}
	
}
//vẽ 4 bức tường 
void veTuong()
{
	setTextColor(15);
	//tường trên và tường dưới
	for (int i = tuongTrai;i <= tuongPhai;i++)
	{
		gotoXY(i, tuongTren);
		cout << char(220);
		gotoXY(i, tuongDuoi);
		cout << char(223);
	}
	//tường trái và tường phải
	for (int i = tuongTren+1;i <= tuongDuoi-1;i++)
	{
		gotoXY(tuongTrai,i);
		cout << char(221);
		gotoXY(tuongPhai, i);
		cout << char(222);
	}
	
	
	
}
//kiểm tra thua bằng tọa độ đầu rắn trùng với tọa độ của tường bằng hàm true false
bool kiemtrachamTuong() {
	if (snake[0].x == tuongTrai|| snake[0].x == tuongPhai|| snake[0].y == tuongTren|| snake[0].y == tuongDuoi)
		return 1;
	
	
}
 //kiểm tra thua khi đầu rắn trùng với tọa độ của một đốt trong thân
bool kiemtrachamDuoi() {
	for (int i=1;i < soDot;i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			return 1;
		
	}
}
//ham kiem tra thua khi ran dam vao tuong hoac can vao than
bool kiemtraThua()
{
	bool kt1= kiemtrachamDuoi();
	bool kt2 =kiemtrachamTuong();
	if (kt1 == 1 || kt2 == 1) {
		PlaySound(TEXT("endGame.wav"), NULL, SND_ASYNC);
		return 1;
	}
	return 0;
}
//che do morden
void morden() {
	
	khoitaoRan();
	// game loop
	int x = 0, y = 0;
	int huong = Phai;

	gotoXY(tuongPhai + 5, tuongTren + 1);//vị trí hiển thị điểm
	setTextColor(15);
	cout << "Diem : 0";
	gotoXY(tuongPhai + 5, tuongTren + 5);setTextColor(12); cout << "AN P DE TAM DUNG TRO CHOI";
	toaDo moi = hienthiMoi();
	noCursorType(); // hàm xóa con trỏ
	
	while (true)
	{
		toaDo dotCuoicu = diChuyen(huong);
		batsuKien(huong);
		hienthiRan(dotCuoicu);
		veTuong();
		if (kiemtradaanMoi(moi) == 1) {
			moi = hienthiMoi();
			themDot();
			diem++;
			gotoXY(tuongPhai + 5, tuongTren + 1);//vị trí hiển thị điểm
			setTextColor(15);
			cout << "Diem : " << diem;
		}
		if (kiemtraThua()==1)
		{
			Sleep(2000);
			
			clrscr();
			setTextColor(15);
			gotoXY(55, 13);
			cout << "SCORE " << diem;
			gotoXY(55, 14);

			Sleep(2000);
			break;
		}
		Sleep(doKho);
	}
	
	xulyThua();
	
}
//Che do classic
void classic() {
	khoitaoRan();
	// game loop
	int x = 0, y = 0;
	int huong = Phai;
	
	gotoXY(tuongPhai + 5, tuongTren + 1);//vị trí hiển thị điểm
	setTextColor(15);
	cout << "Diem : 0";
	gotoXY(tuongPhai + 5, tuongTren + 5);setTextColor(12); cout << "AN P DE TAM DUNG TRO CHOI";
	toaDo moi = hienthiMoi();
	noCursorType(); // hàm xóa con trỏ

	while (true)
	{
		toaDo dotCuoicu = diChuyen(huong);
		batsuKien(huong);
		hienthiRan(dotCuoicu);
		for (int i = 0;i < soDot;i++) {
			if (snake[i].x <= tuongTrai) snake[i].x = tuongPhai - 1;
			if (snake[i].x >=tuongPhai) snake[i].x = tuongTrai + 1;
			if (snake[i].y <=tuongTren) snake[i].y = tuongDuoi - 1;
			if (snake[i].y >=tuongDuoi) snake[i].y = tuongTren + 1;	
		}
		veTuong();
		if (kiemtradaanMoi(moi) == 1) {
			moi = hienthiMoi();
			themDot();
			diem++;
			gotoXY(tuongPhai + 5, tuongTren + 1);//vị trí hiển thị điểm
			setTextColor(15);
			cout << "Diem : " << diem;
		}	
		if (kiemtrachamDuoi() == 1)
		{
			Sleep(2000);
			PlaySound(TEXT("endGame.wav"), NULL, SND_ASYNC);
			clrscr();
			setTextColor(15);
			gotoXY(55, 13);
			cout << "SCORE " << diem;
			gotoXY(55, 14);

			Sleep(2000);
			break;
		}	
		Sleep(doKho);
	}
	xulyThua();
	
}
// hàm xóa màn hình và hiển thị game over khi thua 
void xulyThua()	 {
		
		
		clrscr();
		gotoXY(55, 13);
		cout << "GAME OVER" ;
		Sleep(2000);
		ghidiemCao();
		clrscr();
		mnuyn();
	
}
// hàm hiển thị mồi
toaDo hienthiMoi() {
	int i = 1 + rand() % (15 - 1 + 1);
	setTextColor(i);
	//hiển thị ngẫu nhiên mồi trong giới hạn của khung tường
	srand(time(NULL));
	//int k = rand() % 10;// cong thuc : a + rand()%(b-a+1)
	int x = tuongTrai + 1 + rand() % ((tuongPhai - 1) - (tuongTrai + 1) + 1);
	int y = tuongTren + 1 + rand() % ((tuongDuoi - 1) - (tuongTren + 1) + 1);
	gotoXY(x, y);
	cout << char(DOT_RAN);// hình ảnh của mồi
	return toaDo{ x,y };
	
	
}
//hàm kiểm tra ăn mồi khi tọa độ đầu rắn trùng với tọa độ của mồi
bool kiemtradaanMoi(toaDo moi) {
	if (snake[0].x == moi.x && snake[0].y == moi.y) {
		
		
		return 1;
	}
	else {
		return 0;
	}
}
//hàm thêm đốt khi ăn mồi
void themDot() {
	snake[soDot] = snake[soDot - 1];
	soDot++;
	PlaySound(TEXT("eatFood.wav"), NULL, SND_ASYNC);
	
}
//Hàm hiện menu chính
void inmenu(int vt)
{
	int i;
	//clrscr();
	
	for (i = 1; i <= 4; i++)
	{
		if (i == vt) setTextColor(2);
		else setTextColor(7);
		gotoXY(53, 8 + 1 + i); cprintf(thaotac[i - 1]);
	}
}
//Hàm điều khiển menu chính
void menu(int vt)
{
	char c;
	do
	{
		inmenu(vt);
		gotoXY(80, 25);
		c = getch();
		switch (c)
		{
		case 72: vt--; if (vt == 0) vt = 4; break;
		case 80: vt++; if (vt == 5) vt = 1; break;
		case 27: exit(0);
		}
	} while (c != 13);
	switch (vt)
	{
	case 1: clrscr();   mnulevel();menu(vt); break;
	case 2: clrscr();  docdiemCao(); menu(vt); break;
	case 3: clrscr(); about(); menu(vt);break;
	case 4: exit(0);
	
	}
}
//
void mnuu() {
	menu(1);
}
//hàm hiện menu chon che do choi
void inmenu8(int vt) {
	int i;
	//clrscr();
	gotoXY(45,11 ); setTextColor(9);
	cout << "MOI BAN CHON CHE DO CHOI";
	for (i = 1; i <= 2; i++)
	{
		if (i == vt) setTextColor(2);
		else setTextColor(7);
		gotoXY(53,	13+i ); cprintf(thaotac8[i-1]);
		
	}
}
//ham dieu khien menu chon che do choi 
void menu8(int vt)
{
	char c;
	do
	{
		inmenu8(vt);
		gotoXY(80, 25);
		c = getch();
		switch (c)
		{
		case 72: vt--; if (vt == 0) vt = 2; break;
		case 80: vt++; if (vt == 3) vt = 1; break;
		}
	} while (c != 13);
	switch (vt) 
	{
	case 1: clrscr(); morden();  menu8(vt); break;
	case 2: clrscr(); classic(); menu8(vt); break;
	}
}
//dua ham menu8 vao
void mnu() {
	
	menu8(1);
}
// in menu level
void inmenulevel(int vt) {
	int i;
	//clrscr();
	gotoXY(52, 9);setTextColor(9); cout << "SELECT LEVEL";
	for (i = 1; i <= 3; i++)
	{
		if (i == vt) setTextColor(2);
		else setTextColor(7);
		
		gotoXY(53, 8 + 1 + i); cprintf(level[i - 1]);
	}
}
// dieu khien menu level
void menulevel(int vt) {
	char c;
	do
	{
		inmenulevel(vt);
		gotoXY(80, 25);
		c = getch();
		switch (c)
		{
		case 72: vt--; if (vt == 0) vt = 3; break;
		case 80: vt++; if (vt == 4) vt = 1; break;
		case 27: exit(0);
		}
	} while (c != 13);
	switch (vt)
	{
	case 1: clrscr(); doKho = 150; mnu();menulevel(vt); break;
	case 2: clrscr(); doKho = 100;  mnu(); menulevel(vt); break;
	case 3: clrscr(); doKho = 70; mnu(); menulevel(vt);break;


	}
}
//
void mnulevel() {
	menulevel(1);
}
//doc file diem cao
int docdiemCao() {
	gotoXY(50, 9); setTextColor(9);
	cout << "HIGH SCORE";
	string data;
	fstream f;
	f.open("highscore.txt",ios::in);
	for (int i = 0;i < 5;i++) {
		f >> data;
		gotoXY(50, 10+i);
		cout << data;
		f >> data;
		gotoXY(60,10+ i);
		cout << "" << data << endl << endl;
	}	
	getch();
	clrscr();
	return 0;
}
int ghidiemCao() {
		char data[20];
	// mo 1 file trong che do write
		fstream f;
		f.open("highscore.txt", ios::out | ios::app);
		gotoXY(50, 13);
		cout << "Nhap ten cua ban: ";
		cin.getline(data, 20);
		gotoXY(50, 14);
		f << data << endl;
		//cin.getline(data,20);
		f << diem << endl;
		f.close();
	
	return 0;

}
//about
void about() {
	//clrscr();
	gotoXY(50, 9);
	cout << "SINH VIEN";
	gotoXY(50, 10);
	cout << "TRINH XUAN TUNG";
	gotoXY(50, 11);
	cout << "NGUYEN NGOC KHANH";
	gotoXY(50, 12);
	cout << "NGUYEN TIEN DUNG";
	gotoXY(50, 13);
	cout << "DE TAI";
	gotoXY(50, 14);
	cout << "GAME RAN SAN MOI";
	getch();
	clrscr();
}
// menu yes no 
void menuyesno(int vt) {
	char c;
	do
	{
		inmenuyesno(vt);
		gotoXY(80, 25);
		c = getch();
		switch (c)
		{
		case 72: vt--; if (vt == 0) vt = 2; break;
		case 80: vt++; if (vt == 3) vt = 1; break;
		}
	} while (c != 13);
	switch (vt)
	{
	case 1: clrscr(); reset(); mnuu();  menu8(vt); break;
	case 2: exit(0);
	}
}

// in menu ysno
void inmenuyesno(int vt) {
	int i;
	//clrscr();
	gotoXY(45, 11); setTextColor(7);
	cout << "BAN CO MUON CHOI LAI KHONG ?";
	
	for (i = 1; i <= 2; i++)
	{
		if (i == vt) setTextColor(2);
		else setTextColor(7);
		gotoXY(57, 13 + i); cprintf(yesno[i - 1]);

	}
}
//
void mnuyn() {
	menuyesno(1);
}
//reset rắn về dạng ban đầu
void reset() {
	soDot = 3;
}
// hiện đồng hồ
int clock1() {
	
	int s = 0, m = 0, h = 0;
	
	while (1) {
		gotoXY(tuongPhai + 15, tuongTren + 1);
		printf("TIME : %d:%d:%d ", h, m, s);
		//
		s++;
		if (s == 59) { s = 0; m++; }
		if (m == 59) { m = 0;h++; }
		Sleep(1000);
		cout << "                  ";
	}
	getch();
	return 0;
	
}
//hàm chạy chương trình game
void run() {
	int x = 0;
	
	while (x <= 100) {
		noCursorType();
		gotoXY(50, 13);
		cout << "LOADING ... "; 
		cout << x ;
		gotoXY(65, 13);
		cout << "%";
		if (x == 100)
			Sleep(200);
		Sleep(10);
		x++;
	}
	
	clrscr();
	PlaySound(TEXT("Cut_LostSky.wav"), NULL, SND_ASYNC);
	 gotoXY(43, 9); setTextColor(9);cout << ">>>>>>GAME RAN SAN MOI<<<<<<<";
	menu(1);
	
	system("pause");
	//cin.get();
}
int main()
{
	
	system("cls");

	run();
	
	return 0;
}
