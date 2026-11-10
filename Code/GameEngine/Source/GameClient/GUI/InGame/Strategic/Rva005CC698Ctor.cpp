// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Native EH action 0x7A1414 destroys the counted virtual base at +0xC guarded by the most-derived constructor flag; the complete parent EH graph proves this 28B lifetime.
//
// ??0Rva005CC698@@QAE@PAX0PAURva005CE93EContext@@@Z, retail 0x005CC698
// (240 bytes, RET 0x10 with MSVC's hidden most-derived flag): the constructor
// of the base the rowed Rva005CE93E constructor 0x005CE93E chains to.
// WorldBuilder names the body StrategicInGameUI::RegionDetailsPanel's
// constructor (WB 0x015BF460, StrategicInGameUIRegionDetailsPanel.cpp); the
// address-derived spelling is the one its rowed caller binds.
// Target evidence: over the rowed Rva005CC5E5 base (0x005CC5E5; primary +0,
// vbptr +4, shared Rva0007DF07 virtual base, here at +0x0C) the +8 holder
// starts empty, then the context's mode word (reached through its first
// field) is settled: 1 when record +4 is set, else 2 when record +8 is set,
// and a mode-2 region the local living-world player (rowed 0x002B2B66) does
// not own (+0x13C) falls back to 0. The holder then takes (rowed setter
// 0x00575674) a new 0x20-byte region details panel built by the rowed
// constructor 0x005CC543 from this, both arguments, the mode word and the
// context. The unwind map destroys the holder (+8) and the base.
#include "ascii_string.h"

#include "../../../../../Include/Common/Rva0007DF07.h"

class Rva005CC5E5 : public virtual Rva0007DF07
{
public:
	Rva005CC5E5() throw();
	virtual void slot0();
	virtual ~Rva005CC5E5();
};

class Object;
#include "../../../../../Include/Common/Rva00575674.h"

struct Rva005CC5C8Region
{
	unsigned char m_pad000[0x13C];
	int m_ownerPlayer;		// +0x13C
};

struct Rva005CC5C8Record
{
	Rva005CC5C8Region *m_region;
	int m_04;
	int m_08;
	int m_0C;
};

struct Rva005CC5C8Context
{
	int m_00;
	Rva005CC5C8Record m_record;	// +0x04
};

struct Rva005CE93EContext
{
	int **m_mode;			// +0x00
	Rva005CC5C8Record m_record;	// +0x04
	void *source;			// +0x14
	int *mode() const { return *m_mode; }
};

class Rva005CC5C8
{
public:
	Rva005CC5C8(int owner, int level, const AsciiString &name, int *mode, const Rva005CC5C8Context *context);
private:
	unsigned char m_data[0x20];
};

#include "../../../../../Include/Common/Rva002B2B66.h"
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva005CC698 : public Rva005CC5E5
{
public:
	Rva005CC698(void *, void *, Rva005CE93EContext *);
	virtual ~Rva005CC698();
private:
	Rva00575674 m_panel;		// +0x08
};

Rva005CC698::Rva005CC698(void *level, void *name, Rva005CE93EContext *context)
{
	int *mode = context->mode();
	if (context->m_record.m_04)
		*mode = 1;
	else
	{
		if (context->m_record.m_08)
			*mode = 2;
		if (*mode == 2)
		{
			int regionOwner = context->m_record.m_region->m_ownerPlayer;
			if (regionOwner != ((Rva002B2B66 *)TheLivingWorldLogic)->rva002B2B66())
				*mode = 0;
		}
	}
	m_panel.rva00575674((Object *)new Rva005CC5C8((int)this, (int)level, *(const AsciiString *)name,
		context->mode(), (const Rva005CC5C8Context *)context));
}
