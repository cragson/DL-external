#include "ft_weapon.hpp"

#include "globals.hpp"
#include "offsets.hpp"

#include <print>

void ft_weapon::on_enable()
{
	// gamedll_x64_rwdi.dll + 6F34E9 - F3 0F 5F C6 - maxss xmm0,xmm6
	Globals::g_pProcess->write< uint8_t >(Offsets::weapon_durability + 2, 0x5F);

	std::println("[#] Infinite weapon durability enabled");

	Sleep(420);
}

void ft_weapon::on_disable()
{
	// gamedll_x64_rwdi.dll + 6F34E9 - F3 0F 5D C6 - minss xmm0,xmm6
	Globals::g_pProcess->write< uint8_t >(Offsets::weapon_durability + 2, 0x5D);

	std::println("[#] Infinite weapon durability disabled");

	Sleep(420);
}
