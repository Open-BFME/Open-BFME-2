// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003F797C@Rva000427195@@QAEPAXPAXPBVAsciiString@@@Z @0x003F797C 36B
// Ensure-capacity wrapper over the Eva bucket find-or-insert. Evidence: calls
// pin-only resize 0x00212858 with size+1 then rowed 0x003F78A9; same table
// layout as EvaBucketIndex/Advance/Insert siblings; callers at 0x003F7B16
// and 0x003F7B8E; landing this unblocks 0x003F7B59.
#include "ascii_string.h"

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
	void *rva003F78A9(void *out, const AsciiString *key);
	void *rva003F797C(void *out, const AsciiString *key);
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	int m_pad0C;
	int m_size;
};

void *Rva000427195::rva003F797C(void *out, const AsciiString *key)
{
	rva00212858((unsigned int)(m_size + 1));
	rva003F78A9(out, key);
	return out;
}
