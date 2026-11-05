// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003F797C@Rva000427195@@QAEPAXPAXPBVAsciiString@@@Z @0x003F797C 36B
// Ensure-capacity wrapper over the Eva bucket find-or-insert. Evidence: calls
// pin-only resize 0x00212858 with size+1 then rowed 0x003F78A9; same table
// layout as EvaBucketIndex/Advance/Insert siblings; callers at 0x003F7B16
// and 0x003F7B8E; landing this unblocks 0x003F7B59.
#include "ascii_string.h"

#include "../../Include/GameLogic/Rva000427195.h"

void *Rva000427195::rva003F797C(void *out, const AsciiString *key)
{
	rva00212858(m_numElements + 1);
	rva003F78A9(out, key);
	return out;
}

// ?rva003F7B0E@Rva000427195@@QAEPAXPAXPBVAsciiString@@@Z @0x003F7B0E 20B:
// the table-level wrapper over the ensure above (its call at 0x003F7B16),
// forwarding the hidden result slot and the key and handing the slot back.
// Skeleton twin of map<int,int>::equal_range 0x002B8120.
void *Rva000427195::rva003F7B0E(void *out, const AsciiString *key)
{
	rva003F797C(out, key);
	return out;
}
