// cl: /MD
//
// ?rva003F8101@Rva003F8101@@QAEPAXXZ @0x003F8101 38B.
// Find entry in ptr array [+0xC,+0x10) whose +8 id equals g_009FEF10+0xF4 else null.
// Evidence: loop add edx 4 cmp edx ecx; cmp [eax+8] esi where esi=[g+0xF4];
// caller at 0x003F8FF3 calls with no pushes tests eax; g name in use.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002BA8F1Logic
{
public:
	char m_pad00[0xF4];
	int m_xF4;
};

struct Rva003F8101Item
{
	char m_pad00[8];
	int m_id08;
};

class Rva003F8101
{
public:
	void *rva003F8101();
private:
	char m_pad00[0x0C];
	Rva003F8101Item **m_begin0C;
	Rva003F8101Item **m_end10;
};

void *Rva003F8101::rva003F8101()
{
	int sought = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_xF4;
	Rva003F8101Item **p = m_begin0C;
	Rva003F8101Item **end = m_end10;
	for (; p != end; ++p)
	{
		Rva003F8101Item *it = *p;
		if (it->m_id08 == sought)
			return it;
	}
	return 0;
}
