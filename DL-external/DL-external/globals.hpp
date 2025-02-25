#pragma once
#include "osmium/Memory/Process/process.hpp"

#include "dl_cheat.hpp"

namespace Globals
{
	inline auto g_pProcess = std::make_unique< process >();

	inline auto g_pCheat = std::make_unique< dl_cheat >();
}