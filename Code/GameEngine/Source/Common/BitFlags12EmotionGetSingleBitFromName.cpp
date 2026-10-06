// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Evidence: retail 0x004DC696 (54 bytes) is byte-identical to the landed
// BitFlags getSingleBitFromName pair except for the name-table DIR32: it
// reads 0x00DBA9C8, whose first entries are TAUNT, CHEER, HERO_CHEER
// (12 names total). Same _strcmpi thunk at 0x00BBA518.

#include <bitset>
#include <string.h>

typedef int Int;
typedef bool Bool;

// EmotionNames: the retail string table at VA 0xdba9c8.
const char *EmotionNames[12] = {
	"TAUNT",
	"CHEER",
	"HERO_CHEER",
	"POINT",
	"FEAR",
	"UNCONTROLLABLE_FEAR",
	"TERROR",
	"DOOM",
	"QUARRELSOME",
	"ALERT",
	"BRACE_FOR_BEING_CRUSHED",
	"CHEER_FOR_ABOUT_TO_CRUSH",
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
	for ( const char *const *name = EmotionNames; *name; ++name, ++i )
	{
		if ( _strcmpi( *name, token ) == 0 )
			return i;
	}
	return -1;
}

// ?getSingleBitFromName@?$BitFlags@$0M@@@SAHPBD@Z
template Int BitFlags<12>::getSingleBitFromName( const char *token );
