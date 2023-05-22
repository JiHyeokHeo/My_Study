#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<string.h>
#include<math.h>
#include <random>

using namespace std;

#define DungeonSize 60
int Dungeon[DungeonSize][DungeonSize];

// 시드값을 얻기 위한 random_device 생성.
std::random_device rd;

// random_device 를 통해 난수 생성 엔진을 초기화 한다.
std::mt19937 gen(rd());

// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
std::uniform_int_distribution<int> dis(0, 99);

//for (int i = 0; i < 5; i++) {
//	std::cout << "난수 : " << dis(gen) << std::endl;
//}

//1.분할한다.
//﻿2. 분할이 끝나면 방을 만든다.
//3. 방을 연결한다.
typedef struct DungeonLocation {
	int r1, c1, r2, c2;
	int r3, c3, r4, c4;
};


DungeonLocation divideDungeon(int depth, int r1, int c1, int r2, int c2) {
	DungeonLocation Location;
	//2. 방을 만든다. 
	if (depth == 0 || (r2 - r1 <= 10 || c2 - c1 <= 10)) {
		for (int i = r1 + 2; i < r2 - 2; i++) {
			for (int j = c1 + 2; j < c2 - 2; j++) {
				Dungeon[i][j] = 1;
			}
		}

		return { r1 + 2, c1 + 2, r2 - 3, c2 - 3, r1 + 2, c1 + 2, r2 - 3, c2 - 3 };
	}

	//1. 분할한다
	//3. 방을 합친다.
	int rLen = r2 - r1;
	int cLen = c2 - c1;
	DungeonLocation temp1, temp2;
	if (rLen / cLen > 1 || (cLen / rLen <= 1 && dis(gen) % 2)) { // 세로분할
		int divideNum = (r2 - r1) * (dis(gen) % 3 + 4) / 10;
		//방 분할
		temp1 = divideDungeon(depth - 1, r1, c1, r1 + divideNum, c2);
		temp2 = divideDungeon(depth - 1, r1 + divideNum, c1, r2, c2);

		//방합치기.
		Dungeon[temp1.r4 + 1][(temp1.c3 + temp1.c4) / 2] = 4;
		Dungeon[temp1.r4 + 2][(temp1.c3 + temp1.c4) / 2] = 4;
		Dungeon[temp2.r1 - 1][(temp2.c1 + temp2.c2) / 2] = 4;
		Dungeon[temp2.r1 - 2][(temp2.c1 + temp2.c2) / 2] = 4;
		int rmin = min((temp1.c3 + temp1.c4) / 2, (temp2.c1 + temp2.c2) / 2);
		int rmax = max((temp1.c3 + temp1.c4) / 2, (temp2.c1 + temp2.c2) / 2);
		for (int i = rmin; i <= rmax; i++) {
			Dungeon[temp2.r1 - 2][i] = 4;
		}
	}
	else {// 가로분할
		int divideNum = (c2 - c1) * (dis(gen) % 3 + 4) / 10;
		//방분할
		temp1 = divideDungeon(depth - 1, r1, c1, r2, c1 + divideNum);
		temp2 = divideDungeon(depth - 1, r1, c1 + +divideNum, r2, c2);

		//방합치기
		Dungeon[(temp1.r3 + temp1.r4) / 2][temp1.c4 + 1] = 3;
		Dungeon[(temp1.r3 + temp1.r4) / 2][temp1.c4 + 2] = 3;
		Dungeon[(temp2.r1 + temp2.r2) / 2][temp2.c1 - 1] = 3;
		Dungeon[(temp2.r1 + temp2.r2) / 2][temp2.c1 - 2] = 3;

		int rmin = min((temp1.r3 + temp1.r4) / 2, (temp2.r1 + temp2.r2) / 2);
		int rmax = max((temp1.r3 + temp1.r4) / 2, (temp2.r1 + temp2.r2) / 2);
		for (int i = rmin; i <= rmax; i++) {
			Dungeon[i][temp2.c1 - 2] = 3;
		}
	}
	Location.r1 = temp1.r1, Location.r2 = temp1.r2, Location.c1 = temp1.c1, Location.c2 = temp1.c2;
	Location.r3 = temp2.r3, Location.r4 = temp2.r4, Location.c3 = temp2.c3, Location.c4 = temp2.c4;

	return Location;
}

void createDungeon() {
	memset(Dungeon, 0, sizeof(Dungeon));
	// 던전을 자르는 횟수 // 5회
	divideDungeon(5, 0, 0, DungeonSize, DungeonSize);
}

void printDungeon() {
	for (int i = 0; i < DungeonSize; i++) {
		for (int j = 0; j < DungeonSize; j++) {
			printf("%d", Dungeon[i][j]);
		}
		printf("\n");
	}
}

int main(void) {
	createDungeon();
	printDungeon();
}