// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Object script-status and disabled-state helpers at retail 0x00291C9B+.
// Decoded from retail bytes (all verified):
// - setDisabledUntil pin (0x00290114) carries (DisabledType, frame); the
//   FOREVER literal below is 0x3FFFFFFF (UPDATE_SLEEP_FOREVER).
// - setScriptStatus bit layout (ObjectScriptStatusBit) and the DISABLED
//   enumerators (9/10) match reference/shims/bfmeobject/GameLogic/Object.h;
//   the retail offsets below (+0x437 status, +0x4C4 partition) are read from
//   the binary and supersede the shim's stale notes.

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum DisabledType
{
	DISABLED_MIN = 0,
	DISABLED_SCRIPT_DISABLED = 9,
	DISABLED_SCRIPT_UNDERPOWERED = 10
};

enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_DISABLED = 0x01,
	OBJECT_STATUS_SCRIPT_UNPOWERED = 0x02
};

// Saved status bits (Zero Hour donor ObjectStatusTypes.h; values are inert
// in this TU -- setStatus forwards its arguments without comparing them).
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

// Native 0x23DA79 consumes two arguments (RET8) and builds four words.
// The boolean is already on the outer 0x28CDEB call stack while the mask
// is constructed; it belongs to that setter, whose own RET8 consumes it.
class Rva0023DA79
{
public:
	Rva0023DA79 *rva0023DA79(int ignored, int index);
	unsigned int m_bits[4];
};

class Rva00346BC0
{
public:
	unsigned int m_words[4];
};

class PartitionData
{
public:
	void makeDirty( void );
};

class Object
{
public:
	void setDisabledUntil( DisabledType type, UnsignedInt frame );
	void setDisabled( DisabledType type );
	Bool clearDisabled( DisabledType type );
	void makeDirty( void );
	void setScriptStatus( ObjectScriptStatusBit bit, Bool set );
	void setStatus( ObjectStatusTypes bit, Bool flag );
	Bool rva00292ED0( DisabledType type );
	void rva00292EB3( DisabledType type );
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);

private:
	unsigned char m_pad00[ 0x1F8 ];
	int m_unk1F8[ 11 ]; // +0x1F8 dec-indexed by DisabledType; 11*4 ends at 0x224 upgrades
	unsigned char m_pad224[ 0x437 - 0x224 ];
	unsigned char m_scriptStatus;
	unsigned char m_pad438[ 0x4C4 - 0x438 ];
	PartitionData *m_partitionData;
};

// ?setDisabled@Object@@QAEXW4DisabledType@@@Z
void Object::setDisabled( DisabledType type )
{
	setDisabledUntil( type, 0x3FFFFFFF );
}

// ?makeDirty@Object@@QAEXXZ
void Object::makeDirty( void )
{
	if( m_partitionData )
		m_partitionData->makeDirty();
}


// ?setStatus@Object@@QAEXW4ObjectStatusTypes@@_N@Z
void Object::setStatus( ObjectStatusTypes bit, Bool flag )
{
	Rva0023DA79 mask;
	rva0028CDEB(*reinterpret_cast<const Rva00346BC0 *>(mask.rva0023DA79(0, (int)bit)), flag);
}

// ?setScriptStatus@Object@@QAEXW4ObjectScriptStatusBit@@_N@Z
void Object::setScriptStatus( ObjectScriptStatusBit bit, Bool set )
{
	UnsignedInt oldScriptStatus = m_scriptStatus;

	if( set )
	{
		m_scriptStatus |= bit;
	}
	else
	{
		m_scriptStatus &= ~bit;
	}

	if( m_scriptStatus != oldScriptStatus )
	{
		if( (m_scriptStatus & OBJECT_STATUS_SCRIPT_DISABLED) != (oldScriptStatus & OBJECT_STATUS_SCRIPT_DISABLED) )
		{
			makeDirty();
			if( m_scriptStatus & OBJECT_STATUS_SCRIPT_DISABLED )
			{
				setDisabled( DISABLED_SCRIPT_DISABLED );
			}
			else
			{
				clearDisabled( DISABLED_SCRIPT_DISABLED );
			}
		}
		if( (m_scriptStatus & OBJECT_STATUS_SCRIPT_UNPOWERED) != (oldScriptStatus & OBJECT_STATUS_SCRIPT_UNPOWERED) )
		{
			makeDirty();
			if( m_scriptStatus & OBJECT_STATUS_SCRIPT_UNPOWERED )
			{
				setDisabled( DISABLED_SCRIPT_UNDERPOWERED );
			}
			else
			{
				clearDisabled( DISABLED_SCRIPT_UNDERPOWERED );
			}
		}
	}
}

// ?rva00292ED0@Object@@QAE_NW4DisabledType@@@Z
Bool Object::rva00292ED0( DisabledType type )
{
	if( --m_unk1F8[ type ] == 0 )
		return clearDisabled( type );
	return false;
}

void Object::rva00292EB3( DisabledType type )
{
	if( m_unk1F8[ type ] == 0 )
		setDisabled( type );
	++m_unk1F8[ type ];
}

template <int N>
class BitFlags
{
public:
	unsigned int m_bits[(N + 31) / 32];
};

// placement unverified: no rowed DIR32 site yet; ZH ObjectStatusMaskType starts clear.
BitFlags<45> OBJECT_STATUS_MASK_NONE = { { 0, 0 } };
