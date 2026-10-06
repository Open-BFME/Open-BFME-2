// ?rva005183A0@Rva005183A0@@QAE_NXZ
// partial score=0.99 date=2026-09-30
// ?rva005183A0@Rva005183A0@@QAE_NXZ
// partial score=0.99 date=2026-09-30
// cl: /MD /EHsc
// ?rva005183A0@Rva005183A0@@QAE_NXZ, retail 0x005183A0, 90 bytes.
// Unlock: if +0x310 null return false else if !=5 return true else
// OptionPreferences forward via rowed ctor/forward/base-dtor returning
// forward!=0. Evidence: unlock lane, callers 0x00518413 0x005197C4.
// Improved: true UserPreferences size 0x14 not 0x20; inner block forces
// int save across dtor (esi not bl); ==5 form places true at end.
class Rva002E4272
{
public:
	virtual ~Rva002E4272();
	char m_pad[0x14 - 4];
};
class OptionPreferences : public Rva002E4272
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
	int Rva002E432EForward();
	bool getAllHealthBars();
};
class GameWindow
{
public:
	int winEnable(bool v);
};
void GadgetCheckBoxSetChecked(GameWindow *g, bool v);
class Rva005183A0
{
	char m_pad0[0x2BC];
	GameWindow *m_2BC;
	char m_pad1[0x310 - 0x2BC - 4];
	int m_val310;
public:
	bool rva005183A0();
	void rva005183FA();
};
bool Rva005183A0::rva005183A0()
{
	if (m_val310 == 0)
		return false;
	if (m_val310 == 5)
	{
		int f = OptionPreferences().Rva002E432EForward();
		return f != 0;
	}
	return true;
}

// ?rva005183FA@Rva005183A0@@QAEXXZ, retail 0x005183FA, 129B.
// Same-this twin of rva005183A0 above: GameWindow at +0x2BC via rowed
// GadgetCheckBoxSetChecked plus rowed winEnable, OptionPreferences temp via
// rowed ctor plus getAllHealthBars plus base dtor. Callers 0x00518FAE etc.
void Rva005183A0::rva005183FA()
{
	if (m_2BC == 0)
		return;
	if (!rva005183A0())
	{
		GadgetCheckBoxSetChecked(m_2BC, true);
		m_2BC->winEnable(false);
	}
	else
	{
		bool b = OptionPreferences().getAllHealthBars();
		GadgetCheckBoxSetChecked(m_2BC, b);
		m_2BC->winEnable(true);
	}
}

// Native OptionPreferences table C04CE8 slot0 -> deleting body2E42D2
// -> complete destructor2E4272. Keep this binding separate from the local view.
#pragma comment(linker, "/alternatename:??1OptionPreferences@@UAE@XZ=??1Rva002E4272@@UAE@XZ")
