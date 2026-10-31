// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /ICode/GameEngine/Include

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

LANPlayer::LANPlayer(const LANPlayer &other)
	: m_name(other.m_name),
	  m_login(other.m_login),
	  m_host(other.m_host),
	  m_lastHeard(other.m_lastHeard),
	  m_next(other.m_next),
	  m_address(other.m_address)
{
}
