// cl: /O1 /MD /DNDEBUG /ICode/GameEngine/Source/Common
// ?rva002766F8@Drawable@@QAEXABUOpaqueRefElement4@@@Z, retail 0x002766F8
// (103B, RET 4): Drawable keeps three {reference, frame} slots at +0x38C
// (8 bytes each). Storing a reference reuses the slot already holding it,
// else the least recently stamped one, assigns it through the rowed
// OpaqueRefElement4 assignment (0x00239099) and stamps TheGameLogic's frame
// (+0x40). Name and the slots' purpose are unproven; layout is retail's.

typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../Include/Common/OpaqueRefElement4.h"
#include "../../Include/GameClient/Drawable.h"

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

struct DrawableRecentRef
{
	OpaqueRefElement4 m_ref;
	UnsignedInt m_frame;
};

enum { DRAWABLE_RECENT_REF_SLOTS = 3 };

// Retail field view for the three pairs inside Drawable's opaque region.
struct DrawableRecentRefStorage
{
	unsigned char m_pad000[0x38C];
	DrawableRecentRef m_recentRefs[DRAWABLE_RECENT_REF_SLOTS];
};

void Drawable::rva002766F8(const OpaqueRefElement4 &ref)
{
	DrawableRecentRefStorage *storage = reinterpret_cast<DrawableRecentRefStorage *>(this);
	Int slot = -1;
	for (Int i = 0; i < DRAWABLE_RECENT_REF_SLOTS; ++i)
	{
		if (storage->m_recentRefs[i].m_ref.referent == ref.referent)
		{
			slot = i;
			break;
		}
		if (slot == -1 || storage->m_recentRefs[i].m_frame < storage->m_recentRefs[slot].m_frame)
			slot = i;
	}
	storage->m_recentRefs[slot].m_ref = ref;
	storage->m_recentRefs[slot].m_frame = TheGameLogic->getFrame();
}
