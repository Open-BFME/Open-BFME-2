// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?destroyObject@GameLogic@@QAEXPAVObject@@@Z, retail 0x00242C09 (125 bytes).
//
// Deferred-destruction sequence ported from Open-BFME-1
// Code/GameEngine/Source/GameLogic/System/GameLogicDestroyObject.cpp with
// BFME2 layout repairs: status bit0 at Object+0x94, module array at +0x244
// with the behavior interface EMBEDDED at +0xC (vfptr, lea form), AI at
// +0x258 with setLocomotorGoalNone at virtual slot 136 (+0x220), and the
// destruction list at GameLogic+0x108. Callee pins all pre-derived:
// setStatus 0x23DB0E, destroyPath 0x262A8A, list push_back 0x1EC03C,
// onDestroy 0x28FC1D.

#include <list>

class Object;
// The kept Object-pointer node factory is retail's dedicated-freelist body
// (0x001EB9AC), not the header's generic allocator. Emit that body so this
// TU's copy is identical to the one Player.cpp provides.
#include "../../../Include/Common/FreelistPool.h"
extern FreelistPool g_freelistPool00DB8FEC;
namespace _STL {
template <> inline __declspec(noinline)
_List_node<Object *> *list<Object *, allocator<Object *> >::_M_create_node(Object *const &value)
{
    _List_node<Object *> *node = (_List_node<Object *> *)g_freelistPool00DB8FEC.pop();
    Object **valuePtr = (Object **)((char *)node + 8);
    if (valuePtr)
        *valuePtr = value;
    return node;
}
}

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class DestroyModuleInterface
{
public:
	virtual void onDestroy(void);
};

#include "../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../../Include/GameLogic/PathfindPath.h"

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool flag);
	void onDestroy(void);
	char m_pad00[0x94];
	unsigned char m_statusByte0;
	char m_pad95[0x244 - 0x95];
	BehaviorModule **m_modules;
	char m_pad248[0x258 - 0x248];
	AIUpdateInterface *m_ai;
};

class GameLogic
{
public:
	char m_pad00[0x108];
	_STL::list<Object *> m_objectsToDestroy;
	void destroyObject(Object *obj);
};

void GameLogic::destroyObject(Object *obj)
{
	if (!obj || (obj->m_statusByte0 & 1))
		return;
	for (BehaviorModule **behaviorModule = obj->m_modules; *behaviorModule; ++behaviorModule)
	{
		// Retail dispatches slot 6 at +0x0C; use the embedded interface by
		// reference to preserve its non-null adjustment.
		BehaviorModuleInterface &interface = **behaviorModule;
		DestroyModuleInterface *destroy = static_cast<DestroyModuleInterface *>(interface.slot06());
		if (destroy)
			destroy->onDestroy();
	}
	obj->setStatus(OBJECT_STATUS_NONE, true);
	AIUpdateInterface *ai = obj->m_ai;
	if (ai)
	{
		ai->setLocomotorGoalNone();
		ai->destroyPath();
	}
	m_objectsToDestroy.push_back(obj);
	obj->onDestroy();
}

// ?destroyPath@AIUpdateInterface@@QAEXXZ @0x00262A8A
void AIUpdateInterface::destroyPath(void)
{
	if (m_path)
		delete m_path;
	m_path = 0;
	m_field3B1 = false;
	m_field3B8 = false;
	m_field3B2 = false;
	setLocomotorGoalNone();
}
