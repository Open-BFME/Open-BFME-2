// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringbaseascii /Ireference/open-bfme-1/inputs/reference/shims/iniexception /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
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
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/INIException.h"

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

class EmotionNugget;

class EmotionSystem
{
public:
	EmotionNugget *findNugget( const BfmeEmotionName &name );
};

extern EmotionSystem *TheEmotionSystem; // 0x012F0878

class BfmeThingVKC
{
public:
	void bfmeCopyVKC( const BfmeThingVKC &source );
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

	((BfmeThingVKC *)store)->bfmeCopyVKC( *(BfmeThingVKC *)source );
}
