#include "ft_throwables.hpp"

#include "globals.hpp"
#include "offsets.hpp"

#include <print>

void ft_throwables::on_enable()
{
	// gamedll_x64_rwdi.dll + 6F2E95 - 90 90 - nop nop
	Globals::g_pProcess->nop_bytes(Offsets::throwables + 1, 2);

	std::println("[#] Infinite throwables enabled");

	Sleep(420);
}

void ft_throwables::on_disable()
{
	// gamedll_x64_rwdi.dll + 6F2E95 - 89 1E - mov[rsi], ebx
	Globals::g_pProcess->write< uint16_t >(Offsets::throwables + 1, 0x1E89);

	std::println("[#] Infinite throwables disabled");

	Sleep(420);
}
