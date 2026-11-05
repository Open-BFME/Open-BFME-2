// cl: /O1 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Two BFME 2 cower/back-away updates that finish with the one-drawable voice
// hand-off of AIChargeTargetStateOnEnter.cpp (a DrawableList holding the
// owner's drawable, the pinned pickAndPlayUnitVoiceResponse, message 0x7DB,
// no PickAndPlayInfo). Neither has a Zero Hour or Open-BFME-1 update donor;
// both are read from the retail bodies. They need /O1: under /O2 the
// longer bodies stop inlining the list constructor and push_back, while
// /O1 reproduces retail's out-of-line _List_base constructor and insert.
//
//  - AICowerState::update, retail 0x00352BD0 (248 bytes): slot 6 of the
//    AICowerState vtable 0x00C11958 and of AIUncontrollableCower 0x00C12048.
//    Succeeds without a goal or once the goal is effectively dead (+0x438
//    bit 0) unless its template has kind byte +0x117 bit 3; fails without an
//    owner. Only a state whose slot-17 predicate holds (AICowerState's
//    returns true, AIUncontrollableCower's false) voices: the owner's rowed
//    Object::rva0028C264 id must pass the rowed 0x00293249 check, the owner
//    needs an AI, and the rowed AIUpdateInterface::rva002632C7 must be clear.
//  - AIBackAwayState::update, retail 0x00352CC8 (330 bytes): slot 6 of
//    0x00C13050 (rowed onExit and computePath in slots 5 and 17). Raises the
//    owner's model condition bit 65 (rowed notifier), succeeds without a
//    live goal or once done (+0x54). While +0x50 is set and a path is ready
//    it retargets the goal position to the path's last node (critter desync
//    17). A finished base move marks the state done and calls the rowed
//    AIUpdateInterface::rva00262AEA; the voice plays when rva0028C264
//    returns true, which also ends the state.

// Retail calls the statically linked fprintf (0x002CEC42) directly, so the
// CRT declarations STLport pulls in must not be dllimports.
#define _CRTIMP
#include <list>
#include <stdio.h>

// list<Drawable *> takes its nodes from the 12-byte pool at VA 0x00DBA5E0.
// The base constructor (0x00239BB0) and node creator (0x00239BD8) are spelled
// as stlport_list_drawable_base_ctor.cpp and InGameUISelectDrawable.cpp spell
// them, and the destructor (0x00239AF4) is defined once elsewhere, so this
// unit emits no stock allocator copy of them for the link to reject.
class Drawable;
class FreelistPool { public: void *pop(); };
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
template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base() throw(); // no EH state store before retail's calls
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



enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Drawable;

// pickAndPlayUnitVoiceResponse's parameter type. The list a caller hands it
// is a plain list<Drawable *>: retail destroys it with the base destructor
// 0x00239AF4 on the normal path and with the list<Drawable *> destructor
// thunk 0x00239BAB in the unwind funclet.
#include "../../../Include/GameClient/DrawableList.h"

class PickAndPlayInfo;

class GameMessage
{
public:
	enum Type
	{
		MSG_BFME2_0x7DB = 0x7DB
	};
};

bool pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		FILE *log = (FILE *)theLogicRandomLogFile;
		if (log != 0)
			fprintf(log, text);
	}
}

#include "../../../Include/GameLogic/PathNode.h"

#include "../../../Include/GameLogic/PathfindPath.h"

class AIUpdateInterface
{
public:
	void rva00262AEA();
	// The rowed body is named with an int return, but every caller tests
	// only al; the byte view below is that bool read.
	int rva002632C7() const;
	unsigned char rva002632C7Bool() const { return (unsigned char)rva002632C7(); }
	Path *getPath() const { return m_path; }
	Bool getBfmeFlag3B1() const { return m_bfmeFlag3B1; }
private:
	unsigned char m_pad000[0x140];
	Path *m_path; // +0x140
	unsigned char m_pad144[0x3B1 - 0x144];
	Bool m_bfmeFlag3B1; // +0x3B1
};

#include "../../../Include/Common/ThingTemplate.h"

class ConditionBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
private:
	unsigned int m_words[19];
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Drawable *getDrawable() const;
	AIUpdateInterface *getAI() { return m_ai; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Bool rva0028C264(int *id, int kind);
	void rva0028AE6D();
	__forceinline void setModelConditionBit(int bit)
	{
		if (m_conditionBits.test(bit) == 0)
		{
			m_conditionBits.set(bit);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x10C - 0x08];
	ConditionBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus; // +0x438 (bit 0: effectively dead)
};

// The rowed ObjectID check runs on the owner (address-derived class name).
class Rva00293249
{
public:
	Bool rva00293249(ObjectID id);
};

#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"
#include "../../../Include/GameLogic/AIInternalMoveToState.h"

class AICowerState : public State
{
public:
	virtual StateReturnType update();
	virtual Bool slot17(); // slot 17 of 0x00C11958, the first after State's 17 slots
};

StateReturnType AICowerState::update()
{
	Object *goal = getMachine()->getGoalObject();
	if (!goal)
		return STATE_SUCCESS;
	if (goal->isEffectivelyDead() && !((goal->getTemplate()->m_kindof[3] & (1U << 27)) != 0))
		return STATE_SUCCESS;

	Object *obj = getMachineOwner();
	if (!obj)
		return STATE_FAILURE;
	if (!slot17())
		return STATE_CONTINUE;

	Bool voice = false;
	int id;
	if (obj->rva0028C264(&id, 4))
		voice = ((Rva00293249 *)obj)->rva00293249((ObjectID)id);
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return STATE_FAILURE;
	if (voice && ai->rva002632C7Bool())
		voice = false;
	if (voice)
	{
		_STL::list<Drawable *> list;
		list.push_back(obj->getDrawable());
		pickAndPlayUnitVoiceResponse(static_cast<const DrawableList *>(&list), GameMessage::MSG_BFME2_0x7DB, 0);
		return STATE_SUCCESS;
	}
	return STATE_CONTINUE;
}

class AIBackAwayState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
private:
	unsigned char m_pad4C[0x50 - 0x4C];
	Bool m_retargetToPathEnd; // +0x50
	unsigned char m_pad51[0x54 - 0x51];
	Bool m_done; // +0x54
};

StateReturnType AIBackAwayState::update()
{
	Object *obj = getMachineOwner();
	obj->setModelConditionBit(65);
	AIUpdateInterface *ai = obj->getAI();
	Object *goal = getMachine()->getGoalObject();
	if (!goal || goal->isEffectivelyDead() || m_done)
		return STATE_SUCCESS;

	if (m_retargetToPathEnd)
	{
		AIUpdateInterface *objAI = obj->getAI();
		if (objAI->getPath() && !objAI->getBfmeFlag3B1())
		{
			m_goalPosition = *objAI->getPath()->getLastNode()->getPosition();
			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 17");
			m_adjustDestinations = false;
			m_retargetToPathEnd = false;
		}
	}

	if (AIInternalMoveToState::update() != STATE_CONTINUE)
	{
		m_done = true;
		if (ai)
			ai->rva00262AEA();
	}

	int id;
	if (obj->rva0028C264(&id, 4) == true)
	{
		Drawable *draw = obj->getDrawable();
		if (draw)
		{
			_STL::list<Drawable *> list;
			list.push_back(draw);
			pickAndPlayUnitVoiceResponse(static_cast<const DrawableList *>(&list), GameMessage::MSG_BFME2_0x7DB, 0);
		}
		return STATE_SUCCESS;
	}
	return STATE_CONTINUE;
}
