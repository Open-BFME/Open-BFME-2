// cl: /Ireference/shims/bfme2_ascii /MD
// ?SyncRegion@LivingWorldRegionEffectsManager@@QAEXH@Z @0x003EF08B 179B. Chain via 0x003EF041.
// Retail: kind at this+0x44 selects faction from arg+0x13c/0x140 else -1;
// if arg+0x1a2 and faction!=-1 does tmp rva003EE7CA/84A forward then
// conditional rva003EF041 then logic find and rva002104B6 check gating
// rva003EE89E vs rva003EE900 else rva003EE884/900. Callers at
// 0x003EF142/0x003EF1F5/0x003EFE5B. Prev 0x003EF041 same TU family.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva003EE7CA
{
public:
	int rva003EE7CA(int a, int b);
};
class Rva003EE84A
{
public:
	void rva003EE84A(int a, int b);
};
class Rva003EE89E
{
public:
	void rva003EE89E(int a, int b);
};
class Rva003EE884
{
public:
	void rva003EE884(int a);
};
class Rva003EE900
{
public:
	void rva003EE900(int a);
};
class Rva003EF041
{
public:
	void rva003EF041();
};
class Rva002E2903Player
{
public:
	char m_pad[0x2C];
};
class Rva002104B6
{
public:
	void *rva002104B6(void *p);
};
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *idx);
	char m_pad[0xB0];
	Rva002104B6 *m_B0;
};

struct Rva003EF08BArg
{
	char m_pad00[0x13C];
	int m_13C;
	int m_140;
	char m_pad144[0x1A2 - 0x144];
	unsigned char m_1A2;
};
class LivingWorldRegionEffectsManager
{
public:
	void SyncRegion(int arg);
private:
	char m_pad00[0x14];
	int m_14;
	char m_pad18[0x44 - 0x18];
	int m_44;
};
void LivingWorldRegionEffectsManager::SyncRegion(int argInt)
{
	Rva003EF08BArg *arg = (Rva003EF08BArg *)argInt;
	int faction;
	switch (m_44) {
	case 0:
		faction = arg->m_13C;
		break;
	case 1:
		faction = arg->m_140;
		break;
	default:
		faction = -1;
		break;
	}
	if (arg->m_1A2 && faction != -1) {
		int tmp[3];
		((Rva003EE7CA *)this)->rva003EE7CA((int)&tmp, argInt);
		((Rva003EE84A *)this)->rva003EE84A(argInt, (int)&tmp);
		if (argInt == m_14)
			((Rva003EF041 *)this)->rva003EF041();
		Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(faction, (unsigned int *)0);
		bool same = false;
		if (player) {
			Rva002104B6 *mid = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_B0;
			void *q = mid->rva002104B6((void *)((char *)player + 0x2C));
			same = (q == (void *)argInt);
		}
		if (same)
			((Rva003EE89E *)this)->rva003EE89E(argInt, (int)&tmp);
		else
			((Rva003EE900 *)this)->rva003EE900(argInt);
	} else {
		((Rva003EE884 *)this)->rva003EE884(argInt);
		((Rva003EE900 *)this)->rva003EE900(argInt);
	}
}
