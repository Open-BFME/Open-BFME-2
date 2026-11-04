// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail 0x002493BC, 116 bytes. LANAPI vtable slot 35 (vtable 0x0083E680,
// class of ??1LANAPI@@UAE@XZ).
// ?OnPlayerJoin@LANAPI@@UAEXHVUnicodeString@@@Z
// Honest address name: __thiscall (ret 8: dead int plus by-value
// UnicodeString, destroyed in the EH epilogue via rowed releaseBuffer).
// Bails to the enable tail when holder +0x44 is null or when the address at
// holder+0x114 differs from slot64 getLocalAddress via pin-only Rva00248CBF; else
// calls the holder's virtual slot14, then slot26 RequestGameOptionsPacked(1, zero address).
// Tail always calls rowed Rva00248D84Enable. Chain lane: slot64/slot26 plus
// enable share the 0x00248D84 context; UnicodeString model follows
// Rva0023E928Getter (StringBase<WideChar> with void *m_data).
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef bool Bool;
typedef unsigned char UnsignedByte;

#include "unicode_string.h"


#include "../../Include/GameNetwork/BfmeNetAddress.h"

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

#include "../../Include/GameNetwork/LANAPI.h"

void LANAPI::OnPlayerJoin(int unused, UnicodeString playerName)
{
	Holder44 *holder = reinterpret_cast<Holder44 *>(m_currentGame);
	if (holder == 0)
		goto tail;
	BfmeNetAddress *base = (BfmeNetAddress *)((char *)holder + 0x114);
	if (!base->Rva00248CBF(getLocalAddress()))
		goto tail;
	reinterpret_cast<Holder44 *>(m_currentGame)->slot14();
	{
		BfmeNetAddress query;
		query.ip = 0;
		query.port = 0;
		RequestGameOptionsPacked(true, &query);
	}
tail:
	Rva00248D84Enable();
}
