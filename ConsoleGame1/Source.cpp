#include <iostream>
//#include "olcConsoleGameEngine.h"
#include "../olcConsoleGameEngineGL.h"

using namespace std;


class Example : public olcConsoleGameEngine
{
public:

	Example()
	{

	}

private:
	int nPixelSize = 10;
	int nPixelX;
	int nPixelY;
	float fPlayerX = 0;
	float fPlayerY = 0;
	float fNewPlayerX = 0;
	float fNewPlayerY = 0;
	float fSpeed = 30.0f;

	string	map;

			

protected:

	virtual bool OnUserCreate()
	{
		map.append("............");
		map.append("............");
		map.append(".......o....");
		map.append("......o.o...");
		map.append(".....o...o..");
		map.append("..ooo.......");
		map.append("............");
		map.append("............");

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		//Clear Screen
		Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', 0);
		
		fNewPlayerX = fPlayerX;
		fNewPlayerY = fPlayerY;

		//Get Keyboard input

		if (m_keys[VK_UP].bHeld)
			fNewPlayerY -= fSpeed * fElapsedTime;
		if (m_keys[VK_DOWN].bHeld)
			fNewPlayerY += fSpeed * fElapsedTime;
		if (m_keys[VK_RIGHT].bHeld)
			fNewPlayerX += fSpeed * fElapsedTime;
		if (m_keys[VK_LEFT].bHeld)
			fNewPlayerX -= fSpeed * fElapsedTime;

		//Collision!

		
		if (fNewPlayerX > ScreenWidth())
			fPlayerX = ScreenWidth();
		if (fNewPlayerX < 0)
			fPlayerX = 0;
		if (fNewPlayerY > ScreenHeight())
			fPlayerY = ScreenHeight();
		if (fNewPlayerY < 0)
			fPlayerY = 0;

		
		
		//Draw Screen
		for (int i = 0; i < ScreenWidth() / nPixelSize * ScreenHeight() / nPixelSize; i++)
		{
			if(map[i] == 'o')
				Fill()
		}

		//Draw Player
		Fill((int)fPlayerX, (int)fPlayerY, (int)fPlayerX + nPixelSize, (int)fPlayerY + nPixelSize);

		return true;
	}
};



int main() {

	Example demo;
	demo.ConstructConsole(120, 80, 8, 8);
	demo.Start();

}
