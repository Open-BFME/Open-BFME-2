// cl: /DNDEBUG /MD
//
// ?update@Transport@@QAE_N_N@Z, retail 0x004D54C1 (115B).
// Zero Hour's Transport::update (Transport.cpp) for BFME 2's transport, which
// owns eight UDP sockets (12-byte slots from +0x40E0C) instead of one: a failed
// receive or send makes the update fail only when some socket reports
// ADDRNOTAVAIL (UDP status -7, rowed 0x00594A06). The receive takes the
// caller's flag. The callers' pinned address-derived spelling is kept; the
// receive and send halves (0x004D4D08 / 0x004D4BA7) are pinned.

typedef bool Bool;

class UDP
{
public:
	enum SockStatus { ADDRNOTAVAIL = -7 };
	~UDP();
	int rva00594A06();
};

struct TransportAddr
{
	unsigned int m_ip;
	unsigned short m_port;
};

struct TransportSocketSlot
{
	UDP *m_udpsock;
	TransportAddr m_addr;
};

class Transport
{
public:
	Bool update(Bool flag);
	Bool rva004D4D08(Bool flag);
	Bool rva004D4BA7();
	void RemoveSocketForSlot(unsigned short slot);

private:
	char m_pad00000[0x40E0C];
	TransportSocketSlot m_sockets[8]; // +0x40E0C
};

Bool Transport::update(Bool flag)
{
	Bool retval = true;
	if (rva004D4D08(flag) == false)
	{
		for (int i = 0; i < 8; ++i)
		{
			if (m_sockets[i].m_udpsock && m_sockets[i].m_udpsock->rva00594A06() == UDP::ADDRNOTAVAIL)
			{
				retval = false;
				break;
			}
		}
	}
	if (rva004D4BA7() == false)
	{
		for (int i = 0; i < 8; ++i)
		{
			if (m_sockets[i].m_udpsock && m_sockets[i].m_udpsock->rva00594A06() == UDP::ADDRNOTAVAIL)
			{
				retval = false;
				break;
			}
		}
	}
	return retval;
}

// ?RemoveSocketForSlot@Transport@@QAEXG@Z, retail 0x004D5133 (116B).
// Close one of the eight socket slots: the socket is deleted only when no
// other slot shares it, then the slot is cleared.
void Transport::RemoveSocketForSlot(unsigned short slot)
{
	if (slot < 8)
	{
		UDP *sock = m_sockets[slot].m_udpsock;
		if (sock)
		{
			for (int i = 0; i < 8; ++i)
			{
				if (i != slot && sock == m_sockets[i].m_udpsock)
					goto shared;
			}
			delete sock;
shared:
			m_sockets[slot].m_udpsock = 0;
			TransportAddr none;
			none.m_ip = 0;
			none.m_port = 0;
			m_sockets[slot].m_addr = none;
		}
	}
}
