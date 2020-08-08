#include <iostream>
#include "olcConsoleGameEngineGL.h"

using namespace std;

//Some Comments to add about the game and how it runs.
//Comment made on laptop

struct Block
{
	int x;
	int y;
	int type;
};

struct Player
{
	float x;
	float y;
	float newX;
	float newY;
	float speed;
	float fVelX;
	float fVelY;
	bool bJumped = false;
};

enum BLOCKTYPE
{
	
	DIRT	= 1,
	SKY		= 2,

};

class ConsoleDigger : public olcConsoleGameEngine
{
public:
	ConsoleDigger()
	{

	};

private:
	Block* aWorld;
	Player player;
	float fJumpTime = 0.0f;


protected:

	virtual bool OnUserCreate()
	{
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		player.speed = 30.0f;
		player.x = ScreenWidth() / 2;
		player.y = ScreenHeight() / 2 - 1;


		//Create World array of block types
		aWorld = new Block[ScreenWidth() * ScreenHeight()];

		for (int i = 0; i < ScreenWidth() * ScreenHeight(); i++)
		{
			//arrayPos = y * ScreenWidth() + x

			//i = y * WIDTH + x

			aWorld[i].x = i % ScreenWidth();
			aWorld[i].y = (i - aWorld[i].x) / ScreenWidth();

			if (i < ScreenWidth() * ScreenHeight() / 2)
			{

				aWorld[i].type = SKY;
				
			}
			else
			{
				aWorld[i].type = DIRT;
			}
		}


		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{

		player.fVelX = 0.0f;
		player.fVelY = 0.0f;
		player.newX = player.x;
		player.newY = player.y;
		
		if (m_keys[VK_UP].bHeld)
			player.fVelY = -10.0f;
		if (m_keys[VK_DOWN].bHeld)
		{
			player.fVelY = 10.0f;
		}
		if (m_keys[VK_LEFT].bHeld)
			player.fVelX = -10.0f;
		if (m_keys[VK_RIGHT].bHeld)
			player.fVelX = 10.0f;
		if (GetKey(VK_SPACE).bHeld)
		{
			if (aWorld[((int)player.y + 1) * ScreenWidth() + (int)player.x - 1].type == DIRT || aWorld[((int)player.y + 1) * ScreenWidth() + (int)player.x].type == DIRT)
			{
				aWorld[((int)player.y + 1) * ScreenWidth() + (int)player.x].type = SKY;
				aWorld[((int)player.y + 1) * ScreenWidth() + (int)player.x - 1].type = SKY;
			}
		}
		player.newX += player.fVelX * fElapsedTime;
		player.newY += player.fVelY * fElapsedTime;

		//Collision
		
		



		//Draw World
		for (int i = 0; i < ScreenWidth() * ScreenHeight(); i++)
		{
			//i = y * WIDTH + x SO ->>> y = (i - x) / WIDTH

			if (aWorld[i].type == SKY)
			{
				Draw(aWorld[i].x, aWorld[i].y, PIXEL_SOLID, FG_BLUE);
			}
			else
			{
				Draw(aWorld[i].x, aWorld[i].y, PIXEL_SOLID, FG_DARK_GREEN);
			}
		}

		


		//Draw Player
		if (player.x < 0)
			player.x = 0;
		if (player.x > ScreenWidth())
			player.x = ScreenWidth();
		if (player.y < 0)
			player.y = 0;
		if (player.y > ScreenHeight())
			player.y = ScreenHeight();

		

		Fill(player.x - 1, player.y - 2, player.x + 1, player.y+1, PIXEL_SOLID, FG_GREY);



		return true;
	}

};


int main()
{
	ConsoleDigger game;
	game.ConstructConsole(160, 80, 8, 8);
	game.Start();
}