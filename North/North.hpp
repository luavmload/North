#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <iostream>
#include <string>

//#include <zstd.h>

#include "Luau/Compiler/include/Luau/Compiler.h"
#include "Luau/Compiler/include/Luau/BytecodeBuilder.h"

#include "Luau/Common/include/Luau/BytecodeUtils.h"

#include "Luau/VM/include/lua.h"

#include "Luau/VM/src/lobject.h"

#include "Globals.hpp"
#include "Utils.hpp"

struct North
{
public:
	static void Initialize();
	static int Execute(uintptr_t state, std::string source);
private:
	static void setCapabilites(Proto* proto, uintptr_t* flags);

	class CBytecodeEncoder : public Luau::BytecodeEncoder
	{
		inline void encode(uint32_t* data, size_t count) override
		{
			for (unsigned int i = 0u; i < count;)
			{
				uint8_t& opcode = *(uint8_t*)(data + i);
				i += Luau::getOpLength(LuauOpcode(opcode));

				opcode *= 227;
			}
		}
	};

};

