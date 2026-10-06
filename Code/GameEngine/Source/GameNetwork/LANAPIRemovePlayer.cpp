// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x004499C7, 56 bytes. Matched to BFME1 LANAPI::removePlayer's
// linked-list removal body. Target layout evidence is direct: LANAPI head at
// +0x0C, LANPlayer next at +0x10. The target also clears the removed node's
// next pointer and returns when the head is null; those target-specific
// behaviors are visible in the target body.

typedef unsigned char UnsignedByte;

class LANPlayer
{
public:
	UnsignedByte m_prefix[0x10];
	LANPlayer *m_next;

	LANPlayer *getNext( void ) const { return m_next; }
	void setNext( LANPlayer *next ) { m_next = next; }
};

class LANAPI
{
public:
	virtual void vft( void ) = 0;
	UnsignedByte m_prefix[8];
	LANPlayer *m_lobbyPlayers;

	protected:
	void removePlayer( LANPlayer *player );
};

void LANAPI::removePlayer( LANPlayer *player )
{
	LANPlayer *p = m_lobbyPlayers;
	if( !player )
		return;
	else if( p == player )
	{
		m_lobbyPlayers = p->getNext();
	}
	else
	{
		while( p->getNext() && p->getNext() != player )
			p = p->getNext();
		if( p->getNext() == player )
			p->setNext( player->getNext() );
	}
	player->setNext( 0 );
}
