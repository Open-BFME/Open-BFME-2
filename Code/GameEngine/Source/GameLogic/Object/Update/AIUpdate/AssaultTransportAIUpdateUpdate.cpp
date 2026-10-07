// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Include
// stlport
//
// AssaultTransportAIUpdate::update (BFME 2), from the Generals Zero Hour
// AssaultTransportAIUpdate.cpp.
//
// Target facts. update is reached through the UpdateModuleInterface at +0x10
// and ends in AIUpdateInterface::update (0x0026E267). The ZH-port unit
// AssaultTransportAIUpdate.cpp builds against the ZH layout and keeps its copy
// present-unmatched. Fields (full object): member IDs +0x3E8 (10), healing
// flags +0x410, new-member flags +0x41A, attack-move goal +0x424, designated
// target +0x430, member count +0x43C, attack-move flag +0x440, attack-object
// flag +0x441, new-occupants flag +0x442 (as the rowed helpers 0x0048F6EE and
// 0x0048F690 and the rowed xfer 0x0048F4AC read them). The ZH helpers are
// rows already: giveFinalOrders 0x0048F6EE, isAttackPointless 0x0048F61A,
// isMemberWounded 0x0048F64E, isMemberHealthy 0x0048F472 and
// retrieveMembers 0x0048F690. Object: AI +0x258, contain +0x250, contained-by
// +0x274, effectively-dead bit 0 of +0x438. AIUpdateInterface: command
// interface +0x20, state machine +0x30, allowed-to-chase +0x3C1,
// getLastCommandSource in vtable slot 143. The contain interface fills a
// two-pointer pair through slot 70, the list in its second word.
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define NULL 0
#define TRUE 1
#define FALSE 0

class ModuleData;
class Object;

// class-gate: allow Coord3D the fighter centroid is built through the ZH zero() and add() members, which keep its dead stores in retail; the canonical data-only header cannot declare them; same three floats
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	void add(const Coord3D *a)
	{
		x += a->x;
		y += a->y;
		z += a->z;
	}
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum ObjectID
{
	INVALID_ID = 0
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum AIStateType
{
	AI_ENTER = 15,
	AI_ATTACK_MOVE_TO = 33
};

#define NO_MAX_SHOTS_LIMIT 0x7fffffff
#define MAX_TRANSPORT_SLOTS 10

typedef _STL::list<Object *> ContainedItemsList;

struct ContainedItemsPair
{
	void *m_unknown00;
	const ContainedItemsList *m_items; // +4
};

#define CONTAIN_GAP10(n) virtual void gap##n##0(); virtual void gap##n##1(); virtual void gap##n##2(); virtual void gap##n##3(); virtual void gap##n##4(); \
	virtual void gap##n##5(); virtual void gap##n##6(); virtual void gap##n##7(); virtual void gap##n##8(); virtual void gap##n##9();

class ContainModuleInterface
{
public:
	CONTAIN_GAP10(0) CONTAIN_GAP10(1) CONTAIN_GAP10(2) CONTAIN_GAP10(3)
	CONTAIN_GAP10(4) CONTAIN_GAP10(5) CONTAIN_GAP10(6)
	virtual void getContainedItemsList(ContainedItemsPair &pair); // slot 70
};

class StateMachine
{
public:
	Object *getGoalObject();
};

class Thing
{
public:
	const Coord3D *getPosition() const { return &m_position; }

private:
	char m_unknown00[0x38];
	Coord3D m_position; // +0x38
};

class AIUpdateInterface;

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Bool isContained() const { return m_containedBy != NULL; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }

private:
	char m_unknown44[0x74 - 0x44];
	ObjectID m_id; // +0x74
	char m_unknown78[0x250 - 0x78];
	ContainModuleInterface *m_contain; // +0x250
	char m_unknown254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	char m_unknown25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
	char m_unknown278[0x438 - 0x278];
	unsigned char m_privateStatus; // +0x438
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
	void aiIdle(CommandSourceType cmdSource);
	void aiExit(Object *objectToExit, CommandSourceType cmdSource);
	void rva0026C347(Object *obj, CommandSourceType cmdSource); // aiEnter
	void rva0026C2D9(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource); // aiAttackObject
	void rva00295A0F(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource); // aiAttackMoveToPosition
};

