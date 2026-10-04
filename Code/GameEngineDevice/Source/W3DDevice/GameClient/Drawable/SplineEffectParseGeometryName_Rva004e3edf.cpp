// ?SplineEffectParseGeometryName@@YAXPAVINI@@PAX1PBX@Z, retail 0x004E3EDF, 105 bytes.
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/
// SplineEffectParseGeometryName.cpp. The donor body does not place at BFME 1's
// flags; compiled /Os it is byte-identical to retail once relocations are
// masked (unique hit on unclaimed .text). Only the placed body is defined
// here; the donor's other definitions are omitted.
//
// Open-BFME7: SplineEffect::ParseGeometryName (BFME 1 retail 0x003BB680 135 B;
// a gap claimed through its own exception text -- despite the "::" the entry
// point takes no `this`, it is a plain (INI*, void*, void*, const void*)
// callback like its neighbours; ecx only ever holds the "ini" pointer loaded
// off the stack, exactly as in the sibling record-based Parse bodies).  With no
// INI or instance it throws INIException(3
// "SplineEffect::ParseGeometryName::Invalid data passed in."); otherwise it
// reads one token via INI::getNextAsciiString() and hands it straight to the
// instance's setter (retail 0x004E3E91) by address, then releases the token's
// buffer.  No persistent record struct is built here at all -- the "record" in
// this family is just the temporary AsciiString.
//
// AsciiString comes from the shared compatibility shim, not a TU-local class:
// its destructor calls the releaseBuffer worker retail reaches directly at
// 0x00036410, which is the tail call of this body.
// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -DWIN32 -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable

#include "ascii_string.h"

typedef int Int;

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	AsciiString getNextAsciiString();
};

class Rva003BB680Owner
{
public:
	void setGeometryName( AsciiString &name );
};

// ?SplineEffectParseGeometryName@@YAXPAVINI@@PAX1PBX@Z
void SplineEffectParseGeometryName( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		( (Rva003BB680Owner *)instance )->setGeometryName( ini->getNextAsciiString() );
	}
	else
		throw INIException( 3, "SplineEffect::ParseGeometryName::Invalid data passed in." );
}
