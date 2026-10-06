// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Evidence: retail 0x004BDC6D (54 bytes) is byte-identical to the landed
// BitFlags getSingleBitFromName pair except for the name-table DIR32: it
// reads 0x00DBAA40, whose first entries are VETERAN, ELITE, HERO
// (21 names total; distinct from the 104-entry table at 0x00DBC2C8).
// Same _strcmpi thunk at 0x00BBA518.

#include <bitset>
#include <string.h>

typedef int Int;
typedef bool Bool;

extern const char *VeterancyLevelNames[21]; ///< retail [0x00DBAA40]

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
	for ( const char *const *name = VeterancyLevelNames; *name; ++name, ++i )
	{
		if ( _strcmpi( *name, token ) == 0 )
			return i;
	}
	return -1;
}

// ?getSingleBitFromName@?$BitFlags@$0BF@@@SAHPBD@Z
template Int BitFlags<21>::getSingleBitFromName( const char *token );
