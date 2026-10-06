// cl: /DNDEBUG /MD /EHsc
//
// ?rva00272A02@Drawable@@QAEX_N@Z, retail 0x00272A02, 54 bytes.
// Flag plus broadcast: bit 2 at +0x114 follows the bool arg, then walk
// this+0x14C modules forwarding the bool to slot 0x30 targets.
// Evidence: same +0x14C walk/flags as Drawable_rva0027290C neighbour
// (// cl: /O1 /DNDEBUG /MD /EHsc /G7 frameless); cmp byte proves bool;
// or/and dword at +0x114; ret 4; unblocks 6 incl 0x001E9083 0x00471464.

class DrawModuleForRva272A02
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void rva00272A02Target(bool flag) = 0;
};

class Drawable
{
public:
	void rva00272A02(bool flag);
private:
	unsigned char m_pad[0x114];
	int m_flags114;
	unsigned char m_pad118[0x14C - 0x118];
	DrawModuleForRva272A02 **m_drawModules;
};

void Drawable::rva00272A02(bool flag)
{
	if (flag)
		m_flags114 |= 2;
	else
		m_flags114 &= ~2;
	for (DrawModuleForRva272A02 **p = m_drawModules; *p; ++p)
		(*p)->rva00272A02Target(flag);
}
