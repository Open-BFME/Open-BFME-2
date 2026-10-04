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
// Layout: m_inGame +0x10.
typedef bool Bool;
typedef int Int;
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
};
extern Global009FE958 *g_Va009FE958;
#define TheLAN g_Va009FE958
class GameSlot
{
public:
	void unAccept(void);
};
class LANGameSlot : public GameSlot
{
public:
	Bool isLocalPlayer(void) const;
private:
	unsigned char m_pad00[0x1D0];
};
class LANGameInfo
{
public:
	virtual Int getLocalSlotNum(void) const;
	virtual void resetAccepted(void);
	const LANGameSlot *getConstLANSlot(Int slotNum) const;
	Bool rva004477C7(void) const;
private:
	unsigned char m_pad04[0x10 - 0x04];
	Bool m_inGame; // +0x10
	unsigned char m_pad11[0xDC - 0x11];
	LANGameSlot m_LANSlot[MAX_SLOTS]; // +0xDC
};

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

Bool LANGameInfo::rva004477C7(void) const
{
	if (!m_inGame)
		return false;
	return m_LANSlot[0].isLocalPlayer();
}
