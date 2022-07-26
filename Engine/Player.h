#pragma once
#include "Graphics.h"
#include "MainWindow.h"
#include "Walls.h"
#include "Sectors.h"
class Player {
public:
	void move(MainWindow& wnd);
	float Sin(int angle);
	float Cos(int angle);
	void draw(Graphics& gfx); 
	void initp();
private:
	int dist(int x1, int y1, int x2, int y2);
private:
	int px, py, z; //playerpos
	int a; //player angle
	int l;//up down
	float diff = 0;
	float diff3 = 0;
	int secnum = 4, numwall = 16;
	Walls W[30];
	Sectors S[30];
};