// cl: /O1 /MD
//
// ?Rva00419BFAInit@@YAXXZ, retail 0x00419BFA, 105 bytes.
// Singleton init registering the game command group and the stringbuf IO
// factory, then issuing "debug.io stringbuf add". Evidence: vtable store
// 0x0083ABB8 for 4-byte cmd object kept in g_00E030C8, AddCommands at slot
// 0x84 with "game", AddIOFactory at slot 0x80 with "stringbuf" plus factory
// 0x00419BCD, Command at slot 0x8C, single caller 0x002301F1. The command
// and IO objects are local views, so both are cast to the canonical
// DebugCmdInterface / DebugIOInterface factory parameter types.
// ?Rva00419BCDCreate@@YAPAXXZ, retail 0x00419BCD, 45 bytes. Stringbuf IO
// singleton factory kept in g_00E030C4, 12-byte object with byte+4 and
// dword+8 zeroed.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include "debug.h"

extern Debug *theDebug;
extern void *g_00E030C4;
// The stringbuf singleton slot (VA 0x00E030C4) has only this unit's readers.
void *g_00E030C4;
// The command object slot (VA 0x00E030C8) is defined by its cleanup unit
// (Rva00419A99Cleanup.cpp) under that unit's element type.
class Rva00419A99Item;
extern Rva00419A99Item *g_00E030C8;

class Rva00419BCD_IO
{
public:
	virtual ~Rva00419BCD_IO() {}
	bool m_04;
	int m_08;
	// cl hoists an and-zero store to the front of an unfenced tail; retail keeps
	// the byte store before the dword zero, which the barrier reproduces.
	Rva00419BCD_IO() { m_04 = false; _ReadWriteBarrier(); m_08 = 0; }
};

class Rva00419BFA_Cmd
{
public:
	Rva00419BFA_Cmd();
	virtual ~Rva00419BFA_Cmd() {}
};
// ??0Rva00419BFA_Cmd@@QAE@XZ @0x00419B68 9B: the default constructor, storing the
// class's own vtable (VA 0x00C3ABB8) and returning this.
Rva00419BFA_Cmd::Rva00419BFA_Cmd()
{
}

void *__cdecl Rva00419BCDCreate()
{
	if (g_00E030C4)
		return g_00E030C4;
	Rva00419BCD_IO *p = new Rva00419BCD_IO;
	g_00E030C4 = p;
	return p;
}

void __cdecl Rva00419BFAInit()
{
	if (g_00E030C8)
		return;
	Rva00419BFA_Cmd *p = new Rva00419BFA_Cmd;
	g_00E030C8 = (Rva00419A99Item *)(void *)p;
	theDebug->AddCommands("game", reinterpret_cast<DebugCmdInterface *>(p));
	theDebug->AddIOFactory("stringbuf", "internal string buffer",
		reinterpret_cast<DebugIOInterface *(*)()>(Rva00419BCDCreate));
	theDebug->Command("debug.io stringbuf add");
}
