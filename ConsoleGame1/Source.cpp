#include <iostream>

#include "olcConsoleGameEngine.h"

using namespace std;


class Example : public olcConsoleGameEngine
{
public:


	


	Example()
	{
	}

	virtual bool OnUserCreate()
	{
		block_x = 10.0f;
		block_y = 10.0f;
		right = true;
		down = true;
		fire = false;
		speed = 15.0f;
		currentColor = FG_CYAN;


		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		Fill(0, 0, m_nScreenWidth, m_nScreenHeight, L' ', 0);

		if (right == true && down == true)
			currentColor = FG_RED;
		if (right == true && down == false)
			currentColor = FG_GREEN;
		if (right == false && down == true)
			currentColor = FG_YELLOW;
		if (right == false && down == false)
			currentColor = FG_BLUE;

		if (m_keys[VK_SPACE].bHeld && fire == false) {
			fire = true;
			bullet_x = block_x + 5;
			bullet_y = block_y + 2;
		}

		

		if (m_keys[VK_LEFT].bHeld)
			block_x -= speed * fElapsedTime;
		if (m_keys[VK_RIGHT].bHeld)
			block_x += speed * fElapsedTime;
		if (m_keys[VK_UP].bHeld)
			block_y -= speed * fElapsedTime;
		if (m_keys[VK_DOWN].bHeld)
			block_y += speed * fElapsedTime;



		Fill((int)block_x, (int)block_y, (int)block_x + 5, (int)block_y + 5, PIXEL_SOLID, currentColor);
		if (fire == true) {
			Fill((int)bullet_x, (int)bullet_y, (int)bullet_x + 1, (int)bullet_y + 1, PIXEL_SOLID, FG_WHITE);
			bullet_x += 60.0f * fElapsedTime;

		}
		
		if (bullet_x < 0 || bullet_x > m_nScreenWidth || bullet_y > m_nScreenHeight || bullet_y < 0)
			fire = false;
		
		if (block_x + 5 >= m_nScreenWidth) {
			right = false;
		}
		if (block_y + 5 >= m_nScreenHeight) {
			down = false;
		}

		if (block_x <= 0) {
			right = true;
		}
		if (block_y <= 0) {
			down = true;
		}
		

		return true;
	}

private:
	float block_x;
	float block_y;
	float bullet_x;
	float bullet_y;
	float speed;
	bool right;
	bool down;
	bool fire;
	COLOUR currentColor;
};



int main() {

	Example demo;
	demo.ConstructConsole(120, 80, 8, 8);
	demo.Start();

}
