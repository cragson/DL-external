#include "dl_cheat.hpp"

#include "globals.hpp"
#include "utils.hpp"
#include "offsets.hpp"

#include "ft_godmode.hpp"
#include "ft_vendor.hpp"
#include "ft_stamina.hpp"
#include "ft_weapon.hpp"
#include "ft_throwables.hpp"

#include <print>

bool dl_cheat::setup_features()
{
	auto gm = std::make_unique< ft_godmode >();
	gm->set_name(L"Godmode");
	gm->disable_print_status();
	gm->set_activation_delay(420);
	gm->set_virtual_key_code(VK_NUMPAD1);

	auto vendor = std::make_unique< ft_vendor >();
	vendor->set_name(L"Free vendor");
	vendor->disable_print_status();
	vendor->set_activation_delay(420);
	vendor->set_virtual_key_code(VK_NUMPAD2);

	auto stam = std::make_unique< ft_stamina >();
	stam->set_name(L"Infinite stamina");
	stam->disable_print_status();
	stam->set_activation_delay(420);
	stam->set_virtual_key_code(VK_NUMPAD3);

	auto weap = std::make_unique< ft_weapon >();
	weap->set_name(L"Infinite weapon durability");
	weap->disable_print_status();
	weap->set_activation_delay(420);
	weap->set_virtual_key_code(VK_NUMPAD4);

	auto throwa = std::make_unique< ft_throwables >();
	throwa->set_name(L"Infinite throwables");
	throwa->disable_print_status();
	throwa->set_activation_delay(420);
	throwa->set_virtual_key_code(VK_NUMPAD5);

	
	this->m_features.push_back(std::move(gm));
	this->m_features.push_back(std::move(vendor));
	this->m_features.push_back(std::move(stam));
	this->m_features.push_back(std::move(weap));
	this->m_features.push_back(std::move(throwa));

	return true;
}

bool dl_cheat::setup_offsets()
{
	const auto gamedll = Globals::g_pProcess->get_image_ptr_by_name(L"gamedll_x64_rwdi.dll");

	if (!gamedll)
		return false;

	const auto gm = gamedll->find_pattern(L"F3 0F 5D C6 F3 0F 11 83 64 09 00 00", false);

	if (!gm)
	{
		std::println("[!] Could not find godmode offset in memory!");

		return false;
	}

	Offsets::godmode = gm;

	const auto vendor = gamedll->find_pattern(L"2B C7 89 41 40", false);

	if (!vendor)
	{
		std::println("[!] Could not find free vendor offset in memory!");

		return false;
	}

	Offsets::free_vendor = vendor;

	const auto stam = gamedll->find_pattern(L"F3 0F 11 7E 10 73", false);

	if (!stam)
	{
		std::println("[!] Could not find stamina offset in memory!");

		return false;
	}

	Offsets::stamina = stam;

	const auto durex = gamedll->find_pattern(L"F3 0F 5D C6 0F 28 F0 0F", false);

	if (!durex)
	{
		std::println("[!] Could not find weapon durability offset in memory!");

		return false;
	}

	Offsets::weapon_durability = durex;

	const auto wurfstern_hooyaaaa_ninja = gamedll->find_pattern(L"D8 89 1E 48 8B 5C 24 30", false);

	if (!wurfstern_hooyaaaa_ninja)
	{
		std::println("[!] Could not find throwables offset in memory!");

		return false;
	}

	Offsets::throwables = wurfstern_hooyaaaa_ninja;

	return true;
}

void dl_cheat::print_features()
{
	printf("\n");

	printf("Feature-Name -> Feature-Hotkey\n");

	for (const auto& feature : this->m_features)
		printf(
			"[>] %-25ws -> %s\n",
			feature->get_name().c_str(),
			utils::virtual_key_as_string(feature->get_virtual_key_code()).c_str()
		);

	printf("\n");
}

void dl_cheat::print_offsets()
{
	printf("\n");

	const auto msg = [](const std::string& name, const std::uintptr_t value)
		{
			printf("[>] %-35s -> 0x%llX\n", name.c_str(), value);
		};

	msg("Godmode", Offsets::godmode);
	msg("Free vendor", Offsets::free_vendor);
	msg("Infinite stamina", Offsets::stamina);
	msg("Infinite weapon durability", Offsets::weapon_durability);
	msg("Infinite throwables", Offsets::throwables);

	printf("\n");
}

void dl_cheat::run()
{
	for (const auto& feature : this->m_features)
	{
		// before tick'ing the feature, check first if the state will eventually change
		if (GetAsyncKeyState(feature->get_virtual_key_code()) & 0x8000)
			feature->toggle();

		// let the feature tick() when active
		if (feature->is_active())
			feature->tick();
	}
}

void dl_cheat::shutdown()
{
	// disable every feature here
	for (const auto& feature : this->m_features)
		if (feature->is_active())
			feature->disable();

	// clear image map here
	if (Globals::g_pProcess)
		Globals::g_pProcess->clear_image_map();
}