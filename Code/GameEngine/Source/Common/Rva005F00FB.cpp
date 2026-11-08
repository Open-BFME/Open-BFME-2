// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
//
// ??0Rva005F00FB@@QAE@XZ, retail 0x005F005B, 160 bytes.
//
// Evidence (retail body only; names are address-derived):
//  5f005b: mov eax, FuncInfo / call __EH_prolog
//          AsciiString temp("TypeImages") at [ebp-0x10] through the folded
//          StringBase ctor 0x00037BA0, then the base ctor 0x00221635 with
//          &temp, then the temp's release at 0x00036410.
//          vtable 0x00C78A78 stored at +0, then two EH vector constructor
//          iterators at +8 (stride 4, count 5) and +0x1C (stride 4, count 8)
//          with element ctor 0x00326BE6 and element dtor 0x0048BA39.
//          Two pointer loops zero five dwords at +0x3C and five at +0x50.
// The sibling dtor 0x005F00FB (banked, unlanded) tears the same two arrays
// down through 0x00629110 with the same element dtor, then calls the base
// dtor 0x0022167C, which confirms the two AsciiString arrays and the +0
// polymorphic base (vptr/m_at4 from 0x0022167C's own body).
// Identity is not recovered: the class and member names are address-derived.

#include "ascii_string.h"

class Rva0022167C
{
public:
	Rva0022167C(const AsciiString &name);
	virtual ~Rva0022167C();

private:
	void *m_at4;
};

class Rva005F00FB : public Rva0022167C
{
public:
	Rva005F00FB();
	virtual ~Rva005F00FB();

private:
	AsciiString m_at8[5];  // +0x08, twenty bytes
	AsciiString m_at1c[8]; // +0x1C, thirty-two bytes
	unsigned int m_at3c[5]; // +0x3C
	unsigned int m_at50[5]; // +0x50
};

Rva005F00FB::Rva005F00FB() : Rva0022167C(AsciiString("TypeImages"))
{
	unsigned int *p = m_at3c;
	while (p != m_at50)
		*p++ = 0;
	unsigned int *q = m_at50;
	while (q != m_at50 + 5)
		*q++ = 0;
}

// P36 TEST-BRANCH-ONLY diagnostic: construct the image-type cache global in place with the retail ctor.
inline void *operator new(unsigned int, void *where) { return where; }
void bfmeP36ConstructTypeImages(void *cache)
{
	new (cache) Rva005F00FB;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0022167C reads ??1Rva0022167C@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva0022167C@@UAE@XZ=??1Rva0022167C@@QAE@XZ")
//   0x00221635 reads ??0Rva00221635@@QAE@H@Z
#pragma comment(linker, "/alternatename:??0Rva0022167C@@QAE@ABVAsciiString@@@Z=??0Rva00221635@@QAE@H@Z")
