// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfmelist /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
// stlport
//
// ?rva0043888E@Rva00439E0C@@QAEXPAURva004393D6@@@Z, retail 0x0043888E
// (85 bytes).  First call of the detection walk 0x0043966A, on the same
// receiver (TheGameLogic's +0x178 invisibility manager) and record: drops
// every inactive entry (+0xC0 byte clear) whose window (+0xB8 start plus
// +0xBC duration) ended before the current logic frame.  The record is the
// STLport list of 196-byte entries plus three words (Rva004393D6Copy.cpp);
// the erase is the list's own (retail's folded body at 0x00438539).
// Field names are neutral.
#include "GameLogicObjectLookupView.h"
#include <list>

extern GameLogic *TheGameLogic;

struct BfmePod196 { int a[49]; };

struct Rva004393D6Entry
{
	char m_pad00[0xB8];
	unsigned int m_start;	// +0xB8
	unsigned int m_duration;	// +0xBC
	bool m_active;	// +0xC0
};

struct Rva004393D6 : public _STL::list<BfmePod196>
{
	int m_04;
	int m_08;
	int m_0c;
};

class Rva00439E0C
{
public:
	void rva0043888E(Rva004393D6 *record);
};

void Rva00439E0C::rva0043888E(Rva004393D6 *record)
{
	unsigned int frame = TheGameLogic->getFrame();
	Rva004393D6::iterator it = record->begin();
	while (it != record->end())
	{
		const Rva004393D6Entry *entry = (const Rva004393D6Entry *)&*it;
		if (!entry->m_active && frame > entry->m_start + entry->m_duration)
		{
			Rva004393D6::iterator next = it;
			++next;
			record->erase(it);
			it = next;
		}
		else
			++it;
	}
}
