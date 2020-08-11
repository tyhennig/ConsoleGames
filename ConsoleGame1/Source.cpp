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

	virtual bool OnUserCreate()
	{
		

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		//Clear Screen
		Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', 0);



		
		//Draw Screen
		for (int i = 0; i < ScreenWidth() / nPixelSize * ScreenHeight() / nPixelSize; i++)
		{
			int x = i % (ScreenWidth() / nPixelSize);
			int y = i / (ScreenWidth() / nPixelSize);

			if ((i % ((ScreenWidth() / nPixelSize)) == y))
			{
				
				Fill(x * 10, y * 10, x * 10 + 10, y * 10 + 10, PIXEL_SOLID, FG_CYAN);
			}
		}

		return true;
	}

private:
	int nPixelSize = 10;
	int nPixelX;
	int nPixelY;


	
};



int main() {

	Example demo;
	demo.ConstructConsole(120, 80, 8, 8);
	demo.Start();

}
