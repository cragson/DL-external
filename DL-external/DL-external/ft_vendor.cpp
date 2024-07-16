#include "ft_vendor.hpp"

#include "globals.hpp"
#include "offsets.hpp"

#include <print>

void ft_vendor::on_enable()
{
	// gamedll_x64_rwdi.dll + CD2F0D - 01 F8 - add eax,edi
	Globals::g_pProcess->write< uint16_t >(Offsets::free_vendor, 0xF801);

	std::println("[#] Free vendor enabled");

	Sleep(420);
}

void ft_vendor::on_disable()
{
	// gamedll_x64_rwdi.dll + CD2F0D - 2B C7 - sub eax,edi
	Globals::g_pProcess->write< uint16_t >(Offsets::free_vendor, 0xC72B);

	std::println("[#] Free vendor disabled");

	Sleep(420);
}
