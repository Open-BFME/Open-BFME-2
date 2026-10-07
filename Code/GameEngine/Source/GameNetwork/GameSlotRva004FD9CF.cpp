// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?disconnected@GameSlot@@QBE_NXZ @0x004FD9CF 27B
// GameSlot::disconnected, Zero Hour's GameInfo.h inline
// `Bool disconnected(void) const { return isHuman() && m_disconnected; }`,
// which BFME 2 (like BFME 1, retail 0x000A3080) keeps out of line.
// Target evidence: it calls the rowed isHuman 0x003FF0F1 on the same this and
// then tests the byte at +0x48; all five callers test only al, and
// generateGameSpyGameResultsPacket 0x004FE35F calls it where Zero Hour's
// calls slot->disconnected(). The && expression is what gives retail's
// xor eax,eax / inc eax result; the field name is carried from Zero Hour.

class GameSlot
{
public:
	bool isHuman() const;
	bool disconnected() const;

private:
	char m_pad00[0x48];
	bool m_disconnected;				// +0x48
};

bool GameSlot::disconnected() const
{
	return isHuman() && m_disconnected;
}
