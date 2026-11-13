// cl: /GX-
// ?send@Rva008038F0Sender@@QAEXPAVBfmeC994@@@Z 0x0066F930 123B
// FESL send via connection slot 3. Envelope prefix copies message +0x10/+0x14/+0x1c/+0x20.
// Tail vptr overwritten to the FESL message base table (VA 0x00CE0F20). Connection is *(this+0x10)+4.
// Callees rowed/pinned: ??0Rva007E86B0Base (0x00655770) ??1Rva007E86B0Base (0x00655780).
// Callers include ?bfmeUseSA@BfmeSinkSA (0x0067509C) ?bfmeSendSKA@BfmeSinkSKA ?process@Gen0080AB50.
// Volatile m_owner forces early esi load plus lea ecx [esi+4] matching retail schedule.

typedef unsigned char Byte;

// VA 0x00CE0F20 is the FESL message base table, emitted as BfmeMsgVJH's.
extern "C" char __identifier("??_7BfmeMsgVJH@@6B@");

#include "../../Include/Common/Rva007E86B0Base.h"

struct FeslSendEnvelopePrefix
{
	FeslSendEnvelopePrefix()
	{
		m_00 = 0;
		m_04 = 0;
		m_08 = 0;
		m_0c = 0;
		m_10 = 0;
	}

	int m_00;
	int m_04;
	void *m_08;
	int m_0c;
	Byte m_10;
	char m_pad11[3];
};

class Rva0066F930Tail : public Rva007E86B0Base
{
};

struct FeslSendEnvelope
{
	FeslSendEnvelopePrefix m_prefix;
	Rva0066F930Tail m_tail;
	int m_1c;
	int m_20;
};

#include "../../Include/GameNetwork/BfmeC994.h"

class FeslSendConnection
{
public:
	virtual void v0() = 0;
	virtual void v1() = 0;
	virtual void v2() = 0;
	virtual void v3( FeslSendEnvelope *envelope ) = 0;
};

class Rva008038F0Sender
{
public:
	void send( BfmeC994 *message );

	char m_pad00[ 0x10 ];
	void *volatile m_owner;
};

void Rva008038F0Sender::send( BfmeC994 *message )
{
	FeslSendEnvelope envelope;
	void *owner = m_owner;

	envelope.m_prefix.m_00 = message->m_category;
	envelope.m_prefix.m_04 = message->m_field20;
	envelope.m_prefix.m_08 = message->m_buffer;
	envelope.m_prefix.m_0c = message->m_capacity;
	*(volatile int *)&envelope.m_tail = (int)&__identifier("??_7BfmeMsgVJH@@6B@");
	envelope.m_1c = 0;
	envelope.m_20 = 0;
	envelope.m_tail.m_field04 = 0;

	FeslSendConnection *connection =
		(FeslSendConnection *)((char *)owner + 4);
	connection->v3( &envelope );
}
