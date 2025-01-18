#include "North.hpp"

void North::Initialize()
{
	Functions::print(1, "North Has Been Injected");
}

void North::setCapabilites(Proto* proto, uintptr_t* flags)
{
	if (!proto)
		return;

	proto->userdata = flags;
	for (int i = 0; i < proto->sizep; i++)
		setCapabilites(proto->p[i], flags);
}

int North::Execute(uintptr_t state, std::string source)
{
	static CBytecodeEncoder encoder = CBytecodeEncoder();
	std::string bytecode = Luau::compile(source, { 2, 1, 1 }, {}, &encoder); // Compile to bytecode
	if (bytecode.at(0) == 0)
	{
		std::cerr << "Could not compile bytecode" << std::endl;
		return ERROR;
	}

	std::string compressed = Utils::CompressBytecode(source);

	lua_State* threadState = lua_newthread((lua_State*)state);
	if (Functions::luavm_load((uintptr_t)threadState, &compressed, "@Spooky", 0) != 0)
	{
		std::cerr << "Could not load bytecode" << std::endl;
		return ERROR;
	}
	else
	{
		// Set capabilities here

		Functions::task_defer((uintptr_t)threadState);
		lua_pop(threadState, 1);
	}

	return 1;
}