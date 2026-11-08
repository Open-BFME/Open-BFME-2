// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
// stlport
//
// LANGameInfo's override of GameInfo vtable slot 6, retail 0x00447BE0 (102
// bytes): the game-list column image. Slot 6 of the LANGameInfo vtable
// 0x00C3E518; the GameInfo vtable 0x00C187C0 holds the base body 0x00401015
// there, which this override calls directly for every column but 2. Column 2
// shows "AptLock" (literal 0x00C3E4F4) for a game in progress, as BFME 1's
// LANDisplayGameList did inline (Open-BFME-1 LANDisplayGameList.cpp, retail
// 0x0068EBF0: the AptLock image when isGameInProgress()). The in-progress
// flag at +0x11 is read through Zero Hour's inline isGameInProgress
// (load-then-test). The GameSpy staging room override 0x004FDC78 is the same
// body on its own flag. The names follow the base's address.

typedef int Int;
typedef bool Bool;

#include "ascii_string.h"

#include "../../Include/GameClient/Image.h"

class GameInfo
{
public:
	virtual ~GameInfo( void );
	virtual void slot01( void ); virtual void slot02( void ); virtual void slot03( void );
	virtual void slot04( void ); virtual void slot05( void );
	virtual const Image *rva00401015( Int column );

	Bool isGameInProgress( void ) const { return m_inProgress; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the isGameInProgress copy loses
	// to the first-in-order copy. No flags touched.
	Bool bfme_inProgress_lgl( void ) const { return m_inProgress; }

protected:
	unsigned char m_pre10[0x10 - 4];
	Bool m_inGame;					// +0x10
	Bool m_inProgress;				// +0x11
};

class LANGameInfo : public GameInfo
{
public:
	virtual const Image *rva00401015( Int column );
};

const Image *LANGameInfo::rva00401015( Int column )
{
	switch( column )
	{
		case 2:
			if( bfme_inProgress_lgl() )
				return TheMappedImageCollection->findImageByName( AsciiString( "AptLock" ) );
			return NULL;
	}
	return GameInfo::rva00401015( column );
}
