// ?isLocalPlayer@LANGameSlot@@QBE_NXZ
// partial score=0.94 date=2026-10-04
// cl: /O1 /DNDEBUG /MD
//
// LANGameInfo::getLocalSlotNum, retail 0x00447794 (51 bytes), and
// LANGameInfo::resetAccepted, retail 0x004477E0 (47 bytes): slots 13 and 14
// of vtable 0x00C3E518, whose unique slot-2 name getter returns
// "LANGameInfo"; in the GameInfo vtable the same slots hold the rowed
// GameInfo::getLocalSlotNum and resetAccepted, which Zero Hour's LANGameInfo
// overrides. Ported from Zero Hour's GameEngine/Source/GameNetwork/
// LANGameInfo.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference).
// Callees: getConstLANSlot is the rowed opaque indexer 0x00447773 (slots of
// 0x1D0 bytes from +0xDC, MAX_SLOTS 8), pinned by its Zero Hour name;
// LANGameSlot::isLocalPlayer is pinned at 0x0044770F; GameSlot::unAccept is
// rowed.
// BFME 2 differences: getLocalSlotNum keeps one result and a single exit;
// resetAccepted only resets TheLAN's start timer (its
// vslot 31; TheLAN is the rowed global g_Va009FE958) before unaccepting the
// slots, without Zero Hour's host start-button refresh.
// LANGameSlot::isLocalPlayer, retail 0x0044770F (100 bytes): Zero Hour's
// isHuman() && TheLAN && local IP == slot IP, where BFME 2 compares 8-byte
// addresses (TheLAN vslot 64 returns the local one; the slot's is at +0x38)
// through the pinned BfmeNetAddress::Rva00248CBF, and on a mismatch tries
// once more with the local port raised by 8.
// Layout: m_inGame +0x10.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
struct BfmeNetAddress
{
	bool Rva00248CBF(const BfmeNetAddress *other) const;
	UnsignedInt m_ip;
	UnsignedShort m_port;
};
enum
{
	MAX_SLOTS = 8
};
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
struct Global009FE958 : public VSlots<31>
{
	virtual void ResetGameStartTimer(void) = 0;
	virtual void slot32() = 0; virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0; virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0; virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0; virtual void slot58() = 0; virtual void slot59() = 0;
	virtual void slot60() = 0; virtual void slot61() = 0; virtual void slot62() = 0; virtual void slot63() = 0;
	virtual const BfmeNetAddress *GetLocalAddress(void) = 0;
};
extern Global009FE958 *g_Va009FE958;
#define TheLAN g_Va009FE958
class GameSlot
{
public:
	void unAccept(void);
	Bool isHuman(void) const;
};
class LANGameSlot : public GameSlot
{
public:
	Bool isLocalPlayer(void) const;
private:
	unsigned char m_pad00[0x38];
	BfmeNetAddress m_address; // +0x38
	unsigned char m_pad40[0x1D0 - 0x40];
};
class LANGameInfo
{
public:
	virtual Int getLocalSlotNum(void) const;
	virtual void resetAccepted(void);
	const LANGameSlot *getConstLANSlot(Int slotNum) const;
private:
	unsigned char m_pad04[0x10 - 0x04];
	Bool m_inGame; // +0x10
	unsigned char m_pad11[0xDC - 0x11];
	LANGameSlot m_LANSlot[MAX_SLOTS]; // +0xDC
};

Bool LANGameSlot::isLocalPlayer( void ) const
{
	if (isHuman() && TheLAN)
	{
		if (TheLAN->GetLocalAddress()->Rva00248CBF(&m_address))
			return true;
		BfmeNetAddress alternate = *TheLAN->GetLocalAddress();
		alternate.m_port += 8;
		return alternate.Rva00248CBF(&m_address);
	}
	return false;
}

Int LANGameInfo::getLocalSlotNum( void ) const
{
	Int localSlot = -1;
	if (m_inGame)
	{
		for (Int i=0; i<MAX_SLOTS; ++i)
		{
			const LANGameSlot *slot = getConstLANSlot(i);
			if (slot->isLocalPlayer())
			{
				localSlot = i;
				break;
			}
		}
	}
	return localSlot;
}

void LANGameInfo::resetAccepted( void )
{
	if (TheLAN)
	{
		TheLAN->ResetGameStartTimer();
	}
	for(int i = 0; i< MAX_SLOTS; i++)
	{
		m_LANSlot[i].unAccept();
	}
}
