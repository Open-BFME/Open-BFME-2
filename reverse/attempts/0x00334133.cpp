// ?run@Rva00334133Owner@@QAE?AVAsciiString@@PBDKPAURva00334133Context@@@Z
// partial score=0.93 date=2026-10-10
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7
//
// Retail 0x00334133, 223 bytes through the `ret 0x10` at +0xDC, including the
// catch(...) funclet at +0x9A (it returns the continuation 0x003341D3, the
// 6-byte Catch@007341cd that Ghidra rowed apart). It runs a Lua buffer on the
// state at +0x10 with the context parked at +0x9C, naming the chunk after the
// context's source template (name text at +0x64), and returns the first stack
// result as a string. Body: Open-BFME-1 Rva002E4470LuaBufferRun.cpp (retail
// 0x002E4470 there, donor revision 575ba2b04); BFME 2 differs in the owner
// offsets and in reading the template without the final-override walk. Names
// stay address-derived: the caller is unnamed.
#include <string.h>
#include "ascii_string.h"

struct lua_State;

extern "C"
{
	void __cdecl lua_settop( lua_State *L, int idx );
	int __cdecl lua_dobuffer( lua_State *L, const char *buff, unsigned long size, const char *name );
	int __cdecl lua_gettop( lua_State *L );
	const char *__cdecl lua_tostring( lua_State *L, int idx );
}

struct Rva00334133Template
{
	char m_unmodelled00[ 0x64 ];
	const char *m_nameText;
};

struct Rva00334133Source
{
	char m_unmodelled00[ 4 ];
	Rva00334133Template *m_template;
};

struct Rva00334133Context
{
	char m_unmodelled00[ 0xC ];
	Rva00334133Source *m_source;
};

class Rva00334133Owner
{
public:
	AsciiString run( const char *buffer, unsigned long size, Rva00334133Context *context );
private:
	char m_unmodelled00[ 0x10 ];
	lua_State *m_L;
	char m_unmodelled14[ 0x88 ];
	Rva00334133Context *m_context9C;
};

AsciiString Rva00334133Owner::run( const char *buffer, unsigned long size, Rva00334133Context *context )
{
	m_context9C = context;
	AsciiString result;
	try
	{
		lua_settop( m_L, 0 );
		const char *name = context->m_source->m_template->m_nameText;
		int status = lua_dobuffer( m_L, buffer, size, name ? name + 8 : "" );
		if( status == 0 && lua_gettop( m_L ) > 0 )
		{
			const char *text = lua_tostring( m_L, 1 );
			( (StringBase<char> *)&result )->set( text );
		}
		lua_settop( m_L, 0 );
	}
	catch( ... )
	{
	}
	m_context9C = 0;
	return result;
}
