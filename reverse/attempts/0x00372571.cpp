// ?rva00372571@AIGroup@@QAEXPBUCoord3D@@@Z
// partial score=0.99 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva00372571@AIGroup@@QAEXPAURva00372571Params@@H@Z @0x00372571 1432B
//
// NEAR draft (seqdiff 0.9978; 1432B like retail): every instruction matches
// except the allocator temporary of the pooled list<Object *>: retail passes
// lea eax,[ebp+0xF] (byte above the live cmdSource slot) while cl gives the
// named allocator [ebp-0x18]; with an unnamed temporary cl instead takes
// [ebp+0xB] and moves the list to [ebp-0x18] (retail list at [ebp+8]).
// WorldBuilder twin 0xEE4170 in AIGroup.cpp (line 2156 random call) gives
// the order: click-to-gather tighten test, the formation-gather dispatch
// 0x003724B8, removeInvalidObjectsFromGroup, the airborne tighten veto,
// tighten when under 2000 cells, then a formation slot walk (FormationAssistant
// 0x00423A75 / 0x00424E77 / 0x0042245F / optimizeUnits 0x0042550E / delete
// 0x00423FBD) or a sorted distance walk, and the per-unit stealth mood delay
// and move dispatch.
// Needs: getMinMaxAndCenter (0x0036D14F) defined earlier in this unit (retail
// calls recompute without reloading ECX; the copy here is byte-exact 374B);
// pins for 0x00424E77 0x0042245F 0x0042550E; ScaleRect2D and
// Coord3DInsideRect2D spelled with the canonical class Coord2D.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Coord2D.h"
#include "../../Common/GameLogicObjectLookupView.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define TRUE true
#define FALSE false

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_STEALTHED = 0x0F,
	OBJECT_STATUS_DETECTED = 0x11,
	OBJECT_STATUS_CAN_STEALTH = 0x12,
	OBJECT_STATUS_IN_FORMATION_MOVE = 0x59
};

enum IterOrderType
{
	ITER_SORTED_NEAR_TO_FAR = 1
};

class Player;
class Rva001EB130Holder;

class AIModuleData
{
public:
	char m_pad00[0x1C];
	UnsignedInt m_autoAcquireEnemiesWhenIdle; // +0x1C
};

class AICommandInterface
{
public:
	void rva0036EBB8(Object *target, CommandSourceType cmdSource);
	void aiFollowPathAppend(const Coord3D *pos, CommandSourceType cmdSource);
	void aiMoveToPositionAmphibious(const Coord3D *pos, CommandSourceType cmdSource);
	void aiAttackMoveToPositionAndFaceDirection(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource, Real angle);
	void aiMoveToPositionAndFaceDirection(const Coord3D *pos, CommandSourceType cmdSource, Real angle);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	virtual void p000(); virtual void p001(); virtual void p002(); virtual void p003();
	virtual void p004(); virtual void p005(); virtual void p006(); virtual void p007();
	virtual void p008(); virtual void p009(); virtual void p010(); virtual void p011();
	virtual void p012(); virtual void p013(); virtual void p014(); virtual void p015();
	virtual void p016(); virtual void p017(); virtual void p018(); virtual void p019();
	virtual void p020(); virtual void p021(); virtual void p022(); virtual void p023();
	virtual void p024(); virtual void p025(); virtual void p026(); virtual void p027();
	virtual void p028(); virtual void p029(); virtual void p030(); virtual void p031();
	virtual void p032(); virtual void p033(); virtual void p034(); virtual void p035();
	virtual void p036(); virtual void p037(); virtual void p038(); virtual void p039();
	virtual void p040(); virtual void p041(); virtual void p042(); virtual void p043();
	virtual void p044(); virtual void p045(); virtual void p046(); virtual void p047();
	virtual void p048(); virtual void p049(); virtual void p050(); virtual void p051();
	virtual void p052(); virtual void p053(); virtual void p054(); virtual void p055();
	virtual void p056(); virtual void p057(); virtual void p058(); virtual void p059();
	virtual void p060(); virtual void p061(); virtual void p062(); virtual void p063();
	virtual void p064(); virtual void p065(); virtual void p066(); virtual void p067();
	virtual void p068(); virtual void p069(); virtual void p070(); virtual void p071();
	virtual void p072(); virtual void p073(); virtual void p074(); virtual void p075();
	virtual void p076(); virtual void p077(); virtual void p078(); virtual void p079();
	virtual void p080(); virtual void p081(); virtual void p082(); virtual void p083();
	virtual void p084(); virtual void p085(); virtual void p086(); virtual void p087();
	virtual void p088(); virtual void p089(); virtual void p090(); virtual void p091();
	virtual void p092(); virtual void p093(); virtual void p094(); virtual void p095();
	virtual void p096(); virtual void p097(); virtual void p098(); virtual void p099();
	virtual void p100(); virtual void p101(); virtual void p102(); virtual void p103();
	virtual void p104(); virtual void p105(); virtual void p106(); virtual void p107();
	virtual void p108(); virtual void p109(); virtual void p110(); virtual void p111();
	virtual void p112(); virtual void p113(); virtual void p114(); virtual void p115();
	virtual void p116(); virtual void p117(); virtual void p118(); virtual void p119();
	virtual void p120(); virtual void p121(); virtual void p122(); virtual void p123();
	virtual void p124(); virtual void p125(); virtual void p126(); virtual void p127();
	virtual void p128(); virtual void p129(); virtual void p130(); virtual void p131();
	virtual void p132(); virtual void p133(); virtual void p134(); virtual void p135();
	virtual void p136();
	virtual Bool isDoingGroundMovement() const; // +0x224

