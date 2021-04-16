#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Teste.h"
#include "Console.h"

int main() {
	{
		run_teste();
		ui();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
