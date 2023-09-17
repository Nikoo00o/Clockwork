#pragma once
#include "src\Core\Engine.h"

namespace clockwork {

class ExampleGame
	: public Engine
{

private:

public:
	ExampleGame() noexcept;
	virtual ~ExampleGame() noexcept;

public:
	virtual void start() noexcept;

public:

};

}