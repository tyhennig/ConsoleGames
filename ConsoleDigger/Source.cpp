#include <iostream>
#include "olcConsoleGameEngine.h"

using namespace std;

//Some Comments to add about the game and how it runs.

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
	float speed;
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
		player.y = ScreenHeight() / 2;


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

		
		if (m_keys[VK_UP].bReleased)
			player.bJumped = true;
		if (m_keys[VK_DOWN].bHeld)
		{
			if (aWorld[(((int)player.y) * ScreenWidth() + (int)player.x)].type == SKY)
			{
				player.y += player.speed * fElapsedTime;

			}
		}
		if (m_keys[VK_LEFT].bHeld)
			player.x -= player.speed * fElapsedTime;
		if (m_keys[VK_RIGHT].bHeld)
			player.x += player.speed * fElapsedTime;

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
		Fill(player.x - 1, player.y - 2, player.x + 1, player.y, PIXEL_SOLID, FG_GREY);



		return true;
	}

};


int main()
{
	ConsoleDigger game;
	game.ConstructConsole(180, 100, 8, 8);
	game.Start();
}