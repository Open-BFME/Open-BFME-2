// ?rva00514950@Rva00514EAB@@QAEHHHH@Z
// partial score=0.96 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// ?rva00514950@Rva00514EAB@@QAEHHH@Z @0x00514950 331B virtual slot 1 of vtable 0x00C65F10.
// Evidence: vtable owner ??1Rva00514EAB from OpaqueScalarDeletingDtorsB12; strings HideCredits/ShowMainMenu;
// rowed invoke 0x00222A8B; rowed Mouse::_bfme_setEngineVisibility 0x001EE5BE; abs thunk 0x00629952.

class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;

class Mouse
{
public:
	void _bfme_setEngineVisibility(bool visible);
};
extern Mouse *TheMouse;

extern "C" int __cdecl abs(int value);

extern int g_00E048F0;
extern int g_00E048EC;
extern int g_00E048E8;

class Rva00514EAB
{
public:
	int rva00514950(int msg, int p1, int p2);
private:
	unsigned char m_pad00[0x274];
	void *m_274;
	unsigned char m_pad278[0x27D - 0x278];
	bool m_27D;
	bool m_27E;
	unsigned char m_pad27F[0x288 - 0x27F];
	int m_288;
};

int Rva00514EAB::rva00514950(int msg, int p1, int p2)
{
	int state = m_288;
	if (state == 8)
		return 0;
	if (m_27D)
	{
		if (msg != 0x15)
			return 0;
		if (((unsigned char)p1 - 1) != 0)
			return 0;
		if ((p2 & 1) != 0)
		{
			if (state == 1)
				return 1;
			if (state == 2)
				return 1;
			if (state != 4)
				return 1;
			TheRva00222A8BTarget->invoke(m_274, "HideCredits", 0, 0, 0, 0, 0, 0);
			return 1;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if (m_27E)
			m_27D = true;
		if (msg != 0x15)
		{
			if (msg == 0x18)
			{
				int low = p1 & 0xFFFF;
				int high = (int)((unsigned int)p1 >> 16);
				if (low != 0 || high != 0)
				{
					if ((g_00E048F0 & 1) == 0)
					{
						g_00E048F0 |= 1;
						g_00E048EC = low;
					}
					if ((g_00E048F0 & 2) == 0)
					{
						g_00E048F0 |= 2;
						g_00E048E8 = high;
					}
					if (abs(low - g_00E048EC) > 20 || abs(high - g_00E048E8) > 20)
						m_27D = true;
				}
			}
		}
		else
		{
			if (state != 4)
				m_27D = true;
		}
		if (!m_27D)
			return 0;
		TheMouse->_bfme_setEngineVisibility(true);
		m_27D = true;
		TheRva00222A8BTarget->invoke(m_274, "ShowMainMenu", 0, 0, 0, 0, 0, 0);
		return 0;
	}
}
