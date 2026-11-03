// cl: /O2 /GX- /DNDEBUG /MD
// FESL ariesudp.cpp inbound datagram handler @ 0x00661650 (269B, RET 0xC).
//
// Target facts: slot 2 of the secondary-base vftable 0x00CE2C10 (installed at
// +4 by the matched destructor 0x006617C0; slot 0 is the adjustor thunk
// 0x00661640 to ??_GGen007F4D00, slot 1 the matched compare 0x00661620), so
// the body is entered with `this` at the +4 base and reads the two handlers
// at object +8 as [this+4]. It builds the 0x24-byte packet with the matched
// constructor 0x00661760, copies the sender address (+4/+8/+0xC of the
// address object at packet+0x14), decodes three big-endian words (type, id,
// size) and the payload pointer from the datagram, asserts
// "length >= (int)fap.mSize" (the WorldBuilder twin's string, line 176 of
// ariesudp.cpp), wraps the payload in a FESL message, reads its "TYPE" and
// forwards the packet to handler slot 3 when the type indexes one of the two
// handlers. Returns true.
//
// The WB debug twin (0x016CFC70) calls the handler lookup as a non-virtual
// member of the most-derived object (this-4); retail inlines it. Class and
// method names are address-derived: the original names are not recovered.
// Callees: Rva007EB810Get 0x006587A0, Rva007E8810Message ctor 0x006558C0,
// getInt 0x00655990, and the folded base destructor 0x00655780 for both the
// message and the address (rowed / pinned spellings).

#include "../../Include/GameNetwork/Rva007EB810Diag.h"

Rva007EB810Diag *Rva007EB810Get(void);

class Rva007E8810Message
{
public:
	Rva007E8810Message();
	~Rva007E8810Message();
	int getInt(const char *key, int defaultValue);
	void attach(const unsigned char *record) { m_record = record; }

private:
	char m_pad[0x10];
	const unsigned char *m_record;	// +0x10
	char m_pad14[0x20];
};

class Rva00800780Addr
{
public:
	~Rva00800780Addr();
	virtual void v0();

	int m_04;
	int m_08;
	int m_0C;
};

struct Rva7F4CC0ConstructorThunk
{
	Rva7F4CC0ConstructorThunk();

	unsigned mType;
	unsigned mId;
	const unsigned char *mData;
	unsigned mSize;
	bool mFlag;
	Rva00800780Addr mAddr;			// +0x14
};

class Rva00661650Handler
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void onPacket(Rva7F4CC0ConstructorThunk *packet);
};

class Rva00661650Base
{
public:
	virtual ~Rva00661650Base();
};

class Rva00661650Listener
{
public:
	virtual ~Rva00661650Listener();
	virtual int eq(const void *other, int, int) const;
	virtual bool onDatagram(const Rva00800780Addr &from,
		const unsigned char *data, int length);
};

class Rva00661650AriesUdp : public Rva00661650Base, public Rva00661650Listener
{
public:
	virtual bool onDatagram(const Rva00800780Addr &from,
		const unsigned char *data, int length);

	Rva00661650Handler *getHandler(int type)
	{
		if (type >= 0 && type < 2)
			return m_handlers[type];
		return 0;
	}

private:
	Rva00661650Handler *m_handlers[2];	// +8
	int m_10;
	int m_14;
};

bool Rva00661650AriesUdp::onDatagram(const Rva00800780Addr &from,
	const unsigned char *data, int length)
{
	Rva7F4CC0ConstructorThunk fap;
	fap.mAddr = from;
	fap.mType = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
	fap.mId = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
	fap.mSize = (data[8] << 24) | (data[9] << 16) | (data[10] << 8) | data[11];
	fap.mData = data + 12;
	if (!(length >= (int)fap.mSize))
		Rva007EB810Get()->fail("length >= (int)fap.mSize",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\ariesudp.cpp", 176);
	fap.mSize -= 12;

	Rva007E8810Message msg;
	msg.attach(fap.mData);
	Rva00661650Handler *handler = getHandler(msg.getInt("TYPE", 0));
	if (handler)
		handler->onPacket(&fap);
	return true;
}
