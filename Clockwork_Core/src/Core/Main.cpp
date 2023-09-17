#include "src\Core\ExampleGame.h"

#include "src/Utils/ThreadPool.h"


int main()
{
	clockwork::engine = new clockwork::Engine("Clockwork-Engine");
	clockwork::engine->start();
	delete clockwork::engine;

	//clockwork::utils::test3();

	system("pause");
	return 1;
}