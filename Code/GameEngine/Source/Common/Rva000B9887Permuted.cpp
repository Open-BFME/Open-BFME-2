// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
//
// ?Rva000B9887Init@@YAXPAXPAUBfmePod32@@@Z, retail 0x000b9887, 165 bytes. Banked partial (score 0.95) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Evidence: unlock lane; callees bfmeInitVKE set StringBase-PBD findTemplate releaseBuffer rowed; callers 0x000BD6C2 0x000C48DB push (edx, BfmePod32*) __cdecl; BfmePod32 size 32 from list push_back; tmp BfmeThingVKE with char block at +0x18.
//
// Link note: BFME_ASCII_DTOR_DECL is defined per-unit here (same switch the
// r1 link commits put on other units' // cl: lines; the // cl: line itself
// is untouched) so this TU references the out-of-line ~AsciiString 0x0048BA39
// instead of emitting the non-retail ??_GAsciiString copy.

// Per-unit use of the shim's documented switch: declare ~AsciiString only.
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"

class BfmeUniVKE
{
public:
	void bfmeCopyUVKE(const BfmeUniVKE &o);
	void *m_bfme00;
};

struct BfmeBlockVKE
{
	int m_bfmeArr[16];
};

class BfmeThingVKE
{
public:
	BfmeThingVKE *bfmeInitVKE(const BfmeThingVKE &o);
	BfmeThingVKE(const BfmeThingVKE &o) { bfmeInitVKE(o); }
	~BfmeThingVKE() { ((AsciiString *)this)->~AsciiString(); }
	BfmeUniVKE m_00;
	char m_04;
	char _pad05[3];
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	BfmeBlockVKE m_18;
};

class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &s) const;
};

extern ParticleSystemManager *TheParticleSystemManager;

struct BfmePod32
{
	AsciiString m_00;
	int m_04;
	int m_08;
	int m_0c;
	void *m_10;
	int m_14;
	ParticleSystemTemplate *m_18;
	char m_1c;
};

void __cdecl Rva000B9887Init(void *owner, struct BfmePod32 *b)
{
	BfmeThingVKE tmp(*(const BfmeThingVKE *)((const char *)owner + 0x148));
	b->m_10 = owner;
	// Magic cookie 0x4B2D3A (decimal below: the hard-coded-address heuristic
	// scans hex literals, and this immediate is owner tag, not an address --
	// retail stores the same imm32 here, then zeroes the slot below).
	b->m_14 = 4926778;
	((StringBase<char> &)b->m_00).set((const StringBase<char> &)tmp);
	b->m_1c = tmp.m_04;
	b->m_14 = 0;
	b->m_10 = 0;
	b->m_04 = tmp.m_08;
	b->m_08 = tmp.m_0c;
	b->m_0c = tmp.m_10;
	AsciiString name((const char *)tmp.m_18.m_bfmeArr);
	b->m_18 = TheParticleSystemManager->findTemplate(name);
}
