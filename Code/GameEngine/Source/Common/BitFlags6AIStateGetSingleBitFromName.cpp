// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Evidence: retail 0x004DC6CC (54 bytes) is byte-identical to the landed
// BitFlags getSingleBitFromName pair except for the name-table DIR32: it
// reads 0x00DBA9AC, whose first entries are BACK_AWAY, AVOID_SCARER, IDLE
// (6 names total). Same _strcmpi thunk at 0x00BBA518.

#include <bitset>
#include <string.h>

typedef int Int;
typedef bool Bool;

// AIStateNames: the retail string table at VA 0xdba9ac.
const char *AIStateNames[6] = {
	"BACK_AWAY",
	"AVOID_SCARER",
	"IDLE",
	"RUN_AWAY_PANIC",
	"FACE_OBJECT",
	"QUARREL",
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
	for ( const char *const *name = AIStateNames; *name; ++name, ++i )
	{
		if ( _strcmpi( *name, token ) == 0 )
			return i;
	}
	return -1;
}

// ?getSingleBitFromName@?$BitFlags@$05@@SAHPBD@Z
template Int BitFlags<6>::getSingleBitFromName( const char *token );
