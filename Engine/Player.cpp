#include "Player.h"
#include <math.h>
#include <winuser.h>
int loadSectors[] = {
	//wall start,wall end, z1 height , z2 height,red,green,blue
		0,4,0,40,0,255,0,0,0,255,
		4,8,0,40,0,255,0,0,0,255,
		8,12,0,40,0,255,0,0,0,255,
		12,16,0,40,0,255,0,0,0,255,
};
int loadWalls[] = {
	//x1,y1,x2,y2,red,green,blue
	0, 0, 32, 0,255,255,255,
	32, 0, 32,32,255,0,0,
	32,32,0,32,255,255,255,
	0,32,0,0,255,0,0,

	64, 0, 96, 0,255,255,0,
	96, 0, 96,32,0,0,255,
	96,32, 64,32,0,255,0,
	64,32, 64, 0,0,0,255,

	64, 64, 96,64, 255,255,0,
	96, 64, 96,96, 255,0,255,
	96, 96, 64,96, 255,255,0,
	64, 96, 64,64, 255,0,255,

	0,64,32,64, 255,0,255,
	32, 64,32,96, 0,255,0,
	32, 96,0,96, 255,255,16,
	0, 96,0,64, 255,123,214,

};
void Player::initp() {
	 px = 70, py = -110, z = 20; //playerpos
	 a = 270; //player angle
	l = 0;//up down
	int s, w, v1 = 0, v2 = 0;
	for (s = 0; s < secnum; s++) {
		S[s].ws = loadSectors[v1 + 0];
		S[s].we = loadSectors[v1 + 1];
		S[s].z1 = loadSectors[v1 + 2];
		S[s].z2 = loadSectors[v1 + 3]-loadSectors[v1+2];
		S[s].r1 = loadSectors[v1 + 4];
		S[s].g1 = loadSectors[v1 + 5];
		S[s].b1 = loadSectors[v1 + 6];
		S[s].r2 = loadSectors[v1 + 7];
		S[s].g2 = loadSectors[v1 + 8];
		S[s].b2 = loadSectors[v1 + 9];
		v1 += 10;
	
	for (w = S[s].ws; w < S[s].we; w++) {
		W[w].x1 = loadWalls[v2 + 0];
		W[w].y1 = loadWalls[v2 + 1];
		W[w].x2 = loadWalls[v2 + 2];
		W[w].y2 = loadWalls[v2 + 3];
		W[w].r = loadWalls[v2 + 4];
		W[w].g = loadWalls[v2 + 5];
		W[w].b = loadWalls[v2 + 6];
		v2 += 7;
	 }
	}
}
int Player::dist(int x1, int y1, int x2, int y2)
{
	return sqrt((x2-x1)*(x2 - x1)+ (y2 - y1) * (y2 - y1));
}
void Player::move(MainWindow& wnd) {
	float diff1 = wnd.mouse.GetPosX();
	float diff2 = wnd.mouse.GetPosY();
	if (diff != diff1) {
		if (diff < diff1) {
			a -= (diff - diff1) / 5;
		}
		if (diff > diff1) {
			a += (diff1 - diff) / 5;
		}
	}
	int dx = Sin(a)*2;
	int dy = Cos(a)*2;
	if (diff2 != diff3) {
		if (diff2 < diff3) {
			l -= (diff2 - diff3) / 5;
		}
		if (diff2 > diff3) {
			l += (diff3 - diff2) / 5;
		}
		if (l >= 90) {
			l = 90;
		}
		if (l <= -90) {
			l = -90;
		}
	}
		if (!wnd.kbd.KeyIsPressed('Q')) {
			SetCursorPos(320, 240);
			wnd.mouse.setpos(320, 215);
			ShowCursor(false);
		}
	if (wnd.kbd.KeyIsPressed('W')&&!wnd.kbd.KeyIsPressed('M')) {
		px += dx; py += dy;
	}
	 if (wnd.kbd.KeyIsPressed('S')&&!wnd.kbd.KeyIsPressed('M')) {
		px -= dx; py -= dy;
	}
	if (wnd.kbd.KeyIsPressed('D') && !wnd.kbd.KeyIsPressed('M')) {
		px += dy; py -= dx;
	}
	if (wnd.kbd.KeyIsPressed('A') && !wnd.kbd.KeyIsPressed('M')) {
		px -= dy;
		py += dx;
	}
	if (wnd.kbd.KeyIsPressed('W') && wnd.kbd.KeyIsPressed('M')) {
		z -= 1;
	}
	if (wnd.kbd.KeyIsPressed('S') && wnd.kbd.KeyIsPressed('M')) {
		z += 1;
	}
	diff = wnd.mouse.GetPosX();
	diff3 = wnd.mouse.GetPosY();
}
float Player::Sin(int angle) {
	return sin(angle / 180.f * 3.14159265359f);
}
float Player::Cos(int angle) {
	return cos(angle / 180.f * 3.14159265359f);
}
void clip(int* x1, int*y1, int*z1, int  x2, int  y2, int z2) {
	float da = *y1;
	float db = y2;
	float d = da - db;
	if (d == 0) { 
		d = 1;
	}
	float s = da / (da - db);
	*x1 = *x1 + s * (x2 - (*x1));
	*y1 = *y1 + s * (y2 - (*y1));
	if (*y1 == 0) {
		*y1 = 1;
	}
	*z1 = *z1 + s * (z2 - (*z1));

}
void Player::draw(Graphics& gfx)
{
	int	s, w,loop, wx[4]{}, wy[4]{}, wz[4]{};
	float CS = Cos(a), SN = Sin(a);
	for (s = 0; s < secnum - 1; s++) {
		for (w = 0; w < secnum - s - 1; w++) {
			if (S[w].d < S[w + 1].d) {
				Sectors st = S[w]; 
				S[w] = S[w + 1];
				S[w + 1] = st;
			}
		}
	}
	for (s = 0; s < secnum; s++) {
		S[s].d = 0;
		if (z < S[s].z1)	  { S[s].surface = 1; }
		else if (z > S[s].z2) { S[s].surface = 2; }
		else				  { S[s].surface = 0; }
		for (loop = 0; loop < 2; loop++) {
		for(w=S[s].ws;w<S[s].we;w++){

			
		int x1 = W[w].x1 - px, y1 = W[w].y1 - py;
		int x2 = W[w].x2 - px, y2 = W[w].y2 - py;
		if (loop == 0) { int swp = x1; x1 = x2; x2 = swp; swp = y1; y1 = y2; y2 = swp; }
		wx[0] = x1 * CS - y1 * SN;
		wx[1] = x2 * CS - y2 * SN;
		wx[2] = wx[0];
		wx[3] = wx[1];
		wy[0] = y1 * CS + x1 * SN;
		wy[1] = y2 * CS + x2 * SN;
		wy[2] = wy[0];
		wy[3] = wy[1];
		S[s].d += dist(0, 0, (wx[0] + wx[1]) / 2, (wy[0] + wy[1]) / 2);
		wz[0] = S[s].z1 - z + ((l * wy[0]) / 32);
		wz[1] = S[s].z1 - z + ((l * wy[1]) / 32);
		wz[2] = wz[0] + S[s].z2;
		wz[3] = wz[1] + S[s].z2;
		if (wy[0] < 1 && wy[1] < 1) { continue; }
		if (wy[0] < 1) {
			clip(&wx[0], &wy[0], &wz[0], wx[1], wy[1], wz[1]);
			clip(&wx[2], &wy[2], &wz[2], wx[3], wy[3], wz[3]);
		}
		if (wy[1] < 1) {
			clip(&wx[1], &wy[1], &wz[1], wx[0], wy[0], wz[0]);
			clip(&wx[3], &wy[3], &wz[3], wx[2], wy[2], wz[2]);
		}
		wx[0] = wx[0] * 200 / wy[0] + gfx.ScreenWidth; wy[0] = wz[0] * 200 / wy[0] + gfx.ScreenHeight;
		wx[1] = wx[1] * 200 / wy[1] + gfx.ScreenWidth; wy[1] = wz[1] * 200 / wy[1] + gfx.ScreenHeight;
		wx[2] = wx[2] * 200 / wy[2] + gfx.ScreenWidth; wy[2] = wz[2] * 200 / wy[2] + gfx.ScreenHeight;
		wx[3] = wx[3] * 200 / wy[3] + gfx.ScreenWidth; wy[3] = wz[3] * 200 / wy[3] + gfx.ScreenHeight;
		int xx1 = wx[0];
		int xx2 = wx[1];
		int b1 = wy[0];
		int b2 = wy[1];
		int t1 = wy[2];
		int t2 = wy[3];
		int xx, yy;
		int dyb = b2 - b1;
		int dyt = t2 - t1;
		int dx = xx2 - xx1;
		if (dx == 0) {
			dx = 1;
		}
		int xs = xx1;
		if (xx1 < 1) {
			xx1 = 1;
		}
		if (xx2 < 1) {
			xx2 = 1;
		}
		if (xx1 > gfx.ScreenWidth - 1) {
			xx1 = gfx.ScreenWidth - 1;
		}
		if (xx2 > gfx.ScreenWidth - 1) {
			xx2 = gfx.ScreenWidth - 1;
		}
		for (xx = xx1; xx < xx2; xx++) {
			int y1 = dyb * (xx - xs + 0.5) / dx + b1;
			int y2 = dyt * (xx - xs + 0.5) / dx + t1;
			if (y1 < 1) {
				y1 = 1;
			}
			if (y2 < 1) {
				y2 = 1;
			}
			if (y1 > gfx.ScreenHeight - 1) {
				y1 = gfx.ScreenHeight - 1;
			}
			if (y2 > gfx.ScreenHeight - 1) {
				y2 = gfx.ScreenHeight - 1;
			}
			if (S[s].surface == 1) {
				S[s].surf[xx] = y1; continue;
			}
			if (S[s].surface == 2) {
				S[s].surf[xx] = y2; continue;
			}
			if (S[s].surface == -1) {
				for (yy = S[s].surf[xx]; yy < y1; yy++) {
					gfx.PutPixel(xx, yy, S[s].r1, S[s].g1, S[s].b1);
				}
			}
			if (S[s].surface == -2) {
				for (yy = y2;yy<S[s].surf[xx]; yy++) {
					gfx.PutPixel(xx, yy, S[s].r2, S[s].g2, S[s].b2);
				}
			}
			for (yy = y1; yy < y2; yy++) {
				if (xx > 0 && xx < gfx.ScreenWidth && yy>0 && yy <= gfx.ScreenHeight) {
					gfx.PutPixel(xx, yy, W[w].r, W[w].g, W[w].b);
				}
			}
		}
	}
		S[s].d /= (S[s].we - S[s].ws);
		S[s].surface *= -1;
	}
	}
}
