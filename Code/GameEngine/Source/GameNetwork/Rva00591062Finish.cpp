// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?Rva00591062Get@@YAHPAURva00591062Host@@@Z @0x00591062, 82B.
// Length sum of two AsciiString members at +0x1C/+0x20 via rowed
// CDDrive::getPath 0x002D9BA6 (called non-virtually, matching the direct
// REL32) and Rva002D9BC1 getter 0x002D9BC1, plus 0x11. Lengths read inline
// from the StringBase header length at +4 with a null check; temps release
// via rowed releaseBuffer 0x00036410. Caller at 0x00592A1D proves the
// free-function shape. Honest address name; host class unproven.
//
// The local field pointer is load-bearing: it makes the second hidden-return
// temporary land in the dead argument home [ebp+8], the slot retail uses,
// instead of reusing [ebp-4].
#include "ascii_string.h"

class CDDrive
{
public:
	virtual AsciiString getPath();
};

class Rva002D9BC1AsciiField
{
public:
	AsciiString get() const;
};

struct Rva00591062Host
{
	char m_pad[0x1C];
	AsciiString m_s1C; // +0x1C
	AsciiString m_s20; // +0x20
};

int Rva00591062Get(Rva00591062Host *p)
{
	int l1 = ((CDDrive *)p)->CDDrive::getPath().getLength();
	Rva002D9BC1AsciiField *f = (Rva002D9BC1AsciiField *)(void *)p;
	int l2 = f->get().getLength();
	return l1 + l2 + 0x11;
}
