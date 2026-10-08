// cl: /DNDEBUG /MD /EHsc
// Retail 0x00449745, 167 bytes. LANAPI vtable slot 24 (vtable 0x0083E680,
// class of ??1LANAPI@@UAE@XZ).
// ?rva00449745@LANAPI@@UAEXI@Z
// Honest address name: __thiscall (ret 4: one UnsignedInt). Bails when flag
// +0x41 is set or holder +0x44 is null; bails when the key at holder+0x114
// differs from virtual slot64 via rowed Rva00248CDD compare; else stamps
// timeGetTime()+1000 at +0x20, (arg ? arg-1 : 0) at +0x24, builds a 0x1D8
// LANMessage (type 15, arg at +0x1E) for virtual slot57 plus pinned
// LANAPI::Rva004495A2, calls pinned Transport::update(0) on +0x50,
// then virtual slot44(arg). Chain lane: calls landed 0x00248CDD.
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef unsigned char UnsignedByte;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

struct BfmeNetAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

class Rva00248CDD
{
public:
	Bool rva00248CDD(const Rva00248CDD &other) const;
private:
	UnsignedInt m_key0;
	UnsignedShort m_key4;
};

#include "../../Include/GameNetwork/Transport.h"

#pragma pack(push, 1)
struct LANMessage
{
	UnsignedInt m_type;
	char m_pad[0x1E - 4];
	UnsignedInt m_arg;
	char m_rest[0x1D8 - 0x22];
};
#pragma pack(pop)

struct SlotEntry25
{
	BfmeNetAddress m_address;
	char m_tail[0x1C8];
};

class Rva00447773
{
public:
	void *rva00447773(int index);
	char m_pre[0x114];
	SlotEntry25 m_slots[8];
};

class LANAPI
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void rva00449745(UnsignedInt arg);
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44(UnsignedInt arg) = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57(LANMessage *msg) = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual Rva00248CDD *slot64() = 0;
	void Rva004495A2(LANMessage *msg, UnsignedInt flags);

protected:
	char m_pre20[0x1C];
	UnsignedInt m_time20;
	UnsignedInt m_val24;
	char m_pre41[0x19];
	UnsignedByte m_flag41;
	char m_pad42[2];
	Rva00447773 *m_holder;
	char m_pre50[8];
	Transport *m_transport;
};

void LANAPI::rva00449745(UnsignedInt arg)
{
	if (m_flag41 != 0)
		return;
	if (m_holder == 0)
		return;
	Rva00248CDD *key = (Rva00248CDD *)((char *)m_holder + 0x114);
	if (key->rva00248CDD(*slot64()))
		return;
	m_time20 = timeGetTime() + 1000;
	m_val24 = arg ? arg - 1 : 0;
	LANMessage msg;
	msg.m_type = 15;
	msg.m_arg = arg;
	slot57(&msg);
	Rva004495A2(&msg, 0);
	m_transport->update(0);
	slot44(arg);
}
