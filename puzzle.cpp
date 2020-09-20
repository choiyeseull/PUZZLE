#include <bangtal.h>
#include <stdio.h>
#include <string.h>
#include <Time.h>
using namespace bangtal;

class Piece {
public:
	int pointX, pointY, radiusX, radiusY;

	//사진 조각의 왼쪽 위 x좌표, 왼쪽 위y좌표, 가로길이, 세로길이 
	Piece(int cx, int cy, int rx, int ry) : pointX(cx), pointY(cy), radiusX(rx), radiusY(ry) {};

	//클릭한 부분이 정답으로 인식되는 범위 안에 들어왔는지 check하는 함수
	bool checkin(int x, int y) {
		return (x > pointX) && (x < pointX + radiusX) && (y > pointY) && (y < pointY + radiusY);
	}
	//사방에 흰색상자가 있는지
	bool check_blanc(int wx, int wy) {
		return ((wx == pointX - radiusX) && (wy == pointY)) || ((wx == pointX + radiusX) && (wy == pointY)) || ((wy == pointY + radiusY) && (wx == pointX)) || ((wy == pointY - radiusY) && (wx == pointX));
	}

};

const int num_of_piece = 16;
Piece piece[num_of_piece] = {
	//{pointX, pointY, radiusX, radius Y}
	{213,480,213,120},
	{426,480,213,120},
	{639,480,213,120},
	{852,480,213,120},

	{213,360,213,120},
	{426,360,213,120},
	{639,360,213,120},
	{852,360,213,120},

	{213,240,213,120},
	{426,240,213,120},
	{639,240,213,120},
	{852,240,213,120},

	{213,120,213,120},
	{426,120,213,120},
	{639,120,213,120},
	{852,120,213,120},

};

//1. 토토로 게임 2. 포뇨게임
int select_game = 0;
auto finish_totoro = Scene::create("토토로퍼즐완성", "images/background2.png");
auto finish_ponyo = Scene::create("포뇨퍼즐완성", "images/background.png");

clock_t start, end;



bool check_finish() {
	if (piece[0].pointX == 213 && piece[0].pointY == 360 &&
		piece[1].pointX == 213 && piece[1].pointY == 120 &&
		piece[2].pointX == 426 && piece[2].pointY == 480 &&
		piece[3].pointX == 852 && piece[3].pointY == 360 &&
		piece[4].pointX == 213 && piece[4].pointY == 240 &&

		piece[5].pointX == 639 && piece[5].pointY == 480 &&
		piece[6].pointX == 852 && piece[6].pointY == 480 &&
		piece[7].pointX == 639 && piece[7].pointY == 240 &&
		piece[8].pointX == 639 && piece[8].pointY == 120 &&
		piece[9].pointX == 426 && piece[9].pointY == 240 &&

		piece[10].pointX == 213 && piece[10].pointY == 480 &&
		piece[11].pointX == 852 && piece[11].pointY == 240 &&
		piece[12].pointX == 426 && piece[12].pointY == 360 &&
		piece[13].pointX == 426 && piece[13].pointY == 120 &&
		piece[14].pointX == 639 && piece[14].pointY == 360 &&
		piece[15].pointX == 852 && piece[15].pointY == 120) {


		//3. 성공하면 걸린 시간 출력 
		end = clock();
		if (select_game == 1) {
			finish_totoro->enter();
		}
		else if (select_game == 2) {
			finish_ponyo->enter();
		}
		int do_time = (end - start) / CLOCKS_PER_SEC;
		int min = do_time / 60;
		int sec = do_time % 60;

		char s1[100];
		char s2[50];
		
		sprintf_s(s1, "%d", min);	//정수를 문자열로 바꾸기
		strcat_s(s1, "분");			

		sprintf_s(s2, "%d", sec);
		strcat_s(s2, "초");

		strcat_s(s1, s2);
		showMessage(s1);
	}
	return true;
}