	void rva0026304D(UnsignedInt frame);
	void ignoreObstacle(const Object *obj);
	Bool canAutoAcquire() const { return m_data->m_autoAcquireEnemiesWhenIdle != 0; }
	Bool canAutoAcquireWhileStealthed() const { return (m_data->m_autoAcquireEnemiesWhenIdle & 2) != 0; }
	AICommandInterface *getCommands() { return &m_commands; }

	const AIModuleData *m_data; // +0x04
	char m_pad08[0x20 - 0x08];
	AICommandInterface m_commands; // +0x20
};

class StealthModuleData
{
public:
	char m_pad00[0x08];
	UnsignedInt m_stealthDelay; // +0x08
};

class Rva00373EC6
{
public:
	UnsignedInt getStealthDelay() const { return m_data->m_stealthDelay; }

	char m_pad00[0x04];
	const StealthModuleData *m_data; // +0x04
};

class ThingTemplate
{
public:
	char m_pad000[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
};

struct DisabledFlags
{
	unsigned char m_bits[4];
	__forceinline Bool test(Int bit) const { return (m_bits[bit >> 3] & (1 << (bit & 7))) != 0; }
};

class Object
{
public:
	void rva0028AD32();
	Bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, Bool set);
	Bool rva0028F518();
	Rva00373EC6 *rva0028F4BC();
	Bool isAbleToAttack() const;
	Bool rva0028ECDB(const Coord3D *pos) const;

	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Bool isDisabledHeld() const { return m_disabled.test(3); }
	Bool isImmobile() const { return (m_template->m_kindOf[0] & 4) != 0; }
	void setFormationID(UnsignedInt id) { m_formationID = id; }
	void setFormationOffset(const Coord2D *offset) { m_formationOffset = *offset; }
	void setUserDestination(const Coord2D *dest) { m_userDestination = *dest; }

	char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_position; // +0x38
	char m_pad044[0x1C8 - 0x44];
	DisabledFlags m_disabled; // +0x1C8
	char m_pad1CC[0x258 - 0x1CC];
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x31C - 0x25C];
	Coord2D m_userDestination; // +0x31C
	char m_pad324[0x410 - 0x324];
	UnsignedInt m_formationID; // +0x410
	Coord2D m_formationOffset; // +0x414
};

class ObjectIterator
{
public:
	virtual ~ObjectIterator();
	virtual Object *first() = 0;
	virtual Object *next() = 0;
};

class SimpleObjectIterator : public ObjectIterator
{
public:
	SimpleObjectIterator();
	virtual Object *first();
	virtual Object *next();
	void insert(Object *obj, Real numeric);
	void sort(IterOrderType order);

private:
	unsigned char m_pad04[0x3C - 0x04];
};

class GlobalData
{
public:
	char m_pad000[0xB60];
	Real m_groupMoveClickToGatherFactor; // +0xB60
};

extern GlobalData *TheGlobalData;

struct AIData
{
	char m_pad[0xBD];
	bool m_flagBD; // +0xBD
};

class AI
{
public:
	const AIData *getAiData() const { return m_aiData; }

private:
	char m_pad[0x18];
	AIData *m_aiData; // +0x18
};

extern AI *TheAI;
extern GameLogic *TheGameLogic;

// One formation slot: object id at +0x04 and its offset at +0x18.
struct FormationSlot
{
	char m_pad00[0x04];
	ObjectID m_id; // +0x04
	char m_pad08[0x18 - 0x08];
	Coord2D m_offset; // +0x18
};

