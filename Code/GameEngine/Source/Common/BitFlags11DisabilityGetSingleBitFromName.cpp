// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Evidence: retail 0x0028C7AD (54 bytes) is byte-identical to the landed
// BitFlags<304>::getSingleBitFromName at 0x000B42CA and KindOf BitFlags<218>
// at 0x002AA2F9 except for the name-table DIR32: it reads 0x00DC828C, whose
// first entries are DEFAULT, DISABLED_USER_PARALYZED, DISABLED_EMP (11 names
// total). Same _strcmpi import thunk at 0x00BBA518, same loop returning the
// index or -1. ZH BitFlags.h declares the shared static shape.

#include <bitset>
#include <string.h>

typedef int Int;
typedef bool Bool;

extern const char *DisabilityTypeNames[11]; ///< retail [0x00DC828C]

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
	for ( const char *const *name = DisabilityTypeNames; *name; ++name, ++i )
	{
		if ( _strcmpi( *name, token ) == 0 )
			return i;
	}
	return -1;
}

// ?getSingleBitFromName@?$BitFlags@$0L@@@SAHPBD@Z
template Int BitFlags<11>::getSingleBitFromName( const char *token );
