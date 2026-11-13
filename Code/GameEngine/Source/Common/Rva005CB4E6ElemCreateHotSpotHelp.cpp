// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?CreateHotSpotHelp@Rva005CB4E6Elem@@QAEXXZ retail 0x005CB52B (504 bytes).
// WorldBuilder names the twin 0x015AF9B0
// StrategicInGameUI::RegionDisplay::Impl::CreateHotSpotHelp
// (StrategicInGameUIRegionDisplay.cpp); the ledger's address name for the
// object is Rva005CB4E6Elem (ctor 0x005CB4C7, dtor 0x005CB4E6). Its two
// callers (0x005CB772 and 0x005CB79D) run it once both the hot-spot source
// (+0x08) and the help box (+0x0C) exist. It builds three rowed
// InGameHotSpotSimpleHelp objects (0x005E0BBE) for the source's hot spots
// (virtual slots 7, 8 and 9) with two text strings each, fetched through
// the rowed UnicodeString getters on the label object at 0x00E065EC, and
// hands them to the holders at +0x10, +0x14 and +0x18 (rowed reset 0x005CB337).
#include "ascii_string.h"
#include "unicode_string.h"

class InGameHelpBox;
class InGameHotSpot;

class Rva005E0B0F
{
public:
	virtual ~Rva005E0B0F();
};

class InGameHotSpotSimpleHelp : public Rva005E0B0F
{
public:
	InGameHotSpotSimpleHelp(InGameHelpBox *box, InGameHotSpot *spot, const UnicodeString &title, const UnicodeString &text);

private:
	unsigned char m_pad04[0x18 - 0x04];
};

// The owner of the three help objects (+0x10/+0x14/+0x18).
#include "../../Include/Common/Rva005CB31D.h"

// The hot-spot source at +0x08: slots 7, 8 and 9 name its three hot spots.
class Rva005CB52BHotSpots
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06();
	virtual InGameHotSpot *hotSpot7();
	virtual InGameHotSpot *hotSpot8();
	virtual InGameHotSpot *hotSpot9();
};

// The label object at 0x00E065EC and its rowed UnicodeString getters.
// Defined here: nothing else in the tree did. Retail's 32-byte zero-filled
// .bss object (RVA 0x00A065EC), constructed in place by the 0x007B494C
// initializer; its referencing units spell it as this scalar.
extern unsigned int g_Va00E065EC[8];
unsigned int g_Va00E065EC[8];

#include "../../Include/GameClient/Rva005E755E.h"
#include "../../Include/Common/Rva005E3DE8.h"
#include "../../Include/Common/Rva004FCB85.h"
class Rva004FCB61 { public: UnicodeString rva004fcb61(); };
#include "../../Include/Common/Rva004FCBA9.h"
#include "../../Include/Common/Rva003F83B5.h"

#define REGION_LABELS(T) ((T *)&g_Va00E065EC)

class Rva005CB8D4;

class Rva005CB4E6Elem
{
public:
	void CreateHotSpotHelp();

private:
	Rva005CB8D4 *m_owner;
	int m_04;
	Rva005CB52BHotSpots *m_hotSpots; // +0x08
	InGameHelpBox *m_helpBox; // +0x0C
	Rva005CB31D m_help1; // +0x10
	Rva005CB31D m_help2; // +0x14
	Rva005CB31D m_help3; // +0x18
};

void Rva005CB4E6Elem::CreateHotSpotHelp()
{
	m_help1.rva005CB337(new InGameHotSpotSimpleHelp(m_helpBox, m_hotSpots->hotSpot7(),
		REGION_LABELS(Rva005E3DE8)->rva005E3E1D(), REGION_LABELS(Rva005E755E)->rva005e755e()));
	m_help2.rva005CB337(new InGameHotSpotSimpleHelp(m_helpBox, m_hotSpots->hotSpot8(),
		REGION_LABELS(Rva004FCB61)->rva004fcb61(), REGION_LABELS(Rva004FCB85)->rva004fcb85()));
	m_help3.rva005CB337(new InGameHotSpotSimpleHelp(m_helpBox, m_hotSpots->hotSpot9(),
		REGION_LABELS(Rva003F83B5)->rva003F83B5(), REGION_LABELS(Rva004FCBA9)->rva004fcba9()));
}
