// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Evidence: retail 0x002AA2F9 (54 bytes) is byte-identical to the landed
// BitFlags<304>::getSingleBitFromName at 0x000B42CA except for the name-table
// address: KindOf reads 0x00DBBE18 (the 218-entry KindOf table proven by
// KindOfGetNameFromSingleBit.cpp) where ModelConditionFlags reads 0x00DBAA98.
// Both call the same msvcr71 _strcmpi import thunk at 0x00BBA518, test eax,
// and return the index or -1 with the same push/pop and loop shape. ZH's
// header (Include/Common/BitFlags.h) declares the matching method:
//   static Int getSingleBitFromName(const char* token)
//   {
//     Int i = 0;
//     for (const char** name = s_bitNameList; *name; ++name, ++i)
//       if (stricmp(*name, token) == 0) return i;
//     return -1;
//   }
// KindOfMaskType is BitFlags<218> (0xDA entries), so this instantiates the
// same static body for 218 bits over TheKindOfBitNames.

#include <bitset>
#include <string.h>

typedef int Int;
typedef bool Bool;

extern const char *TheKindOfBitNames[0xDA + 1]; ///< retail [0x00DBBE18]

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
	for ( const char *const *name = TheKindOfBitNames; *name; ++name, ++i )
	{
		if ( _strcmpi( *name, token ) == 0 )
			return i;
	}
	return -1;
}

// ?getSingleBitFromName@?$BitFlags@$0NK@@@SAHPBD@Z
template Int BitFlags<218>::getSingleBitFromName( const char *token );
