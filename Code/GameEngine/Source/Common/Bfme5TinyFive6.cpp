// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Four more tiny ones: two two-part tests, a pair written into an object that
// may not be there, and a widen-the-range helper whose two stores are merged
// into one -- both write through whichever pointer the branch left in the
// register.

class Gen_005B53B0
{
public:
	void *bfmeSlot(void);

private:
	int m_bfmeTag;						// +0x000
	int m_bfmeField;					// +0x004
	int m_bfmeGap[12];					// +0x008
	unsigned char m_bfmeReady;				// +0x038
	char m_bfmeGap2[0x10F];					// +0x039
	int m_bfmeMode;						// +0x148
};

// ?bfmeSlot@Gen_005B53B0@@QAEPAXXZ
void *Gen_005B53B0::bfmeSlot(void)
{
	if (m_bfmeReady && m_bfmeMode == 1)
		return &m_bfmeField;

	return 0;
}