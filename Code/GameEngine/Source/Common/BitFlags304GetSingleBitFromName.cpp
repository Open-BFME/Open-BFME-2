// cl: /O1 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Evidence: retail 0x000B42CA (54 bytes) references the string literal
// "FRONTCRUSHED", an entry of ZH's ModelConditionFlags::s_bitNameList[]
// (GameEngine/Source/Common/BitFlags.cpp). ZH's header
// (Include/Common/BitFlags.h) declares the matching method:
//   static Int getSingleBitFromName(const char* token)
//   {
//     Int i = 0;
//     for (const char** name = s_bitNameList; *name; ++name, ++i)
//       if (stricmp(*name, token) == 0) return i;
//     return -1;
//   }
// This BFME2 binary's ModelConditionFlags is BitFlags<304> (see the sibling
// BitFlags304BuildDescription.cpp, already matched, which reads the same
// per-instantiation extern array under the name ModelConditionNames). The
// call site imports msvcr71.dll!_strcmpi (same import thunk already landed
// for MetaMap::findGameMessageMetaType at 0x1DB3FE), not _stricmp.

#include <bitset>
#include <string.h>

typedef int Int;
typedef bool Bool;

extern const char *const ModelConditionNames[];

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
	for ( const char *const *name = ModelConditionNames; *name; ++name, ++i )
	{
		if ( _strcmpi( *name, token ) == 0 )
			return i;
	}
	return -1;
}

// ?getSingleBitFromName@?$BitFlags@$0IAB@@@SAHPBD@Z
template Int BitFlags<304>::getSingleBitFromName( const char *token );
