// cl: /DNDEBUG /MD /EHsc
// ?parseCanMoveBackwards@@YAXPAVINI@@PAX1PBX@Z at retail 0x001E38F9 (53B).
// Split TU (precedent: INI_parseBool.cpp dedicated frameless TU): the sibling
// TU Code/GameEngine/Source/Common/SmallIniParseCallbacks.cpp keeps bare
// flags for ?parseGeometryRotationAnchorOffset (0x006BD360 16B JMP-tail), so
// this body lives here under /O1 where explain_mismatch proved 53/53 exact.
// BFME1 donor reference/open-bfme-1/game/GameEngine/Source/Common/
// SmallIniParseCallbacks.cpp parseCanMoveBackwards at 6583b3c1, adapted to
// BFME2 member scanBool (kept INI_scanBool.cpp QAE_NPBD) + kept atoi import
// slot 0xBBA624 (gen-small row 35053). Registration: rdata 0x7DE608
// [label VA, parser VA == entry, 0, 0xD8], label 'CanMoveBackwards' @0x7DDF70.
// ABI __cdecl 4-arg (ini, instance-unused, store-int, userData-unused), int
// store (4-byte mov [ecx],eax; cf 1-byte bool store in INI_parseBool.cpp).

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	bool scanBool( const char *token );
};

extern "C" __declspec( dllimport ) int __cdecl atoi( const char * );

// ?parseCanMoveBackwards@@YAXPAVINI@@PAX1PBX@Z
void parseCanMoveBackwards( INI *ini, void *, void *store, const void * )
{
	const char *token = ini->getNextToken( 0 );
	int value = atoi( token );
	if ( value >= 1 && value <= 4 )
		*(int *)store = value;
	else
		*(int *)store = ini->scanBool( token );
}
