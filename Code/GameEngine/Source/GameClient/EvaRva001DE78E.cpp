// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva001DE78E@Eva@@QAEHPBVAsciiString@@@Z @0x001DE78E 39B: Eva event id lookup via rowed Rva00056F61 table at +0x34.
// Donor shape from Code/GameEngine/Source/GameClient/Rva0021311FGet.cpp (iterator find 0x0041534B in embedded table returning node+8).
// Callers at 0x001DEA26 0x001DECB0 0x001DF70F 0x003392CF 0x003E5467 pass global Eva at 0x009FDC30 with AsciiString key; EVA: prefix and Unknown EVA event strings prove Eva.
// Returns -1 on miss else node+8 message id; ret 4 is thiscall with one arg.
#include "ascii_string.h"
class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
};
class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};
class Eva
{
public:
	int rva001DE78E(const AsciiString *key);
private:
	char m_pad[0x34];
	Rva00056F61 m_table;
};
int Eva::rva001DE78E(const AsciiString *key)
{
	Rva0041534BIter it = m_table.rva0041534B(key);
	if (it.m_node == 0)
		return -1;
	return *(int *)((char *)it.m_node + 8);
}
