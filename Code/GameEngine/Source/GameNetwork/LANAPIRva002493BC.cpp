// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail 0x002493BC, 116 bytes. LANAPI vtable slot 35 (vtable 0x0083E680,
// class of ??1LANAPI@@UAE@XZ).
// ?rva002493BC@LANAPI@@UAEXHVUnicodeString@@@Z
// Honest address name: __thiscall (ret 8: dead int plus by-value
// UnicodeString, destroyed in the EH epilogue via rowed releaseBuffer).
// Bails to the enable tail when holder +0x44 is null or when the address at
// holder+0x114 differs from virtual slot64 via pin-only Rva00248CBF; else
// calls the holder's virtual slot14, then virtual slot26(1, zero address).
// Tail always calls rowed Rva00248D84Enable. Chain lane: slot64/slot26 plus
// enable share the 0x00248D84 context; UnicodeString model follows
// Rva0023E928Getter (StringBase<WideChar> with void *m_data).
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef bool Bool;
typedef unsigned char UnsignedByte;

#include "unicode_string.h"


struct BfmeNetAddress
{
	UnsignedInt ip;
	UnsignedShort port;
	Bool Rva00248CBF(const BfmeNetAddress *other) const;
};

class Holder44
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
};

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
	virtual void rva002493BC(int unused, UnicodeString arg);
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
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
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual BfmeNetAddress *slot64() = 0;

protected:
	UnsignedByte m_pre44[0x40];
	Holder44 *m_holder;
};

void LANAPI::rva002493BC(int unused, UnicodeString arg)
{
	Holder44 *holder = m_holder;
	if (holder == 0)
		goto tail;
	BfmeNetAddress *base = (BfmeNetAddress *)((char *)holder + 0x114);
	if (!base->Rva00248CBF(slot64()))
		goto tail;
	m_holder->slot14();
	{
		BfmeNetAddress query;
		query.ip = 0;
		query.port = 0;
		slot26(1, &query);
	}
tail:
	Rva00248D84Enable();
}
