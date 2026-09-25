// ?cacheGameLogicFrame@StatusBitsEldestFrame@@QAEXXZ
// partial score=0.8 date=2026-09-25
// cl: /O1 /DNDEBUG /MD
//
// ?cacheGameLogicFrame@StatusBitsEldestFrame@@QAEXXZ, retail 0x00485975,
// 14 bytes. Sole-called helper refreshing the eldest-frame cache member
// from the GameLogic frame (see StatusBitsUpgradeIfEldestKindofCtor.cpp
// for the owning object and the +0x40 frame precedent).

typedef unsigned int UnsignedInt;

class GameLogic
{
public:
	UnsignedInt getFrame() { return m_frame; }

private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame; // +0x40 (Poisoned precedent)
};

extern GameLogic *TheGameLogic;

struct StatusBitsEldestFrame
{
	void cacheGameLogicFrame(void);

private:
	int m_cachedFrame;
};

// ?cacheGameLogicFrame@StatusBitsEldestFrame@@QAEXXZ @0x00485975
void StatusBitsEldestFrame::cacheGameLogicFrame(void)
{
	int *slot = &m_cachedFrame;
	*slot = (int)TheGameLogic->getFrame();
}
