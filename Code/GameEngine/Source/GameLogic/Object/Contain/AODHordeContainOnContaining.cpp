// cl: /DNDEBUG /MD
//
// Target evidence: the AODHordeContain constructor in AODHordeContainCtor.cpp
// installs primary vftable 0x00C46570; its entry at 0x00C46C08 is this body at
// 0x0047A3CB. The body takes an Object pointer and a one-byte selection flag,
// fades in the object's drawable for five logic seconds, calls the int-taking
// method pinned at 0x0039B28F on Object+0x264, then forwards both arguments to
// 0x0046FA46. That base routine is a HordeContain vtable body and calls the
// rowed HordeContain routine at 0x0046A893.
//
// Identity inference: the same entry/argument shape is `onContaining(Object *,
// Bool)` in the BFME1 contain interface and its derived contain implementations.
// The target vtable relation supports AODHordeContain as the overriding class;
// the experience-tracker and helper names remain address-derived.

extern int BfmeLogicFramesPerSecond;

#include "../../../../Include/Common/Geometry.h"
#include "../../../../Include/GameClient/Drawable.h"

#include "../../../../Include/GameLogic/Module/Rva003BD306Target.h"

#include "../../../Common/Thing/thing.h"
struct Rva0028AC4EEntry;
class AIUpdateInterface;
enum KindOfType { KINDOF_INVALID = -1, KINDOF_RVA_0 = 0 };

class Object : public Thing
{
public:
    Drawable *getDrawable() const;
    const Rva0028AC4EEntry *rva0028AC4E() const;
    bool isKindOf(KindOfType kind) const;
    int rva0028B511() const;
    char m_pad060[0x74 - 0x60];
    int m_id; // +0x74
    char m_pad78[0xA8 - 0x78];
    GeometryInfo m_geometry;
    char m_pad104[0x258 - 0x104];
    AIUpdateInterface *m_ai; // +0x258
    char m_pad25C[0x264 - 0x25C];
    Rva003BD306Target *m_experienceTracker;
};

class HordeContain
{
public:
	virtual void onContaining(Object *object, bool wasSelected);
};

class AODHordeContain : public HordeContain
{
public:
	virtual void onContaining(Object *object, bool wasSelected);
};

// ?onContaining@AODHordeContain@@UAEXPAVObject@@_N@Z
void AODHordeContain::onContaining(Object *object, bool wasSelected)
{
	if (object->getDrawable())
		object->getDrawable()->fadeIn(BfmeLogicFramesPerSecond * 5);

	object->m_experienceTracker->rva0039B28F(1);
	HordeContain::onContaining(object, wasSelected);
}
