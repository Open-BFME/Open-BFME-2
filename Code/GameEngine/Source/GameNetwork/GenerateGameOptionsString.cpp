// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /O1
//
// GenerateGameOptionsString, retail 0x00447C46 (99 bytes): the host's game
// options string, empty unless TheLAN has a current game that this machine
// hosts. Ported from Open-BFME-1's GenerateGameOptionsString.cpp (BFME 1
// retail 0x0068DFF0), itself Zero Hour's LANGameInfo.cpp body with the
// include-slots argument.
// Target evidence: the body asks TheLAN (0x009FE958) for its game through
// LANAPI vslot 56 three times, tests it with the rowed amIHost body
// 0x004477C7 (in-game, then slot 0 is the local player), and returns either
// AsciiString::TheEmptyString or 0x00400AF8's string; 0x00400AF8 formats
// "M=%3.3x%s;MC=%X;MS=%d;SD=%d;GSID=%X;GT=%..." and the "H"/"C"/"O:" slot
// records, which is Zero Hour's GameInfoToAsciiString.
// BFME 2 difference: amIHost stays out of line.

typedef bool Bool;

#include "ascii_string.h"

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap( char (*)[N] ) = 0;
};
template <> class VSlots<0>
{
};

class GameInfo
{
};

class LANGameInfo : public GameInfo
{
public:
	Bool amIHost( void ) const;
};

class LANAPI : public VSlots<56>
{
public:
	virtual LANGameInfo *GetMyGame( void ) = 0;
};

extern LANAPI *TheLAN;

AsciiString GameInfoToAsciiString( const GameInfo *game, Bool includeSlots );

AsciiString GenerateGameOptionsString( void )
{
	if( !TheLAN->GetMyGame() || !TheLAN->GetMyGame()->amIHost() )
		return AsciiString::TheEmptyString;

	return GameInfoToAsciiString( TheLAN->GetMyGame(), true );
}
