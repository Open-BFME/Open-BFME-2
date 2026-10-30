// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x0044B40C, 143 bytes. RequestSetName at 0x44B8D9 calls this helper
// with the newly updated LANPlayer. Its body inserts into LANAPI +0x0C using
// LANPlayer name +0 and next +0x10; equal names use the IP dword at +0x14 as
// a secondary key. BFME1 LANAPI::addPlayer provides the insertion operation.

typedef unsigned short WideChar;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

#include "unicode_string.h"

typedef bool Bool;

struct BfmeNetAddress
{
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

class LANAPI
{
public:
	virtual void slot00(void) = 0;

protected:
	void addPlayer(LANPlayer *player);

private:
	UnsignedByte m_padding04[0x0C - 0x04];
	LANPlayer *m_lobbyPlayers;	// +0x0C
};

void LANAPI::addPlayer(LANPlayer *player)
{
	if (!m_lobbyPlayers)
	{
		m_lobbyPlayers = player;
		player->setNext(0);
		return;
	}

	if (player->getName().compareNoCase(m_lobbyPlayers->getName()) < 0
		|| (player->getName().compareNoCase(m_lobbyPlayers->getName()) == 0
			&& player->getIP() < m_lobbyPlayers->getIP()))
	{
		player->setNext(m_lobbyPlayers);
		m_lobbyPlayers = player;
		return;
	}

	LANPlayer *current = m_lobbyPlayers;
	while (current->getNext()
		&& (player->getName().compareNoCase(current->getNext()->getName()) > 0
			|| (player->getName().compareNoCase(current->getNext()->getName()) == 0
				&& player->getIP() > current->getNext()->getIP())))
		current = current->getNext();

	player->setNext(current->getNext());
	current->setNext(player);
}