#define AI_GAP10(n) virtual void aigap##n##0(); virtual void aigap##n##1(); virtual void aigap##n##2(); virtual void aigap##n##3(); virtual void aigap##n##4(); \
	virtual void aigap##n##5(); virtual void aigap##n##6(); virtual void aigap##n##7(); virtual void aigap##n##8(); virtual void aigap##n##9();

class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
public:
	virtual UpdateSleepTime update();
	// Primary vtable slots 1..142 (slot 0 is BehaviorModuleBase's).
	AI_GAP10(0) AI_GAP10(1) AI_GAP10(2) AI_GAP10(3) AI_GAP10(4) AI_GAP10(5) AI_GAP10(6)
	AI_GAP10(7) AI_GAP10(8) AI_GAP10(9) AI_GAP10(10) AI_GAP10(11) AI_GAP10(12) AI_GAP10(13)
	virtual void aigap140(); virtual void aigap141();
	virtual CommandSourceType getLastCommandSource() const; // slot 143

	Int getCurrentStateID() const;
	Bool isMoving() const;
	Object *getGoalObject() const { return m_stateMachine->getGoalObject(); }
	void setAllowedToChase(Bool allow) { m_isAllowedToChase = allow; }

private:
	char m_unknown24[0x30 - 0x24];
	StateMachine *m_stateMachine; // +0x30
	char m_unknown34[0x3C1 - 0x34];
	Bool m_isAllowedToChase; // +0x3C1
};

class AssaultTransportAIUpdate : public AIUpdateInterface
{
public:
	virtual UpdateSleepTime update();

	void Rva0048F6EEHelper(); // giveFinalOrders
	Bool Rva0048F61ACheck(); // isAttackPointless
	Bool rva0048F64E(void *member); // isMemberWounded
	Bool rva0048F472(const Object *member) const; // isMemberHealthy
	void Rva0048F690Helper(); // retrieveMembers

private:
	char m_unknown3C4[0x3E8 - 0x3C4];
	ObjectID m_memberIDs[MAX_TRANSPORT_SLOTS]; // +0x3E8
	Bool m_memberHealing[MAX_TRANSPORT_SLOTS]; // +0x410
	Bool m_newMember[MAX_TRANSPORT_SLOTS]; // +0x41A
	Coord3D m_attackMoveGoalPos; // +0x424
	ObjectID m_designatedTarget; // +0x430
	char m_unknown434[0x43C - 0x434];
	Int m_currentMembers; // +0x43C
	Bool m_isAttackMove; // +0x440
	Bool m_isAttackObject; // +0x441
	Bool m_newOccupantsAreNewMembers; // +0x442
};

