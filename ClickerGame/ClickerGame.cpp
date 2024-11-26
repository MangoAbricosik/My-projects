#include <iostream>

#include "ClickerGameClass.h"

#pragma warning( disable : 4996) // for test

int main()
{
	freopen("input.txt", "r", stdin); // for test

	ClickerGame game;
	game.Start();

	return 0;
}

