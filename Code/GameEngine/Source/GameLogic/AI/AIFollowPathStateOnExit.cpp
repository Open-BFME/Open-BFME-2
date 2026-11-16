// cl: /DNDEBUG /MD
//
// AIFollowPathState::onExit, retail 0x00349D92 (131 bytes): slot 5 of vtable
// 0x00C12BC8, whose slot-2 name getter returns AIFollowPathState. Ported from
// Zero Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference): base onExit, then
// setCanPathThroughUnits(false), precise-z off and goal path index -1.
// BFME2 additions (target evidence): the AI's out-of-line +0x164 setter
// (pinned AIUpdateInterface::rva00262FEB, the body ICF-shared with
// ParticleEmitterDefClass::Set_Burst_Size) is called with 0 after the
// path-through flag; afterwards, unless the owner template's kind byte +0x115
// has mask 0x20, object status 90 is cleared through the rowed setStatus, and
// the current locomotor entry from the rowed Object::rva0028AC4E gets -1.0
// at +0x2C (both unnamed).
// Layout: AI +0x258 with goal path index +0x194, current locomotor +0x1F0
// (flags +0x44, USE_PRECISE_Z_POS bit 3) and can-path-through-units +0x3BA.
typedef bool Bool;
typedef float Real;
enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_90 = 90
};
#include "../../../Include/GameLogic/LocomotorClass.h"
// LINK: the 0x00262FEB one-store setter is ICF-shared with ParticleEmitterDefClass::Set_Burst_Size (called directly, not via vtable).
class ParticleEmitterDefClass
{
public:
	virtual void Set_Burst_Size(unsigned int value);
};

#include "../../../Include/GameLogic/Module/AIUpdate.h"
struct Rva0028AC4EEntry
{
	unsigned char m_pad00[0x2C];
	Real m_bfme2C; // +0x2C
};
#include "../../../Include/Common/ThingTemplate.h"
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	const ThingTemplate *getTemplate() const { return m_template; }
	void setStatus(ObjectStatusTypes status, bool set);
	const Rva0028AC4EEntry *rva0028AC4E() const;
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x258 - 0x08];
	AIUpdateInterface *m_ai; // +0x258
};
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"
#include "../../../Include/GameLogic/AIInternalMoveToState.h"
class AIFollowPathState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

void AIFollowPathState::onExit( StateExitType status )
{
	AIInternalMoveToState::onExit( status );

	// turn off precision-z-pos when we exit, just in case.
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (!ai) return;
	ai->m_field3BA = false;
	((ParticleEmitterDefClass *)ai)->ParticleEmitterDefClass::Set_Burst_Size(0);
	if (ai->getCurLocomotor())
		ai->getCurLocomotor()->setUsePreciseZPos(false);

	//Assign this value to the AIUpdateInterface so object's can access this value while
	//determine which waypoints to plot in the waypoint renderer.
	ai->m_field194 = -1;

	Object *obj = getMachineOwner();
	if (!((obj->getTemplate()->m_kindof[3] & (1U << 13)) != 0))
		obj->setStatus(OBJECT_STATUS_BFME_90, false);
	if (obj->rva0028AC4E())
		const_cast<Rva0028AC4EEntry *>(obj->rva0028AC4E())->m_bfme2C = -1.0f;
}
