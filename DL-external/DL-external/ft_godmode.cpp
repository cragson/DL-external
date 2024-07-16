#include "ft_godmode.hpp"

#include "globals.hpp"
#include "offsets.hpp"

#include <print>

void ft_godmode::on_enable()
{
	// gamedll_x64_rwdi.dll + BAE6D0 - F3 0F 5F C6 - maxss xmm0,xmm6
	Globals::g_pProcess->write< uint8_t >(Offsets::godmode + 2, 0x5F);

	std::println("[#] Godmode enabled");

	Sleep(420);
}

void ft_godmode::on_disable()
{
	// gamedll_x64_rwdi.dll + BAE6D0 - F3 0F 5D C6 - minss xmm0,xmm6
	Globals::g_pProcess->write< uint8_t >(Offsets::godmode + 2, 0x5D);
	
	std::println("[#] Godmode disabled");

	Sleep(420);
}
