#include "Engine.h"
AppStates appStates;

int main()
{
	fclose(stdin);
	fclose(stdout);
	fclose(stderr);
	FreeConsole();
	Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT, "Battle Ship");
	return EXIT_SUCCESS;
}