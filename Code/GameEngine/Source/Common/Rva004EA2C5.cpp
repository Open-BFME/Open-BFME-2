// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHs
// ?Rva004EA2C5Get@@YAHXZ @0x004EA2C5 55B
// Counts world objects whose template name matches global g_00E04490.
// Evidence: leaf packet walks GameLogic list head +0xAC next +0x8C via rowed
// getFirstObject 0x0023CAD2 and rowed StringBase compare 0x000069D6 with
// holder +0x4 name +0x64; TheGameLogic extern in use.
#include "ascii_string.h"

class Rva004EA2C5Template
{
public:
	char m_pad[0x64];
	StringBase<char> m_name; // +0x64
};

class Object
{
public:
	Object *getNextObject() { return m_next; }

public:
	void *m_unk00; // +0x00
	Rva004EA2C5Template *m_holder; // +0x04
	char m_pad08[0x8C - 8];
	Object *m_next; // +0x8C
};

class GameLogic
{
public:
	Object *getFirstObject();
private:
	unsigned char m_pad[0xAC];
	Object *m_first; // +0xAC
};

extern GameLogic *TheGameLogic;
extern const StringBase<char> g_00E04490;

int __cdecl Rva004EA2C5Get()
{
	int count = 0;
	for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject()) {
		Rva004EA2C5Template *holder = obj->m_holder;
		if (holder->m_name.compare(g_00E04490) == 0)
			++count;
	}
	return count;
}
