// A chain asked all the way along (trimmed from a six-errand donor; the
// other five are declared-only here).

struct BfmeThingET
{
	unsigned char m_bfmeHead[0x1f0];	// 0x000
};

int bfmeFindET(BfmeThingET *thing);


class Object;

// Partition filter base (address-named after its constructor 0x000421C8):
// allow is vftable slot 1; allows runs every filter along the +0x04 links.
#include "../../Include/GameLogic/PartitionFilter.h"

// ?allows@Rva000421C8@@QAE_NPAVObject@@@Z
bool Rva000421C8::allows(Object *obj)
{
	Rva000421C8 *at = this;

	while (at != 0)
	{
		if (!at->allow(obj))
			return false;

		at = at->m_next;
	}

	return true;
}


class BfmeMadeER
{
public:
	unsigned char m_bfmeHead[0x4c];		// 0x00
	void *m_bfmeBack;			// 0x4c
};


