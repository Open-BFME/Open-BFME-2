// cl: /DNDEBUG /MD
//
// AIDeadState::onExit, retail 0x00347110 (30 bytes): slot 5 of vtable
// 0x00C11318, whose slot-2 name getter returns AIDeadState; the Zero Hour
// AIStates.cpp body clears MODELCONDITION_DYING on the machine owner, here bit
// 1*32+30 of the Object+0x10C words (byte +0x113 mask 0x40) with notifier
// 0x0028AE6D.
//
// AIDeadState::onEnter, retail 0x0034707A (150 bytes): slot 4 of the same
// vtable. The Zero Hour body builds nonDyingStuff and swaps it for
// MODELCONDITION_DYING through Object::clearAndSetModelConditionFlags, then
// notifies TheScriptEngine. Here the per-weapon-slot conditions come from
// the rowed builder 0x002C777E for slots 0..5 (OR-merged through the rowed
// 0x002C7492), bits 61 and 157 are set directly, the DYING mask is the
// rowed 0x0028F59A one-bit constructor (bit 0x3E) and the swap is the rowed
// Object::rva0028CFB2; the notifier is the rowed 0x002039B6 frame cache.
// BFME 2 then removes an object whose template has byte +0x109 bit 0 from
// the pathfind map (pinned Pathfinder::RemoveObjectFromPathfindMap).
#include <string.h>
class WeaponTemplateSetHead
{
	char m_data[0x4C];
};
WeaponTemplateSetHead *__cdecl rva002C777E(WeaponTemplateSetHead *out, int idx);
class Rva002C7492
{
public:
	void rva002C7492(const Rva002C7492 *other);
	void set(unsigned int bit) { m_mask[bit >> 5] |= 1U << (bit & 0x1f); }
private:
	unsigned int m_mask[19];
};
struct Rva0028F59A
{
	Rva0028F59A(int unused, int bit);
	unsigned int m_bits[19];
};
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;
class Rva002039B6Host
{
public:
	void rva002039B6();
};
#include "../../../Include/Common/ThingTemplate.h"
enum ModelConditionFlagType
{
	MODELCONDITION_DYING = 1 * 32 + 30
};
#include "../../../Include/GameClient/ModelConditionFlags.h"
class Object
{
public:
	void rva0028AE6D();
	void rva0028CFB2(const int *clr, const int *set);
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x4];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x10C - 0x8];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
};
#include "../../../Include/GameLogic/AIPathfind.h"
#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"
class AIDeadState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
};
StateReturnType AIDeadState::onEnter()
{
	Object *obj = getMachineOwner();
	if (obj)
	{
		Rva002C7492 nonDyingStuff;
		memset(&nonDyingStuff, 0, sizeof(nonDyingStuff));
		for (int slot = 0; slot < 6; slot++)
		{
			WeaponTemplateSetHead slotFlags;
			nonDyingStuff.rva002C7492((const Rva002C7492 *)rva002C777E(&slotFlags, slot));
		}
		nonDyingStuff.set(61);
		nonDyingStuff.set(157);
		obj->rva0028CFB2((const int *)&nonDyingStuff, (const int *)&Rva0028F59A(0, 0x3E));
		((Rva002039B6Host *)TheScriptEngine)->rva002039B6();
		if (((obj->getTemplate()->m_kindof[0] & (1U << 8)) != 0))
			TheAI->pathfinder()->RemoveObjectFromPathfindMap(obj);
	}
	return STATE_CONTINUE;
}
void AIDeadState::onExit(StateExitType status)
{
	Object *obj = getMachineOwner();
	obj->clearModelConditionState(MODELCONDITION_DYING);
}
