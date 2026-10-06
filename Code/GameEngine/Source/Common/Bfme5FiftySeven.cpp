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

// The flag address is read off retail's own DIR32 operands at 0x00087952
// (`c6 05 1c 20 de 00 01`, twice), NOT from the donor's source comment, which
// names 0x012F9DB8. build.py masks DIR32 sites when it compares, so a wrong
// global still byte-matches; the operand bytes are the only evidence here.
extern bool g_bfmeFlagEC;					// retail 0x00DE201C

// ?bfmeSet@@YGX_N@Z
void __stdcall bfmeSet(bool value)
{
	if (value)
	{
		g_bfmeFlagEC = true;

		return;
	}

	if (g_bfmeFlagEC)
		g_bfmeFlagEC = false;
}