class Formation
{
public:
	void rva0042245F(Real angle);
	void optimizeUnits(const Coord3D *pos);

	FormationSlot *m_begin;
	FormationSlot *m_end;
};

class FormationAssistant
{
public:
	Bool getValidObjectList(Rva001EB130Holder *members, Player *player, Rva001EB130Holder *valid);
	Formation *rva00424E77(Int formationType, Rva001EB130Holder *objects, const Coord3D *pos);
};

namespace _STL
{
template <class _Tp> class char_traits;
template <class _Tp> class allocator
{
public:
	allocator() {}
};
template <class _Tp, class _Traits, class _Alloc> class basic_string;
template <class _Tp, class _Alloc> class _List_base
{
public:
	_List_base(const _Alloc &a);
	void *_M_node;
};
}

class Rva00423FBDThis
{
public:
	void Delete(_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *p);
};

class Rva0022AD10Subsystem;
extern Rva0022AD10Subsystem *TheFormationAssistant;

// The pooled list<Object *> body: its out-of-line ~_List_base is 0x001EB769
// and the unwind funclet calls the out-of-line complete dtor 0x001EB940.
class Gen_uwm_001eb769
{
public:
	~Gen_uwm_001eb769();
};

class Rva001EB940 : public _STL::_List_base<Object *, _STL::allocator<Object *> >
{
public:
	__forceinline explicit Rva001EB940(const _STL::allocator<Object *> &a) : _STL::_List_base<Object *, _STL::allocator<Object *> >(a) {}
	~Rva001EB940() { ((Gen_uwm_001eb769 *)this)->~Gen_uwm_001eb769(); }
};

struct Rva00372571Params
{
	const Coord3D *m_pos; // +0x00
	bool m_addWaypoint; // +0x04
	Object *m_ignoreObstacle; // +0x08
	Object *m_target; // +0x0C
	const Real *m_facing; // +0x10
	Int m_formationType; // +0x14
	Player *m_player; // +0x18
	bool m_attackMove; // +0x1C
};

struct Rva0036D7A6Outer;

class BfmeC986
{
public:
	char rva003724B8(int pos, int cmdSource, int a, int ignore, int b);
};

void ScaleRect2D(Coord2D *tl, Coord2D *br, Real scaleFactor);
Bool Coord3DInsideRect2D(const Coord3D *inputPoint, const Coord2D *tl, const Coord2D *br);
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
extern int g_Va00DBA4E4;

struct ObjectListNode
{
	ObjectListNode *m_next;
	ObjectListNode *m_prev;
	Object *m_data;
};

// The member list walk as STLport's list<Object *>::iterator spells it.
struct ObjectListIterator
{
	ObjectListNode *m_node;
	ObjectListIterator() {}
	ObjectListIterator(ObjectListNode *node) : m_node(node) {}
	Object *&operator*() const { return m_node->m_data; }
	ObjectListIterator &operator++() { m_node = m_node->m_next; return *this; }
	bool operator!=(const ObjectListIterator &o) const { return m_node != o.m_node; }
};

class AIGroup
{
public:
	Bool getMinMaxAndCenter(Coord2D *min, Coord2D *max, Coord3D *center);
	Bool removeInvalidObjectsFromGroup(Rva0036D7A6Outer *params);
	void groupTightenToPosition(const Coord3D *pos, bool addWaypoint, CommandSourceType cmdSource);
	static void computeIndividualDestination(Coord3D *dest, const Coord3D *groupDest, Object *obj,
		const Coord3D *center, const Real *facing, Int mode);
	void rva00372571(Rva00372571Params *params, int cmdSource);

private:
	void recompute();

	ObjectListIterator begin() const { return ObjectListIterator(m_head->m_next); }
	ObjectListIterator end() const { return ObjectListIterator(m_head); }

	UnsignedInt size() const
	{
		UnsignedInt result = distance(begin(), end());
		return result;
	}

	static Int distance(const ObjectListIterator &first, const ObjectListIterator &last)
	{
		Int n = 0;
		ObjectListIterator it(first);
		while (it != last)
		{
			++it;
			++n;
		}
		return n;
	}

	char m_pad00[0x04];
	ObjectListNode *m_head; // +0x04
	char m_pad08[0x0C - 0x08];
	bool m_dirty; // +0x0C
};

