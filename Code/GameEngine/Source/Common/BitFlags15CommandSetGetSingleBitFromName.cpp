// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Evidence: retail 0x003182F3 (54 bytes) is byte-identical to the landed
// BitFlags getSingleBitFromName pair except for the name-table DIR32: it
// reads 0x00DBAA00, whose first entries are NONE, LEADERSHIP, FORMATION
// (15 names total). Same _strcmpi thunk at 0x00BBA518.

#include <bitset>
#include <string.h>

typedef int Int;
typedef bool Bool;

// CommandSetNames: the retail string table at VA 0xdbaa00.
const char *CommandSetNames[15] = {
	"NONE",
	"LEADERSHIP",
	"FORMATION",
	"SPELL",
	"WEAPON",
	"STRUCTURE",
	"LEVEL",
	"BUFF",
	"DEBUFF",
	"STUN",
	"INNATE_ARMOR",
	"INNATE_DAMAGEMULT",
	"INNATE_VISION",
	"INNATE_AUTOHEAL",
	"INNATE_HEALTH",
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
	for ( const char *const *name = CommandSetNames; *name; ++name, ++i )
	{
		if ( _strcmpi( *name, token ) == 0 )
			return i;
	}
	return -1;
}

// ?getSingleBitFromName@?$BitFlags@$0P@@@SAHPBD@Z
template Int BitFlags<15>::getSingleBitFromName( const char *token );
