// cl: /Ireference/shims/bfme2_ascii /MD /EHs
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

enum ObjectStatusTypes
{
	STATUS_0 = 0,
	STATUS_1 = 1,
	STATUS_2 = 2
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes s) const;
	Object *getNextObject() { return m_next; }
	char m_pad00[4];
	void *m_04;
	char m_pad08[0x6C];
	int m_74;
	char m_pad78[0x14];
	Object *m_next; // +0x8C
	char m_pad90[0x1F0];
	float m_280;
};

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;
// The rowed initializer at 7B31DF constructs "FarmTemplate" in this
// four-byte storage; its existing owner keeps the global address unique.
extern unsigned g_Va00E04490;

int __cdecl Rva004EA2C5Get()
{
	int count = 0;
	for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject()) {
		Rva004EA2C5Template *holder = (Rva004EA2C5Template *)obj->m_04;
		if (holder->m_name.compare(*(const StringBase<char> *)&g_Va00E04490) == 0)
			++count;
	}
	return count;
}
