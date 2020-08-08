#include <iostream>
#include <vector>
#include "olcConsoleGameEngine.h"

using namespace std;

struct sControlPoints
{
	float x;
	float y;

};

struct sPoint
{
	int x;
	int y;
};

class ConsoleSpline : public olcConsoleGameEngine
{
public:

	ConsoleSpline()
	{

	}

	sPoint getSplinePoint(float t)
	{
		int p0, p1, p2, p3;

		p1 = floor(t) + 1;
		p0 = p1 - 1;
		p2 = p1 + 1;
		p3 = p1 + 2;

		float tt = t * t;
		float ttt = tt * t;

		float q1 = -ttt + 2.0f * tt - t;
		float q2 = 3.0f * ttt - 5.0f * tt + 2.0f;
		float q3 = -3.0f * ttt + 4.0f * tt + t;
		float q4 = ttt - tt;

		
		float tx = 0.5f*( vControlPoints[p0].x * q1 + vControlPoints[p1].x * q2 + vControlPoints[p2].x * q3 + vControlPoints[p3].x * q4);
		float ty = 0.5f*(vControlPoints[p0].y * q1 + vControlPoints[p1].y * q2 + vControlPoints[p2].y * q3 + vControlPoints[p3].y * q4);



		sPoint p = { tx, ty };

		return p;
	}

private:
	vector<sControlPoints> vControlPoints;
	vector<sPoint> points;
	

protected:

	virtual bool OnUserCreate()
	{
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ', PIXEL_SOLID);

		sControlPoints a;
		sControlPoints b;
		sControlPoints c;
		sControlPoints d;

		a.x = 10;
		a.y = 30;

		b.x = ScreenWidth() / 2;
		b.y = ScreenHeight() / 2 - 20;

		c.x = ScreenWidth() / 2;
		c.y = ScreenHeight() / 2 + 20;

		d.x = 40;
		d.y = 50;

		vControlPoints = { a, b, c, d };

		return true;

	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);



		if (m_keys[VK_DOWN].bHeld)
			vControlPoints[0].y += 30.0f * fElapsedTime;
		if (m_keys[VK_UP].bHeld)
			vControlPoints[0].y -= 30.0f * fElapsedTime;
		if (m_keys[VK_LEFT].bHeld)
			vControlPoints[0].x -= 30.0f * fElapsedTime;
		if (m_keys[VK_RIGHT].bHeld)
			vControlPoints[0].x += 30.0f * fElapsedTime;

		if (m_keys[L'S'].bHeld)
			vControlPoints[3].y += 30.0f * fElapsedTime;
		if (m_keys[L'W'].bHeld)
			vControlPoints[3].y -= 30.0f * fElapsedTime;
		if (m_keys[L'A'].bHeld)
			vControlPoints[3].x -= 30.0f * fElapsedTime;
		if (m_keys[L'D'].bHeld)
			vControlPoints[3].x += 30.0f * fElapsedTime;


		//Draw Spline
		for (float t = 0.0f; t < 1.0f; t += 0.02f)
		{
			sPoint p = getSplinePoint(t);
			Draw(p.x, p.y);
		}


		for (int i = 0; i < vControlPoints.size(); i++)
			Draw(vControlPoints[i].x, vControlPoints[i].y, PIXEL_SOLID, FG_RED);


		
		return true;
	}
};


int main()
{
	ConsoleSpline game;

	game.ConstructConsole(280, 180, 5, 5);
	game.Start();
}