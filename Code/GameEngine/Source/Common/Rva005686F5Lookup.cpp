// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?rva005686F5@@YGPAXPBURva005686F5Elem@@@Z @0x005686F5 44B.
// Null-guarded two-stage name lookup: if g_00DFE1A8 is null return 0,
// else scan it with Rva0020DB91::rva0020DB91 (rowed 0x0020DB91) for m_00;
// a miss returns 0, a hit runs the pinned 0x003EE083 AsciiString scan on
// m_04. The element carries two adjacent AsciiStrings at +0/+4 (the +4 is
// the observed add-esi-4); later fields seen at the 0x0056956D caller.
#include "ascii_string.h"

class Rva0020DB91
{
public:
	void *rva0020DB91(const AsciiString &arg);
};

extern Rva0020DB91 *g_00DFE1A8;

class Rva003EE083
{
public:
	void *rva003EE083(const AsciiString &arg);
};

struct Rva005686F5Elem
{
	AsciiString m_00;
	AsciiString m_04;
};

void *__stdcall rva005686F5(const Rva005686F5Elem *e)
{
	if (g_00DFE1A8 == 0)
		return 0;
	void *item = g_00DFE1A8->rva0020DB91(e->m_00);
	if (item == 0)
		return 0;
	return ((Rva003EE083 *)item)->rva003EE083(e->m_04);
}
