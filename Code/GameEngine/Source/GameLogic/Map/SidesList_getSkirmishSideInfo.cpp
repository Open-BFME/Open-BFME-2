// cl: /DNDEBUG /MD /EHsc
//
// ?getSkirmishSideInfo@SidesList@@QAEPAVSidesInfo@@H@Z
// retail 0x002A98D1, 33 bytes. Dedicated TU.
//
// Donor: SidesList::getSkirmishSideInfo, the inline accessor in
// reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/
// GameEngine/Include/GameLogic/SidesList.h (BFME1 keeps the same header
// inline; its out-of-line copy here sits among the Player bodies that call it
// on TheSidesList). Bounds-checked index into the skirmish side array, NULL
// when out of range. BFME2 layout per the rowed SidesList_sidesInfo.cpp:
// m_numSkirmishSides at +0x7C0, m_skirmishSides at +0x7C4 with a 0x60 stride.
// Same spelling as the rowed getSideInfo twin at 0x002035BA.

#include "../../../Include/GameLogic/SidesInfo.h"

class SidesList
{
public:
	SidesInfo *getSkirmishSideInfo(int i);

private:
	unsigned char m_pad[0x7C0];
	int m_numSkirmishSides; // +0x7C0
	SidesInfo m_skirmishSides[1]; // +0x7C4, 0x60 stride
};

// ?getSkirmishSideInfo@SidesList@@QAEPAVSidesInfo@@H@Z
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline SidesInfo *SidesList::getSkirmishSideInfo(int i)
{
	return (i >= 0 && i < m_numSkirmishSides) ? &m_skirmishSides[i] : 0;
}

// ?bfmeAnchorSidesListGetSkirmishSideInfo absent-from-retail
SidesInfo *bfmeAnchorSidesListGetSkirmishSideInfo(SidesList *sidesList, int i)
{
	return sidesList->getSkirmishSideInfo(i);
}

