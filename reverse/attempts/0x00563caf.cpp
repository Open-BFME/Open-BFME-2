// ??0Rva00563CAF@@QAE@PAXPAUDrawInfo@@@Z
// partial score=0.91 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /DNDEBUG /MD /arch:SSE2
// Retail 0x00563CAF (RVA 0x00563CAF) size 115: particle draw module ctor.
// Evidence: pinned ParticleModule005F2CA0 base 0x0055C86D then vtable 0xC1D588 plus s_slot3E4first at +0x14 plus GpuDrawModuleInfo at +0x18 with vtable 0xC1D5B4 then ints string float from info +0xc/+0x10/+0x14/+0x18.
#include "ascii_string.h"

extern const void *const g_00C1D588[];
extern const void *const g_00C1D5B4[];
extern "C" int s_slot3E4first;

class ParticleModule005F2CA0
{
public:
	ParticleModule005F2CA0(void *a, void *b);

private:
	char m_base[0x14];
};

class GpuDrawModuleInfo
{
public:
	GpuDrawModuleInfo();
	virtual ~GpuDrawModuleInfo();

public:
	int m_totalFrames;
	int m_framesPerRow;
	AsciiString m_detailTexture;
	float m_speedMultiplier;
};

struct DrawInfo
{
	char m_pad[0xc];
	int m_0c;
	int m_10;
	AsciiString m_14;
	float m_18;
};

class __declspec(novtable) Rva00563CAF : public ParticleModule005F2CA0
{
public:
	Rva00563CAF(void *a, DrawInfo *b);

private:
	void *m_14;
	GpuDrawModuleInfo m_18;
};

// ??0Rva00563CAF@@QAE@PAXPAUDrawInfo@@@Z present-unmatched
Rva00563CAF::Rva00563CAF(void *a, DrawInfo *b)
	: ParticleModule005F2CA0(a, b)
	, m_18()
{
	*(const void **)this = g_00C1D588;
	m_14 = (void *)&s_slot3E4first;
	*(const void **)((char *)this + 0x18) = g_00C1D5B4;
	m_18.m_totalFrames = b->m_0c;
	m_18.m_framesPerRow = b->m_10;
	((StringBase<char> *)&m_18.m_detailTexture)->set(*(const StringBase<char> *)&b->m_14);
	m_18.m_speedMultiplier = b->m_18;
}