int main() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	//1. 시작화면 : 게임선택
	auto menu = Scene::create("게임선택", "images/menu.png");

	//1. 시작화면 : 토토로, 포뇨 사진
	auto totoro = Object::create("images/totoro.png", menu,80, 150);
	auto ponyo = Object::create("images/ponyo.png", menu, 700, 150);
	
	//2. 포뇨게임, 토토로게임 장면 생성
	auto totoro_puzzle = Scene::create("토토로퍼즐", "images/background2.png");
	auto scene = Scene::create("포뇨퍼즐", "images/background.png");

	//2. 토토로 클릭하면 토토로 게임 실행 
	totoro->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		select_game = 1;
		totoro_puzzle->enter();
		start = clock();

		return true;
	});
	//2. 포뇨 클릭하면 포뇨 게임 실행 
	ponyo->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		select_game = 2;
		scene->enter();
		start = clock();

		return true;
	});

	//*******************************************  < 1. 포뇨 게임 >  ****************************************************
	//흰상자
	int blanc = 15;
	auto blancX = piece[blanc].pointX;
	auto blancY = piece[blanc].pointY;

	ObjectPtr picture[num_of_piece];
	
	picture[0] = Object::create("images/5.png", scene, piece[0].pointX, piece[0].pointY, true);
	picture[1] = Object::create("images/13.png", scene, piece[1].pointX, piece[1].pointY, true);
	picture[2] = Object::create("images/2.png", scene, piece[2].pointX, piece[2].pointY, true);
	picture[3] = Object::create("images/8.png", scene, piece[3].pointX, piece[3].pointY, true);

	picture[4] = Object::create("images/9.png", scene, piece[4].pointX, piece[4].pointY, true);
	picture[5] = Object::create("images/3.png", scene, piece[5].pointX, piece[5].pointY, true);
	picture[6] = Object::create("images/4.png", scene, piece[6].pointX, piece[6].pointY, true);
	picture[7] = Object::create("images/11.png", scene, piece[7].pointX, piece[7].pointY, true);

	picture[8] = Object::create("images/15.png", scene, piece[8].pointX, piece[8].pointY, true);
	picture[9] = Object::create("images/10.png", scene, piece[9].pointX, piece[9].pointY, true);
	picture[10] = Object::create("images/1.png", scene, piece[10].pointX, piece[10].pointY, true);
	picture[11] = Object::create("images/12.png", scene, piece[11].pointX, piece[11].pointY, true);

	picture[12] = Object::create("images/6.png", scene, piece[12].pointX, piece[12].pointY, true);
	picture[13] = Object::create("images/14.png", scene, piece[13].pointX, piece[13].pointY, true);
	picture[14] = Object::create("images/7.png", scene, piece[14].pointX, piece[14].pointY, true);
	picture[blanc] = Object::create("images/16.png", scene, piece[blanc].pointX, piece[blanc].pointY, true);

	int tmpx, tmpy;
	picture[0]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[0].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[0].pointX, piece[0].pointY);
			picture[0]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[0].pointX;
			piece[0].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[0].pointY;
			piece[0].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	picture[1]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[1].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[1].pointX, piece[1].pointY);
			picture[1]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[1].pointX;
			piece[1].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[1].pointY;
			piece[1].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	picture[2]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[2].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[2].pointX, piece[2].pointY);
			picture[2]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[2].pointX;
			piece[2].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[2].pointY;
			piece[2].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	picture[3]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[3].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[3].pointX, piece[3].pointY);
			picture[3]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[3].pointX;
			piece[3].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[3].pointY;
			piece[3].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	picture[4]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[4].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[4].pointX, piece[4].pointY);
			picture[4]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[4].pointX;
			piece[4].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[4].pointY;
			piece[4].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	picture[5]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[5].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[5].pointX, piece[5].pointY);
			picture[5]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[5].pointX;
			piece[5].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[5].pointY;
			piece[5].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	picture[6]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[6].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[6].pointX, piece[6].pointY);
			picture[6]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[6].pointX;
			piece[6].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[6].pointY;
			piece[6].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	picture[7]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[7].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[7].pointX, piece[7].pointY);
			picture[7]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[7].pointX;
			piece[7].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[7].pointY;
			piece[7].pointY = tmpy;

		}
	check_finish();
	return true;
	});

	picture[8]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[8].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[8].pointX, piece[8].pointY);
			picture[8]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[8].pointX;
			piece[8].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[8].pointY;
			piece[8].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	picture[9]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[9].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[9].pointX, piece[9].pointY);
			picture[9]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[9].pointX;
			piece[9].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[9].pointY;
			piece[9].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	picture[10]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[10].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[10].pointX, piece[10].pointY);
			picture[10]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[10].pointX;
			piece[10].pointX = tmpx;

			tmpy = blancY;
			blancY = piece[10].pointY;
			piece[10].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	picture[11]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[11].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[11].pointX, piece[11].pointY);
			picture[11]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[11].pointX;
			piece[11].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[11].pointY;
			piece[11].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	picture[12]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[12].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[12].pointX, piece[12].pointY);
			picture[12]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[12].pointX;
			piece[12].pointX = tmpx;

			tmpy = blancY;
			blancY = piece[12].pointY;
			piece[12].pointY = tmpy;

		}
	check_finish();
	return true;
	});

	picture[13]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[13].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[13].pointX, piece[13].pointY);
			picture[13]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[13].pointX;
			piece[13].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[13].pointY;
			piece[13].pointY = tmpy;

		}
	check_finish();
	return true;
	});

	picture[14]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[14].check_blanc(blancX, blancY)) {
			picture[blanc]->locate(scene, piece[14].pointX, piece[14].pointY);
			picture[14]->locate(scene, blancX, blancY);

			tmpx = blancX;
			blancX = piece[14].pointX;
			piece[14].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[14].pointY;
			piece[14].pointY = tmpy;
		}
	check_finish();
	return true;
	});

