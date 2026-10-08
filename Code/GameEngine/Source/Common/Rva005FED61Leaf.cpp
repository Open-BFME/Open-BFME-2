// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?rva005FED61@Rva005FED61@@QAEXPBVAsciiString@@H@Z @0x005FED61 56B
// Leaf thiscall (AsciiString key, int delta): looks the key up through
// g_009FF000 slot rva002D06CA, reads index at payload+0x5C4, keeps 0-6
// (drops <0, ==7 and >=8) and adds delta into this+4[idx]. Evidence: rowed
// rva002D06CA 0x002D06CA plus global g_009FF000, neighbours Rva005FED59 and
// Disp8 getters in same dir, caller 0x005FEDA7, ret 8 two-arg shape.
#include "ascii_string.h"
#include "BattlePromptCounterView.h"

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

struct Rva005FED61Payload
{
	char m_pad00[0x5C4];
	int m_idx5C4;
};

void Rva005FED61::rva005FED61(const AsciiString *key, int delta)
{
	void *raw = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(key);
	if (raw == 0)
		return;
	int idx = ((Rva005FED61Payload *)raw)->m_idx5C4;
	if (idx < 0 || idx == 7 || idx >= 8)
		return;
	m_counts04[idx] += delta;
}
