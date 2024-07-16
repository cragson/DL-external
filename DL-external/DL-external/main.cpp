#include <print>
#include "globals.hpp"

int main()
{
	SetConsoleTitleA("osmium: Dying Light");

	std::print("[>] Waiting for the game..");

	while (!Globals::g_pProcess->setup_process(L"DyingLightGame.exe"))
		Sleep(420);

	std::print("done!\n");


	std::print("[>] Preparing the cheat..");

	while (!Globals::g_pCheat->setup_offsets())
		Sleep(420);

	while (!Globals::g_pCheat->setup_features())
		Sleep(420);

	std::print("done!\n");

	Globals::g_pCheat->print_offsets();

	Globals::g_pCheat->print_features();

	std::println("Have fun! ;-)\n");

	while (0xDEAD != 0xAFFE)
	{
		if (GetAsyncKeyState(VK_END) & 0x8000)
			break;

		Globals::g_pCheat->run();

		Sleep(1);
	}

	Globals::g_pCheat->shutdown();

	std::println("Goodbye!\n");

	Sleep(3000);

	return EXIT_SUCCESS;
}