Bool AIGroup::getMinMaxAndCenter(Coord2D *min, Coord2D *max, Coord3D *center)
{
	Int count = 0;
	min->x = 1e10f;
	max->x = -1e10f;
	min->y = 1e10f;
	max->y = -1e10f;
	center->x = 0.0f;
	center->y = 0.0f;
	center->z = 0.0f;

	ObjectListIterator i;
	UnsignedInt id = 0;
	for (i = begin(); i != end(); ++i) {
		if ((*i)->isDisabledHeld()) {
			continue;
		}
		AIUpdateInterface *ai = (*i)->getAI();
		if (ai) {
			const Coord3D *objPos = (*i)->getPosition();
			center->x += objPos->x;
			center->y += objPos->y;
			center->z += objPos->z;

			min->x = min->x > objPos->x ? objPos->x : min->x;
			max->x = max->x < objPos->x ? objPos->x : max->x;
			min->y = min->y > objPos->y ? objPos->y : min->y;
			max->y = max->y < objPos->y ? objPos->y : max->y;
			UnsignedInt curID = (*i)->m_formationID;
			if (count == 0) {
				id = curID;
			} else {
				if (id == 0) {
					id = 0;
				}
			}

			count++;
		}
	}

	center->x /= count;
	center->y /= count;
	center->z /= count;
	Bool isFormation = (id != 0);
	if (count < 2)
		isFormation = false;
	return isFormation;
}

