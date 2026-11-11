// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
//
// ??0Rva005E9F7B@@QAE@XZ, retail 0x005E2237, 86 bytes.
//
// Evidence (retail body only; names are address-derived):
//  5e2237: mov eax, FuncInfo / call __EH_prolog
//          AsciiString temp("RegionDetailsPanelStructuresPage") at [ebp-0x10]
//          through the folded StringBase ctor 0x00037BA0, then the pinned base
//          ctor Rva0022167C 0x00221635 with &temp, then the temp release at
//          0x00036410. Then vtable 0x00C77AD8 at +0 and the constant
//          0x80FFFFFF stored at +8; this is the last body before the rowed
//          19-byte Icon::getBuildPlot at 0x005E228D, so the extent is 86 B
//          (an earlier 105-byte claim ran into that body).
// The class shares its slot-0 deleting dtor 0x005EA68B and the rowed
// non-deleting dtor ??1Rva005E9F7B@@UAE@XZ at 0x005E9F7B (5-byte jmp to the
// base dtor); the panel page's own vtable sits where the dtor's sibling rows
// put it. Identity beyond the shared dtor family is not recovered.

#include "ascii_string.h"

class Rva0022167C
{
public:
	Rva0022167C(const AsciiString &name);
	virtual ~Rva0022167C();

private:
	void *m_at4;
};

class INI;
class Rva005E9F7B : public Rva0022167C
{
public:
	Rva005E9F7B();
	virtual ~Rva005E9F7B();
	virtual void rva005E2126(INI *ini);

private:
	unsigned int m_at8; // 0x80FFFFFF
};

Rva005E9F7B::Rva005E9F7B() : Rva0022167C(AsciiString("RegionDetailsPanelStructuresPage")), m_at8(0x80FFFFFFu)
{
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0022167C reads ??1Rva0022167C@@QAE@XZ
//   0x00221635 reads ??0Rva00221635@@QAE@H@Z
