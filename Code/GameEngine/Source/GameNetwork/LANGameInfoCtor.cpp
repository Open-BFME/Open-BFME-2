// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// LANGameSlot::LANGameSlot, retail 0x00448150 (59 bytes), and
// LANGameInfo::LANGameInfo, retail 0x004481D4 (162 bytes). Ported from Zero
// Hour's GameEngine/Source/GameNetwork/LANGameInfo.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference).
// Target evidence: LANAPI::RequestGameCreate (0x0044B55A) news a 0xF6C-byte
// object with 0x004481D4, builds a local slot with 0x00448150 and destroys it
// with 0x00447B0E; 0x004481D4 runs the rowed GameInfo constructor, builds its
// eight 0x1D0-byte slots at +0xDC with 0x00448150/0x00447B0E and stores the
// LANGameInfo vtable 0x00C3E518 (slot 2 names "LANGameInfo"); 0x00448150 runs
// the GameSlot constructor (pinned 0x003FFB4C) and stores vtable 0x00C3E4FC,
// the vtable the slot copy constructor 0x0044B27F also installs.
// BFME 2 differences: LANPlayer (+0x1AC) starts zeroed, including a port
// halfword after the IP, instead of assigning empty strings; the game's local
// IP is TheLAN's eight-byte local address (vslot 64) copied to +0x38.
// Callees: GameInfo::setSlotPointer 0x003FF332 (bounds-checked store into
// the slot-pointer table at +0x18, as Zero Hour's).

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

#include "ascii_string.h"
#include "unicode_string.h"

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap( char (*)[N] ) = 0;
};
template <> class VSlots<0>
{
};

enum
{
	MAX_SLOTS = 8
};

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedInt m_port;
};

class LANAPI : public VSlots<64>
{
public:
	virtual BfmeNetAddress *getLocalAddress( void ) = 0;
};

extern LANAPI *TheLAN;

class GameSlot
{
public:
	GameSlot( void );
	virtual ~GameSlot( void );

private:
	unsigned char m_body[0x1AC - 4];
};

class LANPlayer
{
public:
	LANPlayer( void ) : m_lastHeard( 0 ), m_next( 0 ), m_IP( 0 ), m_port( 0 ) {}
	~LANPlayer( void );

private:
	UnicodeString m_name;				// +0x00
	UnicodeString m_login;				// +0x04
	UnicodeString m_host;				// +0x08
	UnsignedInt m_lastHeard;			// +0x0C
	LANPlayer *m_next;				// +0x10
	UnsignedInt m_IP;				// +0x14
	UnsignedShort m_port;				// +0x18
};

class LANGameSlot : public GameSlot
{
public:
	LANGameSlot( void );
	virtual ~LANGameSlot( void );

private:
	LANPlayer m_user;				// +0x1AC
	AsciiString m_serial;				// +0x1C8
	UnsignedInt m_lastHeard;			// +0x1CC
};

class GameInfo
{
public:
	GameInfo( void );
	virtual ~GameInfo( void );
	void setSlotPointer( Int index, GameSlot *slot );

protected:
	unsigned char m_pre38[0x38 - 4];
	BfmeNetAddress m_localIP;			// +0x38
	unsigned char m_padDC[0xDC - 0x40];
};

class LANGameInfo : public GameInfo
{
public:
	LANGameInfo( void );
	virtual ~LANGameInfo( void );

private:
	LANGameSlot m_LANSlot[MAX_SLOTS];		// +0xDC
	LANGameInfo *m_next;				// +0xF5C
	UnsignedInt m_lastHeard;			// +0xF60
	UnicodeString m_gameName;			// +0xF64
	Bool m_isDirectConnect;				// +0xF68
};

LANGameSlot::LANGameSlot( void )
{
	m_lastHeard = 0;
}

LANGameInfo::LANGameInfo( void ) : m_next( 0 ), m_lastHeard( 0 ), m_isDirectConnect( false )
{
	for( UnsignedInt i = 0; i < MAX_SLOTS; ++i )
		setSlotPointer( i, &m_LANSlot[i] );

	m_localIP = *TheLAN->getLocalAddress();
}
