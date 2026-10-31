// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /ICode/GameEngine/Include
//
// ??0LANGameSlot@@QAE@ABV0@@Z @0x0044B27F 107B: LANGameSlot's copy
// constructor (callers 0x0044B6E9 0x00582402 0x0058265D 0x00582D16; Zero
// Hour's LANAPI::RequestGameCreate passes a local slot by value to
// LANGameInfo::setSlot). It copies the rowed GameSlot base (0x002295D7,
// 0x1AC bytes), installs the LANGameSlot vtable 0x00C3E4FC (the one the
// default constructor 0x00448150 stores), copies the LANPlayer at +0x1AC
// (rowed copy 0x0044A901), the AsciiString at +0x1C8 and the last-heard
// word at +0x1CC.
//
// ??_GLANGameSlot@@UAEPAXI@Z @0x0044818B 28B: slot 0 of that vtable, the
// scalar deleting destructor this unit emits with the vtable; it calls the
// implicit ~LANGameSlot 0x00447B0E and the global operator delete.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
#include "ascii_string.h"
#include "unicode_string.h"
class Rva00248CDD
{
public:
	Bool rva00248CDD( const Rva00248CDD &other ) const;
};
struct BfmeNetAddress : public Rva00248CDD
{
	BfmeNetAddress( void ) {}
	BfmeNetAddress( UnsignedInt ip, UnsignedShort port ) : m_ip( ip ), m_port( port ) {}
	BfmeNetAddress *self( void ) { return this; }
	Bool Rva00248CBF( const BfmeNetAddress *other ) const;

	UnsignedInt m_ip;
	UnsignedShort m_port;
};
enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_CLOSED = 1,
	SLOT_EASY_AI = 2,
	SLOT_MED_AI = 3,
	SLOT_BRUTAL_AI = 4,
	SLOT_AI_5 = 5,
	SLOT_PLAYER = 6
};
struct GameSlotConnectInfo
{
	Int m_nat;
	UnsignedShort m_port;
};
class GameSlot
{
public:
	GameSlot( const GameSlot &other );
	virtual ~GameSlot( void );
	void setState( SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo );
	void setAddress( const BfmeNetAddress &address ) { m_address = address; }
	Bool isHuman( void ) const;
	Bool hasMap( void ) const { return m_hasMap; }

private:
	UnsignedByte m_pre09[9 - 4];
	Bool m_hasMap;					// +0x09
public:
	UnsignedByte m_pre38[0x38 - 0x0A];
	BfmeNetAddress m_address;		// +0x38
	UnsignedByte m_pad40[0x1AC - 0x40];
};
class LANPlayer
{
public:
	LANPlayer() : m_lastHeard(0), m_next(0)
	{
		m_address.m_ip = 0;
		m_address.m_port = 0;
	}
	LANPlayer( const LANPlayer &other );
	~LANPlayer();

	const UnicodeString &getName(void) const { return m_name; }
	LANPlayer *getNext(void) const { return m_next; }
	void setNext(LANPlayer *next) { m_next = next; }
	UnsignedInt getIP(void) const { return m_address.m_ip; }

	UnicodeString m_name;
	UnicodeString m_login;
	UnicodeString m_host;
	UnsignedInt m_lastHeard;
	LANPlayer *m_next;
	BfmeNetAddress m_address;
};
class LANGameSlot : public GameSlot
{
public:
	LANGameSlot( void );
	LANGameSlot( const LANGameSlot &other );
	virtual ~LANGameSlot( void );

	void setLogin( AsciiString name );
	void setHost( AsciiString name );
	void setLastHeard( UnsignedInt time ) { m_lastHeard = time; }

private:
	LANPlayer m_user;				// +0x1AC
	AsciiString m_serial;				// +0x1C8
	UnsignedInt m_lastHeard;			// +0x1CC
};

LANGameSlot::LANGameSlot(const LANGameSlot &other) :
	GameSlot(other),
	m_user(other.m_user),
	m_serial(other.m_serial),
	m_lastHeard(other.m_lastHeard)
{
}