// ?update@AssaultTransportAIUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0048F828 914B
UpdateSleepTime AssaultTransportAIUpdate::update( void )
{
	Object *transport = getObject();

	if( transport->isEffectivelyDead() )
	{
		Rva0048F6EEHelper();
		return UPDATE_SLEEP_FOREVER;
	}

	//First removing dead members or members that have been ordered to do something outside of this AI.
	if( m_currentMembers )
	{
		for( int i = 0; i < m_currentMembers; i++ )
		{
			Object *member = TheGameLogic->findObjectByID( m_memberIDs[ i ] );
			AIUpdateInterface *ai = member ? member->getAI() : NULL;
			if( !member || member->isEffectivelyDead() || ai->getLastCommandSource() != CMD_FROM_AI )
			{
				//Member is toast -- so remove him from our list!
				if( m_currentMembers - 1 > i )
				{
					//Move the last slot to this slot to keep array contiguous.
					m_memberIDs[ i ]			= m_memberIDs[ m_currentMembers - 1 ];
					m_memberHealing[ i ]	= m_memberHealing[ m_currentMembers - 1 ];
					m_newMember[ i ]			= m_newMember[ m_currentMembers - 1 ];
				}
				else
				{
					//Just clean out last slot.
					m_memberIDs[ i ]			= INVALID_ID;
					m_memberHealing[ i ]	= FALSE;
					m_newMember[ i ]			= FALSE;
				}
				if( ai )
				{
					ai->setAllowedToChase( FALSE );
				}
				m_currentMembers--;
			}
		}
	}

	//Now add any potentially new members to the group.
	ContainModuleInterface *contain = transport->getContain();
	if( contain )
	{
		ContainedItemsPair items;
		contain->getContainedItemsList( items );
		ContainedItemsList::const_iterator passengerIterator;
		passengerIterator = items.m_items->begin();
		while( passengerIterator != items.m_items->end() )
		{
			Object *passenger = *passengerIterator;
			//Advance to the next iterator
			passengerIterator++;

			//Make sure it isn't in our list already.
			Bool found = FALSE;
			for( int i = 0; i < m_currentMembers; i++ )
			{
				if( passenger->getID() == m_memberIDs[ i ] )
				{
					//He is in the list... so skip him.
					found = TRUE;
					break;
				}
			}
			if( found )
			{
				//Get next passenger.
				continue;
			}

			//It's possible to add members manually -- but if we already have 10 members, then wait!
			if( m_currentMembers < MAX_TRANSPORT_SLOTS )
			{
				//Not in list, so add him!
				m_memberIDs[ m_currentMembers ] = passenger->getID();
				if( passenger->getAI() )
				{
					passenger->getAI()->setAllowedToChase( TRUE );
				}

				//Check if the passenger is wounded below threshhold (if so make sure we heal him before ordering him to fight!)
				if( rva0048F64E( passenger ) )
				{
					m_memberHealing[ m_currentMembers ] = TRUE;
				}
				if( m_newOccupantsAreNewMembers )
				{
					//New members won't eject out until a new attack order is issued.
					m_newMember[ m_currentMembers ] = TRUE;
				}

				m_currentMembers++;
			}
		}
		m_newOccupantsAreNewMembers = TRUE;
	}

	if( Rva0048F61ACheck() )
	{
		aiIdle( CMD_FROM_AI );
		return UPDATE_SLEEP_NONE;
	}

	//Keep track of the average position of all combat units assigned to me.
	Coord3D fighterCentroidPos;
	UnsignedInt fightingMembers = 0;
	fighterCentroidPos.zero();

	//If we're already in the process, reacquire the designated target again... see if
	//it's still alive.
	Object *designatedTarget = TheGameLogic->findObjectByID( m_designatedTarget );
	if( designatedTarget && designatedTarget->isEffectivelyDead() )
	{
		designatedTarget = NULL;
	}
	if( designatedTarget )
	{
		//Look for members not currently attacking this target.
		for( int i = 0; i < m_currentMembers; i++ )
		{
			Object *member = TheGameLogic->findObjectByID( m_memberIDs[ i ] );
			AIUpdateInterface *ai = member ? member->getAI() : NULL;

			if( member && ai )
			{
				Bool contained = member->isContained();
				Bool wounded = rva0048F64E( member );
				if( contained && rva0048F472( member ) && !m_newMember[ i ] )
				{
					//This contained member is healthy so order him to exit to start fighting!
					//New members are exempt!
					ai->aiExit( transport, CMD_FROM_AI );
				}
				if( !contained )
				{
					if( wounded )
					{
						if( ai->getCurrentStateID() != AI_ENTER )
						{
							//Order wounded members back to get healed.
							ai->rva0026C347( transport, CMD_FROM_AI );
						}
					}
					else
					{
						//Increment the number of fighters and their position.
						fighterCentroidPos.add( member->getPosition() );
						fightingMembers++;

						if( !ai->isMoving() )
						{
							if( ai->getGoalObject() != designatedTarget )
							{
								//Okay, this dude is outside and waiting... order him to attack the designated target
								ai->rva0026C2D9( designatedTarget, NO_MAX_SHOTS_LIMIT, CMD_FROM_AI );
							}
						}
					}
				}
			}
		}
	}
	else
	{
		if( m_isAttackMove && getCurrentStateID() != AI_ATTACK_MOVE_TO )
		{
			//Continue to move towards the attackmove area.
			rva00295A0F( &m_attackMoveGoalPos, NO_MAX_SHOTS_LIMIT, CMD_FROM_AI );
		}
		else if( m_isAttackObject )
		{
			Rva0048F690Helper();
		}
	}

	AIUpdateInterface::update();
	return UPDATE_SLEEP_NONE;
}
