// cl: /O1 /MD /DNDEBUG /ICode/GameEngine/Source/Common
// ?rva002766F8@Drawable@@QAEXABUOpaqueRefElement4@@@Z, retail 0x002766F8
// (103B, RET 4): Drawable keeps three {reference, frame} slots at +0x38C
// (8 bytes each). Storing a reference reuses the slot already holding it,
// else the least recently stamped one, assigns it through the rowed
// OpaqueRefElement4 assignment (0x00239099) and stamps TheGameLogic's frame
// (+0x40). Name and the slots' purpose are unproven; layout is retail's.

typedef int Int;
typedef unsigned int UnsignedInt;

struct OpaqueRefElement4
{
	void *m_ref;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

struct DrawableRecentRef
{
	OpaqueRefElement4 m_ref;
	UnsignedInt m_frame;
};

enum { DRAWABLE_RECENT_REF_SLOTS = 3 };

class Drawable
{
public:
	void rva002766F8(const OpaqueRefElement4 &ref);
private:
	unsigned char m_pad000[0x38C];
	DrawableRecentRef m_recentRefs[DRAWABLE_RECENT_REF_SLOTS]; // +0x38C
};

void Drawable::rva002766F8(const OpaqueRefElement4 &ref)
{
	Int slot = -1;
	for (Int i = 0; i < DRAWABLE_RECENT_REF_SLOTS; ++i)
	{
		if (m_recentRefs[i].m_ref.m_ref == ref.m_ref)
		{
			slot = i;
			break;
		}
		if (slot == -1 || m_recentRefs[i].m_frame < m_recentRefs[slot].m_frame)
			slot = i;
	}
	m_recentRefs[slot].m_ref = ref;
	m_recentRefs[slot].m_frame = TheGameLogic->getFrame();
}
