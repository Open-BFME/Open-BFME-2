// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Four more: another counted handle, a four-word copy out, an xor swap and a
// global flag setter.

class Gen_0073A2E0
{
public:
	void bfmeSwapBits(void);

private:
	int m_bfmeHead[16];					// +0x00
	unsigned int m_bfmeFirst;				// +0x40
	unsigned int m_bfmeSecond;				// +0x44
	bool m_bfmeDirty;					// +0x48
};

// ?bfmeSwapBits@Gen_0073A2E0@@QAEXXZ
void Gen_0073A2E0::bfmeSwapBits(void)
{
	if (m_bfmeDirty)
	{
		m_bfmeFirst = m_bfmeFirst ^ m_bfmeSecond;
		m_bfmeSecond = m_bfmeSecond ^ m_bfmeFirst;
		m_bfmeFirst = m_bfmeFirst ^ m_bfmeSecond;

		m_bfmeDirty = false;
	}
}
