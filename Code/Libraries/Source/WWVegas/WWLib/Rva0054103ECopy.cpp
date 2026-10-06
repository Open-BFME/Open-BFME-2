// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
//
// ??0Rva0054103E@@QAE@ABV0@@Z @0x0054103E (29B).
// Rva0054103E copy ctor: dword at +0 plus Region2D at +4 (20B total).
// Retail copies [src+0] to [this+0] then tail-calls the rowed Region2D copy
// ctor at 0x4254E for [this+4] from [src+4] and returns this in eax.
// Evidence: four vector callers use it as the 0x14 element copy (uninit copy
// at 0x005410B1 with count (last-first)/0x14, guard at 0x0054106D, uninit copy
// at 0x0054115F, insert at 0x00541DDF); no vptr stores so non-virtual.

struct Region2D
{
	Region2D(const Region2D &that);
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

class Rva0054103E
{
public:
	Rva0054103E(const Rva0054103E &that);

private:
	int m_00;
	Region2D m_04;
};

Rva0054103E::Rva0054103E(const Rva0054103E &that)
	: m_00(that.m_00)
	, m_04(that.m_04)
{
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:??4Rva0054103E@@QAEAAV0@ABV0@@Z=??0Rva0054103E@@QAE@ABV0@@Z")
