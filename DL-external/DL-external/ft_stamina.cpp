#include "ft_stamina.hpp"

#include "globals.hpp"
#include "offsets.hpp"

#include <print>

void ft_stamina::on_enable()
{
	// gamedll_x64_rwdi.dll + CF0053 - F3 0F 11 56 10 - movss [rsi+10],xmm2
	Globals::g_pProcess->write< uint8_t >(Offsets::stamina + 3, 0x56);

	std::println("[#] Infinite stamina enabled");

	Sleep(420);
}

void ft_stamina::on_disable()
{
	// gamedll_x64_rwdi.dll + CF0053 - F3 0F 11 7E 10 - movss [rsi+10],xmm7
	Globals::g_pProcess->write< uint8_t >(Offsets::stamina + 3, 0x7E);

	std::println("[#] Infinite stamina disabled");

	Sleep(420);
}
