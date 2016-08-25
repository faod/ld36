#include <game/Game.h>

int main(int argc, char *argv[])
{
	(void) argc, (void) argv;

	faod::Game g("ludum", 800, 600);
	g.run();

	return 0;
}
