// cl: /DNDEBUG /MD /EHsc
// Retail 0x00248D9D, 146 bytes. LANAPI vtable slot 38 (vtable 0x0083E680,
// class of ??1LANAPI@@UAE@XZ).
// The slots are walked by index through m_currentGame's getSlotAddress: the
// banked 0.99 attempt computed holder + offset + 0x114 by hand, which swaps
// the lea operands of retail's strength-reduced address.
// Honest address name: __thiscall (ret 8: address plus flag byte). Guards on
// AmIHost (vslot 54), scans 8 net slots at +0x114 stride 0x1D0 comparing
// each BfmeNetAddress with pin-only Rva00248CBF, validates the global wide
// string per miss, then marks the hit via indexer 0x00447773 (m_isAccepted at
// +8 or GameSlot::unAccept) and finishes with RequestGameOptionsPacked
// (vslot 26) plus rowed Rva00248D84Enable unless all 8 missed. Layout follows
// LANAPILookupPlayer (BfmeNetAddress struct, LANAPI +0x44 current game) and
// Rva00447773Indexer (8x1D0 entries, caller 0x00248DF1).
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef unsigned char UnsignedByte;

#include "../../Include/GameNetwork/BfmeNetAddress.h"

// Retail's validate hook on the lobby's global wide name is an empty
// function folded into the 0x000B3FD0 pool; the shared StringBase header
// inlines it empty, so the body spells the call through the pool's Coord3D
// destructor row (0x000B3FD0, coord3d.cpp) instead.
#define COORD3D_VIEW_EXTERN_DTOR
#include "../../../Libraries/Include/Lib/Coord3DCtorView.h"
#undef COORD3D_VIEW_EXTERN_DTOR

class GameSlot
{
public:
	void unAccept();
	char m_pad[8];
	Bool m_isAccepted;
};

#include "../../Include/Common/SlotEntry.h"

class Rva00447773
{
public:
	void *getLANSlot(int index);
	const BfmeNetAddress *getSlotAddress(int index) const { return &m_slots[index].m_address; }
	char m_pre[0x114];
	SlotEntry m_slots[8];
};

class LANGameInfo : public Rva00447773 {};

class AptLanLobby
{
	static AptLanLobby *s_instance;
public:
	static AptLanLobby *Instance() { return s_instance; }
	void OnGameJoin( void );
	void CancelMenu( void );
	void OnGameCreate( void );
};
void Rva00248D84Enable();

#include "../../Include/GameNetwork/LANAPI.h"

struct GlobalA03354
{
	StringBase<UnsignedShort> m_name;
};

void LANAPI::OnAccept(const BfmeNetAddress *address, Bool flag)
{
	if (!(UnsignedByte)AmIHost())
		return;
	int index;
	for (index = 0; index < 8; ++index)
	{
		const BfmeNetAddress *slotAddr = m_currentGame->getSlotAddress(index);
		if (slotAddr->Rva00248CBF(address))
			goto found;
		GlobalA03354 *g = (GlobalA03354 *)AptLanLobby::Instance();
		if (g != 0)
			((Coord3D *)&g->m_name)->~Coord3D();
	}
	goto done;
found:
	{
		GameSlot *gs = (GameSlot *)m_currentGame->getLANSlot(index);
		if (flag)
			gs->m_isAccepted = true;
		else
			gs->unAccept();
	}
done:
	if (index != 8)
	{
		BfmeNetAddress query;
		query.ip = 0;
		query.port = 0;
		RequestGameOptionsPacked(0, &query);
		Rva00248D84Enable();
	}
}
