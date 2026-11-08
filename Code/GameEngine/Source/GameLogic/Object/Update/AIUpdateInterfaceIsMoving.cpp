// cl: /O1 /DNDEBUG /MD
//
// ?isMoving@AIUpdateInterface@@QBE_NXZ
// retail 0x00264688, 97 bytes (Ghidra FUN_00664688), pinned from
// privateFollowPathAppend where the Open-BFME-1 donor asks isMoving().
//
// Body (layout from the banked attempt and its evidence): an object whose
// template has kind bit +0x108 & 4 never moves; an object contained by
// another (+0x274) that has an AI (+0x258) and whose template lacks bit
// +0x115 & 0x20 moves as its container does; otherwise the +0x3B7 flag, the
// virtual at byte offset 0x1B8 and the goal word at +0x1FC decide. The
// container case is written as the tail call it was: MSVC turns it into
// retail's backward jump, which the loop forms of earlier attempts rotated.

typedef bool Bool;

#include "../../../../Include/Common/ThingTemplate.h"

class AIUpdateInterface;

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Object *getContainedBy() const { return m_containedBy; }
private:
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_pad008[0x258 - 0x008];
	AIUpdateInterface *m_ai;
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy;
};

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

Bool AIUpdateInterface::isMoving() const
{
	const Object *obj = getObject();
	if (obj->getTemplate()->m_kindof[0] & (1U << 2))
		return false;

	Object *container = obj->getContainedBy();
	if (container && container->getAI() && !(container->getTemplate()->m_kindof[3] & (1U << 13)))
		return container->getAI()->isMoving();

	if (m_field3B7)
		return true;
	if (isIdle())
		return false;
	else
		return m_field1FC != 0 ? true : false;
}
