// cl: /DNDEBUG /MD /EHsc
// Retail 0x00248D9D, 146 bytes. LANAPI vtable slot 38 (vtable 0x0083E680,
// class of ??1LANAPI@@UAE@XZ).
// The slots are walked by index and addressed as m_holder->m_slots[i]: the
// banked 0.99 attempt computed holder + offset + 0x114 by hand, which swaps
// the lea operands of retail's strength-reduced address.
// Honest address name: __thiscall (ret 8: address plus flag byte). Guards on
// virtual slot54, scans 8 net slots at holder+0x114 stride 0x1D0 comparing
// each BfmeNetAddress with pin-only Rva00248CBF, validates the global wide
// string per miss, then marks the hit via indexer 0x00447773 (flag byte at
// +8 or GameSlot::unAccept) and finishes with virtual slot26 plus rowed
// Rva00248D84Enable unless all 8 missed. Layout follows LANAPILookupPlayer
// (BfmeNetAddress struct, LANAPI +0x44 holder) and Rva00447773Indexer
// (8x1D0 entries, caller 0x00248DF1).
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef unsigned char UnsignedByte;

struct BfmeNetAddress
{
	UnsignedInt ip;
	UnsignedShort port;
	Bool Rva00248CBF(const BfmeNetAddress *other) const;
};

template<typename T> class StringBase
{
	friend class LANAPI;
	void validate() const;
};

class GameSlot
{
public:
	void unAccept();
	char m_pad[8];
	UnsignedByte m_flag8;
};

struct SlotEntry
{
	BfmeNetAddress m_address;
	char m_tail[0x1C8];
};

class Rva00447773
{
public:
	void *rva00447773(int index);
	char m_pre[0x114];
	SlotEntry m_slots[8];
};

struct GlobalA03354
{
	StringBase<UnsignedShort> m_name;
};

extern GlobalA03354 *g_Va00A03354;
void Rva00248D84Enable();

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
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26(int code, BfmeNetAddress *query) = 0;
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
	virtual void rva00248D9D(const BfmeNetAddress *address, Bool flag);
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual Bool slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;

protected:
	UnsignedByte m_pre44[0x40];
	Rva00447773 *m_holder;
};

void LANAPI::rva00248D9D(const BfmeNetAddress *address, Bool flag)
{
	if (!slot54())
		return;
	int index;
	for (index = 0; index < 8; ++index)
	{
		BfmeNetAddress *slotAddr = &m_holder->m_slots[index].m_address;
		if (slotAddr->Rva00248CBF(address))
			goto found;
		GlobalA03354 *g = g_Va00A03354;
		if (g != 0)
			g->m_name.validate();
	}
	goto done;
found:
	{
		GameSlot *gs = (GameSlot *)m_holder->rva00447773(index);
		if (flag)
			gs->m_flag8 = 1;
		else
			gs->unAccept();
	}
done:
	if (index != 8)
	{
		BfmeNetAddress query;
		query.ip = 0;
		query.port = 0;
		slot26(0, &query);
		Rva00248D84Enable();
	}
}
// ?g_Va00A03354@@3PAUGlobalA03354@@A: the global at VA 0xe03354 is ?g_Va00A03354@@3HA.
#pragma comment(linker, "/alternatename:?g_Va00A03354@@3PAUGlobalA03354@@A=?g_Va00A03354@@3HA")
