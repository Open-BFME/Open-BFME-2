// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Evidence: retail 0x0028C819 (54 bytes) is byte-identical to the landed
// BitFlags getSingleBitFromName pair except for the name-table DIR32: it
// reads 0x00DA5F30, whose first entries are DESTROYED, CAN_ATTACK,
// UNDER_CONSTRUCTION (101 names total). Same _strcmpi thunk at 0x00BBA518.

#include <bitset>
#include <string.h>

typedef int Int;
typedef bool Bool;

// BodyStateNames: the retail string table at VA 0xda5f30.
const char *BodyStateNames[101] = {
	"DESTROYED",
	"CAN_ATTACK",
	"UNDER_CONSTRUCTION",
	"UNSELECTABLE",
	"NO_COLLISIONS",
	"NO_ATTACK",
	"AIRBORNE_TARGET",
	"PARACHUTING",
	"REPULSOR",
	"HIJACKED",
	"AFLAME",
	"BURNED",
	"WET",
	"IS_FIRING_WEAPON",
	"IS_BRAKING",
	"STEALTHED",
	"HIDDEN",
	"DETECTED",
	"CAN_STEALTH",
	"SOLD",
	"UNDERGOING_REPAIR",
	"RECONSTRUCTING",
	"IS_ATTACKING",
	"NO_AUTO_ACQUIRE",
	"USING_ABILITY",
	"IS_AIMING_WEAPON",
	"NO_ATTACK_FROM_AI",
	"IGNORING_STEALTH",
	"IS_MELEE_ATTACKING",
	"GUARD_SELECTION",
	"LEASHED_RETURNING",
	"DEATH_1",
	"DEATH_2",
	"DEATH_3",
	"DEATH_4",
	"DEATH_5",
	"CONTESTED",
	"CONTESTING_BUILDING",
	"HORDE_MEMBER",
	"RIDERLESS",
	"RIDER_IS_PILOT",
	"RIDER1",
	"RIDER2",
	"RIDER3",
	"RIDER4",
	"RIDER5",
	"RIDER6",
	"RIDER7",
	"RIDER8",
	"IMMOBILE",
	"FLEE_OFF_MAP",
	"NOT_IN_WORLD",
	"INAUDIBLE",
	"CHANTING",
	"ENRAGED",
	"CREATE_DRAWABLE_WITH_LOW_DETAIL",
	"SINKING",
	"RAMPAGING",
	"INSIDE_GARRISON",
	"DEPLOYED",
	"UNATTACKABLE",
	"ENCLOSED",
	"TEMPORARILY_DEFECTED",
	"TAGGED",
	"DEPLOYING",
	"BLOODTHIRSTY",
	"PORTER_TAGGED",
	"GRAB_AND_DROP",
	"STAND_GROUND",
	"UNCONTROLLABLY_SCARED",
	"SPECIAL_ABILITY_PACKING_UNPACKING_OR_USING",
	"PLEASE_EAT_ME",
	"UPDATING_AI",
	"HUNT_WHEN_IDLE",
	"IGNORE_AI_COMMAND",
	"RUNNING_DOWN_FROM_BEHIND",
	"DO_NOT_SCORE",
	"CAN_NOT_WALK_ON",
	"MARCH_OF_DEATH",
	"DO_NOT_PICK_ME",
	"INHERITED_FROM_ALLY_TEAM",
	"SWITCHED_WEAPONS",
	"END_FIRE_STATE",
	"BOOKENDING",
	"ELVISH_EXPRESSLY",
	"INSIDE_CASTLE",
	"BUILD_BEING_CANCELED",
	"PENDING_CONSTRUCTION",
	"PHANTOM_STRUCTURE",
	"IN_FORMATION_TEMPLATE",
	"IS_LEAVING_FACTORY",
	"MOVING_TO_DISMOUNT",
	"NO_HERO_PROPERTIES",
	"CAN_ENTER_ANYTHING",
	"HOLDING_THE_RING",
	"INVISIBLE_DETECTED_BY_FRIEND",
	"INVISIBLE_DETECTED",
	"WORKER_REPAIRING",
	"ATTACHED",
	"WONT_RIDE_WITH_YOU",
	"COMMAND_BUTTON_TOGGLED",
};

template <size_t NUMBITS>
class BitFlags
{
public:
	static Int getSingleBitFromName( const char *token );

private:
	_STL::bitset<NUMBITS> m_bits;
};

template <size_t NUMBITS>
Int BitFlags<NUMBITS>::getSingleBitFromName( const char *token )
{
	Int i = 0;
	for ( const char *const *name = BodyStateNames; *name; ++name, ++i )
	{
		if ( _strcmpi( *name, token ) == 0 )
			return i;
	}
	return -1;
}

// ?getSingleBitFromName@?$BitFlags@$0GF@@@SAHPBD@Z
template Int BitFlags<101>::getSingleBitFromName( const char *token );
