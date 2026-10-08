// cl: /DNDEBUG /MD
//
// ?update@Transport@@QAE_NPAVRva00594DC0@@@Z, retail 0x004D54C1 (115B).
// Zero Hour's Transport::update (Transport.cpp) for BFME 2's transport, which
// owns eight UDP sockets (12-byte slots from +0x40E0C) instead of one: a failed
// receive or send makes the update fail only when some socket reports
// ADDRNOTAVAIL (UDP status -7, rowed 0x00594A06). The receive takes the
// caller's optional receiver pointer. Native doRecv invokes that object's
// 0x005952C4 method, so the former Bool argument view was incorrect.

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

#include "../../Include/GameNetwork/Transport.h"

Bool Transport::update(Rva00594DC0 *receiver)
{
	Bool retval = true;
	if (doRecv(receiver) == false)
	{
		for (int i = 0; i < 8; ++i)
		{
			if (((UDP *)m_slots[i].m_object) && ((UDP *)m_slots[i].m_object)->rva00594A06() == UDP::ADDRNOTAVAIL)
			{
				retval = false;
				break;
			}
		}
	}
	if (doSend() == false)
	{
		for (int i = 0; i < 8; ++i)
		{
			if (((UDP *)m_slots[i].m_object) && ((UDP *)m_slots[i].m_object)->rva00594A06() == UDP::ADDRNOTAVAIL)
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
		UDP *sock = (UDP *)m_slots[slot].m_object;
		if (sock)
		{
			for (int i = 0; i < 8; ++i)
			{
				if (i != slot && sock == ((UDP *)m_slots[i].m_object))
					goto shared;
			}
			delete sock;
shared:
			m_slots[slot].m_object = 0;
			TransportAddr none;
			none.m_ip = 0;
			none.m_port = 0;
			*(TransportAddr *)&m_slots[slot].m_x = none;
		}
	}
}
