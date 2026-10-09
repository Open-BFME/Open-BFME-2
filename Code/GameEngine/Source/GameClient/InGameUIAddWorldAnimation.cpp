// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?addWorldAnimation@InGameUI@@QAEXPAVAnim2DTemplate@@PBUCoord3D@@W4WorldAnimationOptions@@MM@Z
// retail 0x002A0E16..0x002A0F19 (259 bytes) EH thiscall ret 0x14; not in the
// InGameUI vftable. Callers 0x0045280B and 0x00294F5E.
// Donor: ZH and BFME 1 GameEngine/Source/GameClient/InGameUI.cpp
// addWorldAnimation (BFME 1 row 0x00443720) with the same control flow:
// sanity on template / position / positive duration; a 0x1C-byte
// WorldAnimationData from operator new 0x0002FDA0 with its constructor
// inlined (zero stores; the out-of-line copy is the rowed 0x0029AF82); a
// 0x34-byte Anim2D built by the pinned constructor 0x002D6D63 from the
// template and TheAnim2DCollection under unwind state 0 (operator delete
// 0x0002FD60 on throw); the expire frame is TheGameLogic's frame (+0x40
// unsigned) plus the duration times the logic frame rate g_Va00DBA4E4 via
// ftol2; options at +0x14 position at +4 z rise at +0x18; then the record is
// pushed on the list at +0x8CC through the folded four-byte push_front at
// 0x00392076, viewed as the rowed list<int> as in
// InGameUIUpdateAndDrawWorldAnimations.cpp. The pinned Anim2D constructor
// spells its arguments with address-derived types so the template and
// collection are cast to them.
// InGameUI.cpp still carries a present-unmatched copy of this body.
#include <list>
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../Common/GameLogicObjectLookupView.h"

typedef float Real;
typedef unsigned int UnsignedInt;

enum WorldAnimationOptions
{
	WORLD_ANIM_NO_OPTIONS = 0
};

class Anim2DTemplate;
class Anim2DCollection;
struct Rva002D752DNode;
class Rva002D752D;

class Anim2D
{
public:
	Anim2D(Rva002D752DNode *animTemplate, Rva002D752D *collectionSystem);

private:
	char m_storage[0x34];
};

extern Anim2DCollection *TheAnim2DCollection;
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;

class WorldAnimationData
{
public:
	WorldAnimationData(void)
	{
		m_anim = 0;
		m_worldPos.x = 0.0f;
		m_worldPos.y = 0.0f;
		m_worldPos.z = 0.0f;
		m_expireFrame = 0;
		m_options = WORLD_ANIM_NO_OPTIONS;
		m_zRisePerSecond = 0.0f;
	}

	Anim2D *m_anim;	// +0x00
	Coord3D m_worldPos;	// +0x04
	UnsignedInt m_expireFrame;	// +0x10
	WorldAnimationOptions m_options;	// +0x14
	Real m_zRisePerSecond;	// +0x18
};

// Retail's world animation list as the rowed four-byte list<int>.
typedef _STL::list<int> WorldAnimationList;

class InGameUI
{
public:
	void addWorldAnimation(Anim2DTemplate *animTemplate, const Coord3D *pos,
		WorldAnimationOptions options, Real durationInSeconds, Real zRisePerSecond);

private:
	char m_opaque000[0x8CC];
	WorldAnimationList m_worldAnimationList;	// +0x8CC
};

void InGameUI::addWorldAnimation(Anim2DTemplate *animTemplate, const Coord3D *pos,
	WorldAnimationOptions options, Real durationInSeconds, Real zRisePerSecond)
{
	// sanity
	if (animTemplate == 0 || pos == 0 || durationInSeconds <= 0.0f)
		return;

	// allocate a new world animation data struct
	WorldAnimationData *wad = new WorldAnimationData;
	if (wad == 0)
		return;

	// allocate a new animation instance
	Anim2D *anim = new Anim2D((Rva002D752DNode *)animTemplate, (Rva002D752D *)TheAnim2DCollection);

	// assign all data
	wad->m_anim = anim;
	wad->m_expireFrame = TheGameLogic->getFrame() + (durationInSeconds * g_Va00DBA4E4);
	wad->m_options = options;
	wad->m_worldPos = *pos;
	wad->m_zRisePerSecond = zRisePerSecond;

	// add to list
	m_worldAnimationList.push_front(reinterpret_cast<const int &>(wad));
}