void AIGroup::rva00372571(Rva00372571Params *params, int cmdSource)
{
	Coord3D center;
	Coord2D min;
	Coord2D max;
	Coord3D dest;
	Bool tightenGroup = FALSE;

	Bool isFormation = getMinMaxAndCenter(&min, &max, &center);
	isFormation = FALSE;
	if (params->m_addWaypoint)
		isFormation = FALSE;
	if (m_dirty)
		recompute();

	if (!isFormation && params->m_target == 0 && cmdSource == CMD_FROM_PLAYER
		&& TheGlobalData->m_groupMoveClickToGatherFactor > 0.0f)
	{
		ScaleRect2D(&min, &max, TheGlobalData->m_groupMoveClickToGatherFactor);
		if (Coord3DInsideRect2D(params->m_pos, &min, &max))
			tightenGroup = TRUE;
	}

	Real numUnits = (Real)size();
	if (numUnits > 1.0f && !tightenGroup && !params->m_addWaypoint && params->m_target == 0
		&& cmdSource == CMD_FROM_PLAYER && params->m_formationType == -1 && TheAI->getAiData()->m_flagBD)
	{
		if (((BfmeC986 *)this)->rva003724B8((int)params->m_pos, cmdSource, 0, (int)params->m_ignoreObstacle, 1))
			return;
	}

	if (!removeInvalidObjectsFromGroup((Rva0036D7A6Outer *)params))
		return;

	ObjectListIterator i;
	if (tightenGroup || isFormation)
	{
		for (i = begin(); i != end(); ++i)
		{
			AIUpdateInterface *ai = (*i)->getAI();
			if (ai && !ai->isDoingGroundMovement())
			{
				tightenGroup = FALSE;
				isFormation = FALSE;
			}
		}
	}

	if (tightenGroup)
	{
		isFormation = FALSE;
		if (!params->m_addWaypoint)
		{
			Int dx = (max.x - min.x) / 10.0f;
			Int dy = (max.x - min.x) / 10.0f;
			Int cells = dx * dy;
			if (cells < 2000)
			{
				groupTightenToPosition(params->m_pos, false, (CommandSourceType)cmdSource);
				return;
			}
		}
	}

	SimpleObjectIterator *iter = new SimpleObjectIterator;
	if (params->m_formationType != -1)
	{
		_STL::allocator<Object *> alloc;
		Rva001EB940 objList(alloc);
		if (((FormationAssistant *)TheFormationAssistant)->getValidObjectList(
				(Rva001EB130Holder *)&m_head, params->m_player, (Rva001EB130Holder *)&objList))
		{
			Real angle = *params->m_facing;
			Formation *formation = ((FormationAssistant *)TheFormationAssistant)->rva00424E77(
				params->m_formationType, (Rva001EB130Holder *)&objList, params->m_pos);
			if (formation)
			{
				formation->rva0042245F(angle);
				formation->optimizeUnits(params->m_pos);
				for (FormationSlot *slot = formation->m_begin; slot != formation->m_end; ++slot)
				{
					Coord2D *offset = &slot->m_offset;
					Object *obj = TheGameLogic->findObjectByID(slot->m_id);
					if (obj)
					{
						obj->setFormationOffset(offset);
						if (obj->isDisabledHeld())
							continue;
						if (obj->isImmobile())
							continue;
						if (obj->getAI() == 0)
							continue;
						obj->rva0028AD32();
						iter->insert(obj, 0.0f);
					}
				}
				((Rva00423FBDThis *)TheFormationAssistant)->Delete(
					(_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *)formation);
			}
		}
	}
	else
	{
		for (i = begin(); i != end(); ++i)
		{
			Real dx, dy;
			Object *obj = *i;
			if (obj->isDisabledHeld())
				continue;
			if (obj->isImmobile())
				continue;
			if (obj->getAI() == 0)
				continue;
			Coord3D unitPos;
			const Coord3D *from = obj->getPosition();
			unitPos.x = from->x;
			unitPos.y = from->y;
			unitPos.z = from->z;
			obj->rva0028AD32();
			dx = unitPos.x - params->m_pos->x;
			dy = unitPos.y - params->m_pos->y;
			Real adjust = 0;
			iter->insert((*i), adjust + dx * dx + dy * dy);
		}
		iter->sort(ITER_SORTED_NEAR_TO_FAR);
	}

	Bool firstUnit = TRUE;
	Int moveType = isFormation;
	if (params->m_formationType != -1)
		moveType = 2;

	Object *theUnit;
	for (theUnit = iter->first(); theUnit; theUnit = iter->next())
	{
		Coord3D goalPos;
		goalPos.x = params->m_pos->x;
		goalPos.y = params->m_pos->y;
		goalPos.z = params->m_pos->z;
		theUnit->setFormationID(0);
		AIUpdateInterface *ai = theUnit->getAI();
		if (firstUnit)
		{
			if (isFormation)
			{
				Coord2D v = theUnit->m_formationOffset;
				goalPos.x -= v.x;
				goalPos.y -= v.y;
			}
			else
			{
				center = *theUnit->getPosition();
			}
			firstUnit = FALSE;
		}
		if (moveType == 2)
			theUnit->setStatus(OBJECT_STATUS_IN_FORMATION_MOVE, TRUE);
		else
			theUnit->setStatus(OBJECT_STATUS_IN_FORMATION_MOVE, FALSE);
		computeIndividualDestination(&dest, &goalPos, theUnit, &center, params->m_facing, moveType);

		if (cmdSource == CMD_FROM_PLAYER && theUnit->testStatus(OBJECT_STATUS_CAN_STEALTH) && ai->canAutoAcquire())
		{
			if (!theUnit->rva0028F518() && !theUnit->testStatus(OBJECT_STATUS_STEALTHED)
				&& !theUnit->testStatus(OBJECT_STATUS_DETECTED))
			{
				if (!ai->canAutoAcquireWhileStealthed())
				{
					Rva00373EC6 *stealth = theUnit->rva0028F4BC();
					if (stealth)
					{
						UnsignedInt stealthFrames = stealth->getStealthDelay();
						UnsignedInt randomFrames = GetGameLogicRandomValue(0, g_Va00DBA4E4,
							"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIGroup.cpp", 2156);
						ai->rva0026304D(TheGameLogic->getFrame() + stealthFrames + randomFrames);
					}
				}
			}
		}

		if (params->m_ignoreObstacle)
			ai->ignoreObstacle(params->m_ignoreObstacle);

		if (params->m_target)
			ai->getCommands()->rva0036EBB8(params->m_target, (CommandSourceType)cmdSource);
		else if (params->m_addWaypoint)
			ai->getCommands()->aiFollowPathAppend(&dest, (CommandSourceType)cmdSource);
		else if (theUnit->rva0028ECDB(&goalPos))
		{
			Coord2D userDest;
			userDest.x = params->m_pos->x;
			userDest.y = params->m_pos->y;
			theUnit->setUserDestination(&userDest);
			ai->getCommands()->aiMoveToPositionAmphibious(&dest, (CommandSourceType)cmdSource);
		}
		else if (moveType == 2 && params->m_facing)
		{
			if (params->m_attackMove && theUnit->isAbleToAttack())
				ai->getCommands()->aiAttackMoveToPositionAndFaceDirection(&dest, 0x7FFFFFFF, (CommandSourceType)cmdSource, *params->m_facing);
			else
				ai->getCommands()->aiMoveToPositionAndFaceDirection(&dest, (CommandSourceType)cmdSource, *params->m_facing);
		}
		else
			ai->getCommands()->aiMoveToPosition(&dest, (CommandSourceType)cmdSource);
	}

	::delete iter;
}
