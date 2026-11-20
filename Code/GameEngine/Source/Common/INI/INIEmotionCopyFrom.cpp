// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/INI/INIEmotionCopyFrom.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// parseEmotionNuggetCopyFrom 0x004DCA34 (158B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.

// The EmotionNugget CopyFrom field parser, retail 0x0037B1B0.  The field table
// identifies this callback directly: it resolves a named nugget and copies its
// BfmeThing payload into the field at offset zero.
#include "../../../Include/Common/INI/INI.h"
#include "../../../Include/Common/INI/FieldParse.h"

// The BFME string implementation is shared by several source-level aliases.
// This one-word view preserves the proven findNugget parameter spelling while
// making the retail const-char constructor and release body explicit callees.
class BfmeStringLiteralBase
{
	friend class BfmeEmotionName;

private:
	BfmeStringLiteralBase( const char *text );
};

class BfmeEmotionName
{
public:
	BfmeEmotionName( const char *text )
	{
		((BfmeStringLiteralBase *)this)->BfmeStringLiteralBase::BfmeStringLiteralBase( text );
	}
	~BfmeEmotionName();

private:
	char *m_data;
};

#include "../../../Include/GameLogic/EmotionSystem.h"

extern EmotionSystem *TheEmotionSystem; // 0x012F0878

class Rva004DC920
{
public:
	void rva004DC788( const Rva004DC920 &source );	// 0x004DC788
};

// ?parseEmotionNuggetCopyFrom@@YAXPAVINI@@PAX1PBX@Z
void parseEmotionNuggetCopyFrom( INI *ini, void *, void *store, const void * )
{
	const char *token = ini->getNextToken();
	if( token == 0 )
		throw INIException( 3, "Name of emotion nugget to copy data from expected." );

	EmotionNugget *source;
	{
		BfmeEmotionName name( token );
		source = TheEmotionSystem->findNugget( name );
	}
	if( source == 0 )
		throw INIException( 3, "Emotion nugget to copy from not found." );

	((Rva004DC920 *)store)->rva004DC788( *(Rva004DC920 *)source );
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x00037BA0 reads ??0?$StringBase@D@@AAE@PBD@Z
#pragma comment(linker, "/alternatename:??0BfmeStringLiteralBase@@AAE@PBD@Z=??0?$StringBase@D@@AAE@PBD@Z")
//   0x00036410 reads ??1?$StringBase@D@@QAE@XZ
#pragma comment(linker, "/alternatename:??1BfmeEmotionName@@QAE@XZ=??1?$StringBase@D@@QAE@XZ")
