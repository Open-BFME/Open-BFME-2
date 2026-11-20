// cl: /DNDEBUG /MD
// ?rva00366500@Rva00366500@@QAE_NH@Z 0x00366500 45B bitfield setter at +0xC bits 4-9 mask 0x3F0 callers 0x0052E6E6 0x0052E914 0x00366E2E

#include "../../../Include/GameLogic/PathfindCell.h"

#include "../../../Include/GameLogic/Rva00366500.h"

bool Rva00366500::rva00366500(int v)
{
	unsigned int &flags = reinterpret_cast<PathfindCell *>(this)->m_0C;
	unsigned int cur = flags;
	unsigned int field = (cur >> 4) & 0x3f;
	if (field == (unsigned int)v)
		return false;
	flags = (cur & ~0x3f0u) | (((unsigned int)v << 4) & 0x3f0u);
	return true;
}

bool Rva00366500::rva0036652D(int v)
{
	unsigned int &flags = reinterpret_cast<PathfindCell *>(this)->m_0C;
	unsigned int cur = flags;
	unsigned int field = (cur >> 10) & 0x3f;
	if (field == (unsigned int)v)
		return false;
	flags = (cur & ~0xfc00u) | (((unsigned int)v << 10) & 0xfc00u);
	return true;
}
