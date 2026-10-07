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

#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum StateExitType
{
	EXIT_NORMAL = 0
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Drawable;

// Retail calls the list destructor out of line (the shared pointer-list
// destructor 0x00239AF4); declaring it here keeps /O1 from expanding it.
class DrawableList : public _STL::list<Drawable *>
{
public:
	~DrawableList() throw();
};

class PickAndPlayInfo;

class GameMessage
{
public:
	enum Type
	{
		MSG_BFME2_0x7DB = 0x7DB
	};
};

void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		FILE *log = (FILE *)g_00DFEFF0;
		if (log != 0)
			fprintf(log, text);
	}
}

class PathNode
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
private:
	unsigned char m_pad00[0x0C];
	Coord3D m_pos; // +0x0C
};

class Path
{
public:
	PathNode *getLastNode() const { return m_pathTail; }
private:
	unsigned char m_pad00[0x08];
	PathNode *m_pathTail; // +0x08
};

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

class ThingTemplate
{
public:
	Bool testKindByte117() const { return (m_kindOf[3] & 0x08) != 0; }
private:
	unsigned char m_pad00[0x114];
	unsigned char m_kindOf[12]; // +0x114
};

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

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10();
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual Bool slot17();
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType update();
protected:
	void setAdjustsDestination(Bool b) { m_adjustDestination = b; }
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustDestination; // +0x48
};

class AICowerState : public State
{
public:
	virtual StateReturnType update();
};

StateReturnType AICowerState::update()
{
	Object *goal = getMachine()->getGoalObject();
	if (!goal)
		return STATE_SUCCESS;
	if (goal->isEffectivelyDead() && !goal->getTemplate()->testKindByte117())
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
		DrawableList list;
		list.push_back(obj->getDrawable());
		pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_BFME2_0x7DB, 0);
		return STATE_SUCCESS;
	}
	return STATE_CONTINUE;
}
