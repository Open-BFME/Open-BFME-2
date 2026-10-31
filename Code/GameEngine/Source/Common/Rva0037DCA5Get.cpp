// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?GetCommandPointSize@Rva0037DCA5@@QAEHXZ, retail 0x0037DCA5 (39B).
// Lookup via TheThingFactory global 0x00DFF000 plus AsciiString at +0x4 through
// rowed 0x002D06CA. Returns 0 when lookup misses else template dword at +0x618
// times int at +0x90. Sibling of rowed 0x0037E270 (same global and callee via
// Rva0037E270Lookup.cpp) and unclaimed 0x0037DC52 (same +0x4 lookup shape).
// Callers at 0x002B369C 0x002B36A5 0x002B6C58 0x0031906A 0x0040CFAC.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"
class ThingTemplate;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &key);
};
extern class ThingFactory *TheThingFactory;
struct Rva0037DCA5Template
{
	char m_pad[0x618];
	int m_cost;
};
class Rva0037DCA5
{
	char m_pad0[4];
	AsciiString m_name;
	char m_pad8[0x90 - 8];
	int m_count;
public:
	int GetCommandPointSize();
	void *GetThingTemplate();
	void *GetDisplayNameStrategicGame();
	void *GetDisplayNameStrategicGame(int v);
};
#include "unicode_string.h"
class Rva002E2903Player;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int v, unsigned int *x);
};

class LivingWorldPlayer
{
public:
	void *rva002E06EF();
};
// ?GetThingTemplate@Rva0037DCA5@@QAEPAXXZ @0x0037DC52 16B same +0x4 lookup via 0x002D06CA and global 0x00DFF000.
void *Rva0037DCA5::GetThingTemplate()
{
	return (void *)TheThingFactory->findTemplate(m_name);
}
// ?GetDisplayNameStrategicGame@Rva0037DCA5@@QAEPAXXZ @0x0040C64A 19B chain of GetThingTemplate.
// Returns empty wide sentinel 0x00E0C898 when lookup misses else template+0x58.
// Caller at 0x00220BA7 passes this plus pushes return for wide copy.
void *Rva0037DCA5::GetDisplayNameStrategicGame()
{
	void *found = GetThingTemplate();
	if (found == 0)
		return (void *)&UnicodeString::TheEmptyString;
	return (char *)found + 0x58;
}

void *Rva0037DCA5::GetDisplayNameStrategicGame(int v)
{
	void *found = GetThingTemplate();
	if (found == 0)
		return (void *)&UnicodeString::TheEmptyString;
	if ((((unsigned char *)found)[0x11F] & 0x40) == 0)
		return (char *)found + 0x58;
	Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(v, 0);
	if (player == 0)
		return (char *)found + 0x58;
	void *inner = ((LivingWorldPlayer *)player)->rva002E06EF();
	if (inner == 0)
		return (char *)found + 0x58;
	return (char *)inner + 8;
}
