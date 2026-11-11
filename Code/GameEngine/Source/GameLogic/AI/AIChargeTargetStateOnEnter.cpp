// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// AIChargeTargetState::onEnter, retail 0x00352E12 (184 bytes): slot 4 of
// the state vtable 0x00C130A8, whose slot-2 getter names the class (the
// rowed constructor 0x00343042 installs it). Donor: Open-BFME-1
// AIChargeTargetState_onEnter.cpp. Fails without an AI or a goal object;
// otherwise clears setAdjustsDestination (+0x48), copies the goal's
// position to the +0x20 goal position and takes the temporary weapon lock
// on the primary slot. BFME 2 replaces the donor's per-unit
// "VoiceStartCharging" audio event with the one-drawable list hand-off of
// AIUpdateInterface_voiceResponses_Rva0026B25A.cpp: message 0x7EA, no
// PickAndPlayInfo. Then the pinned AIInternalMoveToState::onEnter.

#include <list>

// list<Drawable *> takes its nodes from the 12-byte pool at VA 0x00DBA5E0.
// The base constructor (0x00239BB0) and node creator (0x00239BD8) are spelled
// as stlport_list_drawable_base_ctor.cpp and InGameUISelectDrawable.cpp spell
// them, and the destructor (0x00239AF4) is defined once elsewhere, so this
// unit emits no stock allocator copy of them for the link to reject.
class Drawable;
#include "../../../Include/Common/FreelistPool.h"
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL {
template <> __declspec(noinline)
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &__a)
	: _M_node(__a, (_List_node<Drawable *> *)0)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base();
template <> __declspec(noinline) _List_node<Drawable *> *
list<Drawable *>::_M_create_node(Drawable *const &value)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	_Construct(&node->_M_data, value);
	return node;
}
}

#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;


enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum WeaponLockType
{
	NOT_LOCKED,
	LOCKED_TEMPORARILY
};

class Drawable;
class AIUpdateInterface;

#include "../Object/object.h"

// Retail calls the list destructor out of line (the shared pointer-list
// destructor 0x00239AF4); declaring it here keeps /O1 from expanding it.
#include "../../../Include/GameClient/DrawableList.h"

class PickAndPlayInfo;

#include "../../../Include/Common/MessageStream.h"

bool pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"


#include "../../../Include/GameLogic/AIInternalMoveToState.h"

class AIChargeTargetState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType AIChargeTargetState::onEnter()
{
	Object *source = getMachineOwner();
	AIUpdateInterface *ai = source->getAI();
	Object *victim = getMachine()->getGoalObject();
	if (!ai || !victim)
		return STATE_FAILURE;

	m_adjustDestinations = false;
	m_goalPosition = *victim->getPosition();
	source->setWeaponLock(PRIMARY_WEAPON, LOCKED_TEMPORARILY);

	Drawable *drawable = source->getDrawable();
	if (drawable)
	{
		DrawableList list;
		list.push_back(drawable);
		pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_BFME2_0x7EA, 0);
	}

	return AIInternalMoveToState::onEnter();
}
