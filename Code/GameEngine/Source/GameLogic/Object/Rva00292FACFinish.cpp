// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00292FAC@Object@@QBE_NXZ
// finish from 0.93 bank: retail tail branches (87B); bank emitted branchless (84B).
// Object isSelectable/producer-under-construction helper at retail 0x00292FAC 87B.
// TU-scoped private Object view: this file defines only rva00292FAC and does
// not touch the ObjectScriptStatus.cpp view.
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE,
	OBJECT_STATUS_DESTROYED,
	OBJECT_STATUS_CAN_ATTACK,
	OBJECT_STATUS_UNDER_CONSTRUCTION,
	OBJECT_STATUS_UNSELECTABLE,
	OBJECT_STATUS_NO_COLLISIONS,
	OBJECT_STATUS_NO_ATTACK,
	OBJECT_STATUS_AIRBORNE_TARGET,
	OBJECT_STATUS_PARACHUTING,
	OBJECT_STATUS_REPULSOR,
	OBJECT_STATUS_HIJACKED,
	OBJECT_STATUS_AFLAME,
	OBJECT_STATUS_BURNED,
	OBJECT_STATUS_WET,
	OBJECT_STATUS_IS_FIRING_WEAPON,
	OBJECT_STATUS_BRAKING,
	OBJECT_STATUS_STEALTHED,
	OBJECT_STATUS_DETECTED,
	OBJECT_STATUS_CAN_STEALTH,
	OBJECT_STATUS_SOLD,
	OBJECT_STATUS_UNDERGOING_REPAIR,
	OBJECT_STATUS_RECONSTRUCTING,
	OBJECT_STATUS_MASKED,
	OBJECT_STATUS_IS_ATTACKING,
	OBJECT_STATUS_IS_USING_ABILITY,
	OBJECT_STATUS_IS_AIMING_WEAPON,
	OBJECT_STATUS_NO_ATTACK_FROM_AI,
	OBJECT_STATUS_IGNORING_STEALTH,
	OBJECT_STATUS_IS_CARBOMB,
	OBJECT_STATUS_DECK_HEIGHT_OFFSET,
	OBJECT_STATUS_RIDER1,
	OBJECT_STATUS_RIDER2,
	OBJECT_STATUS_RIDER3,
	OBJECT_STATUS_RIDER4,
	OBJECT_STATUS_RIDER5,
	OBJECT_STATUS_RIDER6,
	OBJECT_STATUS_RIDER7,
	OBJECT_STATUS_RIDER8,
	OBJECT_STATUS_FAERIE_FIRE,
	OBJECT_STATUS_MISSILE_KILLING_SELF,
	OBJECT_STATUS_REASSIGN_PARKING,
	OBJECT_STATUS_BOOBY_TRAPPED,
	OBJECT_STATUS_IMMOBILE,
	OBJECT_STATUS_DISGUISED,
	OBJECT_STATUS_DEPLOYED,

	OBJECT_STATUS_COUNT
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct ThingTemplate
{
	unsigned char m_pad00[ 0x108 ];
	unsigned char m_byte108; // +0x108, 0x80 STRUCTURE bit per ObjectIsSelectable
	unsigned char m_pad109[ 0x115 - 0x109 ];
	unsigned char m_byte115; // +0x115, 0x20 producer check
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	Bool testStatus( ObjectStatusTypes bit ) const;
	Bool isSelectable( void ) const;
	Bool rva00292FAC( void ) const;

private:
	unsigned char m_pad00[ 4 ]; // +0x00 vtable
	ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[ 0x78 - 0x08 ]; // +0x08..0x77
	ObjectID m_producerID; // +0x78
	unsigned char m_pad7C[ 0x437 - 0x7C ]; // +0x7C..+0x436
};

Bool Object::rva00292FAC( void ) const
{
	ObjectID producerID = m_producerID;
	if( producerID != INVALID_OBJECT_ID )
	{
		Object *producer = TheGameLogic->findObjectByID( producerID );
		if( producer != 0 )
		{
			if( ( producer->m_template->m_byte115 & 0x20 ) != 0 )
			{
				if( producer->testStatus( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
					return false;
			}
		}
	}
	return isSelectable() && !( m_template->m_byte108 & 0x80 );
}