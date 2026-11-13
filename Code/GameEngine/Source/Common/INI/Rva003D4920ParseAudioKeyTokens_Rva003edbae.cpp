// cl: -DNDEBUG -MD -EHsc
// Open-BFME7: INI field parser at 0x003D4920 (125 B): every remaining token
// becomes an AsciiString handed to LargeGroupAudioKeyMap::bfmeAddKey
// (0x003D46A0, landed) on the map the store argument points at; the string
// is destroyed after each call (EH state 0 across the call).  Address-derived
// parser name.

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/Common/LargeGroupAudioKeyMap.h"

class Rva003D4920
{
public:
	static void parseAudioKeyTokens( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseAudioKeyTokens@Rva003D4920@@SAXPAVINI@@PAX1PBX@Z
void Rva003D4920::parseAudioKeyTokens( INI *ini, void *, void *store, const void * )
{
	LargeGroupAudioKeyMap *keys = (LargeGroupAudioKeyMap *)store;
	for( const char *token = ini->getNextTokenOrNull(); token; token = ini->getNextTokenOrNull() )
	{
		AsciiString name( token );
		keys->bfmeAddKey( name );
	}
}