//*******************************************  < 2. 토토로 게임 >  ***************************************************
	
	ObjectPtr totoro_pic[num_of_piece];
	
	totoro_pic[0] = Object::create("images/totoro_5.png", totoro_puzzle, piece[0].pointX, piece[0].pointY, true);
	totoro_pic[1] = Object::create("images/totoro_13.png", totoro_puzzle, piece[1].pointX, piece[1].pointY, true);
	totoro_pic[2] = Object::create("images/totoro_2.png", totoro_puzzle, piece[2].pointX, piece[2].pointY, true);
	totoro_pic[3] = Object::create("images/totoro_8.png", totoro_puzzle, piece[3].pointX, piece[3].pointY, true);

	totoro_pic[4] = Object::create("images/totoro_9.png", totoro_puzzle, piece[4].pointX, piece[4].pointY, true);
	totoro_pic[5] = Object::create("images/totoro_3.png", totoro_puzzle, piece[5].pointX, piece[5].pointY, true);
	totoro_pic[6] = Object::create("images/totoro_4.png", totoro_puzzle, piece[6].pointX, piece[6].pointY, true);
	totoro_pic[7] = Object::create("images/totoro_11.png", totoro_puzzle, piece[7].pointX, piece[7].pointY, true);

	totoro_pic[8] = Object::create("images/totoro_15.png", totoro_puzzle, piece[8].pointX, piece[8].pointY, true);
	totoro_pic[9] = Object::create("images/totoro_10.png", totoro_puzzle, piece[9].pointX, piece[9].pointY, true);
	totoro_pic[10] = Object::create("images/totoro_1.png", totoro_puzzle, piece[10].pointX, piece[10].pointY, true);
	totoro_pic[11] = Object::create("images/totoro_12.png", totoro_puzzle, piece[11].pointX, piece[11].pointY, true);

	totoro_pic[12] = Object::create("images/totoro_6.png", totoro_puzzle, piece[12].pointX, piece[12].pointY, true);
	totoro_pic[13] = Object::create("images/totoro_14.png", totoro_puzzle, piece[13].pointX, piece[13].pointY, true);
	totoro_pic[14] = Object::create("images/totoro_7.png", totoro_puzzle, piece[14].pointX, piece[14].pointY, true);
	totoro_pic[blanc] = Object::create("images/16.png", totoro_puzzle, piece[blanc].pointX, piece[blanc].pointY, true);


	totoro_pic[0]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[0].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[0].pointX, piece[0].pointY);
			totoro_pic[0]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[0].pointX;
			piece[0].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[0].pointY;
			piece[0].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	totoro_pic[1]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[1].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[1].pointX, piece[1].pointY);
			totoro_pic[1]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[1].pointX;
			piece[1].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[1].pointY;
			piece[1].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	totoro_pic[2]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[2].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[2].pointX, piece[2].pointY);
			totoro_pic[2]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[2].pointX;
			piece[2].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[2].pointY;
			piece[2].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	totoro_pic[3]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[3].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[3].pointX, piece[3].pointY);
			totoro_pic[3]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[3].pointX;
			piece[3].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[3].pointY;
			piece[3].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	totoro_pic[4]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[4].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[4].pointX, piece[4].pointY);
			totoro_pic[4]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[4].pointX;
			piece[4].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[4].pointY;
			piece[4].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	totoro_pic[5]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[5].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[5].pointX, piece[5].pointY);
			totoro_pic[5]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[5].pointX;
			piece[5].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[5].pointY;
			piece[5].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	totoro_pic[6]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[6].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[6].pointX, piece[6].pointY);
			totoro_pic[6]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[6].pointX;
			piece[6].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[6].pointY;
			piece[6].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	totoro_pic[7]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[7].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[7].pointX, piece[7].pointY);
			totoro_pic[7]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[7].pointX;
			piece[7].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[7].pointY;
			piece[7].pointY = tmpy;

		}
	check_finish();
	return true;
	});

	totoro_pic[8]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[8].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[8].pointX, piece[8].pointY);
			totoro_pic[8]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[8].pointX;
			piece[8].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[8].pointY;
			piece[8].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	totoro_pic[9]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[9].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[9].pointX, piece[9].pointY);
			totoro_pic[9]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[9].pointX;
			piece[9].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[9].pointY;
			piece[9].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	totoro_pic[10]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[10].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[10].pointX, piece[10].pointY);
			totoro_pic[10]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[10].pointX;
			piece[10].pointX = tmpx;

			tmpy = blancY;
			blancY = piece[10].pointY;
			piece[10].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	totoro_pic[11]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[11].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[11].pointX, piece[11].pointY);
			totoro_pic[11]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[11].pointX;
			piece[11].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[11].pointY;
			piece[11].pointY = tmpy;
		}
	check_finish();
	return true;
	});

	totoro_pic[12]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[12].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[12].pointX, piece[12].pointY);
			totoro_pic[12]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[12].pointX;
			piece[12].pointX = tmpx;

			tmpy = blancY;
			blancY = piece[12].pointY;
			piece[12].pointY = tmpy;

		}
	check_finish();
	return true;
	});

	totoro_pic[13]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[13].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[13].pointX, piece[13].pointY);
			totoro_pic[13]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[13].pointX;
			piece[13].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[13].pointY;
			piece[13].pointY = tmpy;

		}
	check_finish();
	return true;
	});

	totoro_pic[14]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (piece[14].check_blanc(blancX, blancY)) {
			totoro_pic[blanc]->locate(totoro_puzzle, piece[14].pointX, piece[14].pointY);
			totoro_pic[14]->locate(totoro_puzzle, blancX, blancY);

			tmpx = blancX;
			blancX = piece[14].pointX;
			piece[14].pointX = tmpx;
			tmpy = blancY;
			blancY = piece[14].pointY;
			piece[14].pointY = tmpy;
		}
	check_finish();
	return true;
	});

//********************************************************************************************

	startGame(menu);
	return 0;
}