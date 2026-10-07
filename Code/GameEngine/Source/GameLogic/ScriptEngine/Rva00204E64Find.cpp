// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// ?Rva00204E64Find@@YGPAVScriptList@@ABVAsciiString@@@Z @0x00204E64 87B: free
// function mapping a side name to its ScriptList: key via TheNameKeyGenerator,
// scan players for a matching +0x50 key, return &getSideInfo(i)->m_scriptList
// or NULL. Evidence: rowed nameToKey 0x0009FA65, rowed getNthPlayer 0x002A7A29,
// rowed getSideInfo 0x002035BA; unblocks 0x0020C140 0x00204F3B 0x0020C3BB.

enum NameKeyType
{
	NK_INVALID = 0
};

#include "ascii_string.h"

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Player
{
public:
	char m_pad[0x50];
	NameKeyType m_nameKey; // +0x50
};

class PlayerList
{
public:
	Player *getNthPlayer(int i);
};

extern PlayerList *ThePlayerList;

class ScriptList
{
	char m_body[0x4C];
};

class SidesInfo
{
public:
	char m_pad[8];
	ScriptList m_scriptList; // +0x08
};

class SidesList
{
public:
	SidesInfo *getSideInfo(int i);
	char m_pad[0x3C];
	int m_numSides; // +0x3C
};

extern SidesList *TheSidesList;
// TheSidesList: matched references place it at VA 0xe01d58 (zero-filled .bss).
SidesList * TheSidesList;

ScriptList * __stdcall Rva00204E64Find(const AsciiString &name)
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	for (int i = 0; i < TheSidesList->m_numSides; i++) {
		Player *player = ThePlayerList->getNthPlayer(i);
		if (player != 0 && player->m_nameKey == key)
			return &TheSidesList->getSideInfo(i)->m_scriptList;
	}
	return 0;
}
