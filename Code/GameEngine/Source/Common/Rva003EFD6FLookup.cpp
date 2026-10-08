// cl: /DNDEBUG /MD /EHsc
//
// ?rva003EFD6F@Rva003EFD6F@@QAEPAUValue003EFD6F@@PBVRva002E071E@@@Z @ 0x003EFD6F (68B).
// Thiscall lookup returning +0x10c on find+compare success else +0x108.
// Key [this+0x13c] vs [arg+0x14], rowed find 0x002B51F8 via global
// g_009FEF10 (TheLivingWorldLogic), rowed compare 0x002E071E. Callers
// 0x003192FC/0x003F0245/0x003F02A8 etc.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002E2903Player;
class Rva002E071E
{
public:
	bool rva002E071E(const Rva002E071E *other) const;
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

struct Value003EFD6F
{
	char m_pad[4];
};

class Rva003EFD6F
{
public:
	Value003EFD6F *rva003EFD6F(const Rva002E071E *arg);

private:
	char m_pad00[0x108];
	Value003EFD6F *m_108;
	Value003EFD6F *m_10c;
	char m_pad110[0x13c - 0x110];
	int m_13c;
};

Value003EFD6F *Rva003EFD6F::rva003EFD6F(const Rva002E071E *arg)
{
	int key = m_13c;
	if (key != *(const int *)((const char *)arg + 0x14))
	{
		Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(key, 0);
		if (player != 0 && ((const Rva002E071E *)player)->rva002E071E(arg))
			return m_10c;
	}
	return m_108;
}
