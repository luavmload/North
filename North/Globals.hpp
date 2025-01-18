#pragma once

#define REBASE(adress) (uintptr_t)GetModuleHandleA(0) + adress

#include <cstdint> // uintptr_t

static uintptr_t max_capabilities = 0x3FFFF00 | 0xFFFFFFFFCFFui64;

namespace Offsets
{
	const uintptr_t print			= REBASE(0x13CDA30);
	const uintptr_t luavm_load		= REBASE(0xB37E80);
	const uintptr_t task_defer		= REBASE(0xF0C9A0);
	const uintptr_t get_scheduler	= REBASE(0x2D7B7A0);
};

namespace TypeDefs
{
	using print_t = DWORD64 (__cdecl*)(unsigned int type, const char* message);
	using luavm_load_t = DWORD64 (__cdecl*)(uintptr_t state, std::string* source, const char* chunk, int environment);
	using task_defer_t = int (__cdecl*)(uintptr_t state);
	using get_scheduler_t = uintptr_t(__cdecl*)();
};

namespace Functions
{
	TypeDefs::print_t print = reinterpret_cast<TypeDefs::print_t>(Offsets::print);
	TypeDefs::luavm_load_t luavm_load = reinterpret_cast<TypeDefs::luavm_load_t>(Offsets::luavm_load);
	TypeDefs::task_defer_t task_defer = reinterpret_cast<TypeDefs::task_defer_t>(Offsets::task_defer);
	TypeDefs::get_scheduler_t get_scheduler = reinterpret_cast<TypeDefs::get_scheduler_t>(Offsets::get_scheduler);
}
