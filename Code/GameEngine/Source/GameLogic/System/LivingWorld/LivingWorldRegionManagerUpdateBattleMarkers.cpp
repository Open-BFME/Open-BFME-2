// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Oi
// LivingWorldRegionManager::UpdateBattleMarkers, retail 0x0020EBA0 249B (WB
// 0x00B57470, LivingWorldRegionManager.cpp:1496..1515; the name is already
// pinned from LivingWorldLogic::OnBattleComplete's call). With pending battles
// it refreshes the logic's proxy (0x002B254F gate, 0x002B256E getter, 0x003F830F)
// and, for more than one player (0x002B5256), enumerates the battle whose
// 0x003F4831 id matches through 0x0020E7BD with the 0x00BE433C visitor, else
// the 0x0020E794 selection with the 0x00BE433C or 0x00BE4320 visitor by
// 0x003F48EF. The emptiness test is WB's `size() > 0` (retail sar/je).
#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

class LivingWorldBattle
{
public:
	int rva003F4831();
	bool rva003F48EF(void *p);
};


class Rva002B254F
{
public:
	int rva002B254F();
};

class Rva002BA8F1Logic
{
public:
	int rva002B5256(bool flag);
};

class Rva003F81FDProxy
{
public:
	void rva003F830F(void *p);
};

class Rva002B256E
{
public:
	void *rva002B256E();
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define g_009FEF10 ((Rva002BA8F1Logic *)TheLivingWorldLogic)
extern const void *const g_00BE433C[];
// Retail's one-slot visitor table at VA 0x00BE433C (RVA 0x007E433C; see
// RegionArmyComparatorView.h): its slot is 0x0020E779, rowed as
// Rva0020E767::call (VslotSmallBodiesAB.cpp). Defined here: nothing
// else in the tree did.
extern "C" void __identifier("?call@Rva0020E767@@UAE_NPAVRva003F409F@@@Z")();
extern const void *const g_00BE433C[] =
{
	(const void *)&__identifier("?call@Rva0020E767@@UAE_NPAVRva003F409F@@@Z")
};
extern "C" const void *const __identifier("??_7Rva0020E394@@6B@")[];

struct EmptyBase20EBA0
{
	EmptyBase20EBA0() {}
	~EmptyBase20EBA0() { _ReadWriteBarrier(); }
};

struct TmpBE433C : EmptyBase20EBA0
{
	const void *v;
	void *o;
	TmpBE433C(void *oo) : v(g_00BE433C), o(oo) {}
	~TmpBE433C() {}
};

struct TmpBE4320 : EmptyBase20EBA0
{
	const void *v;
	TmpBE4320() : v(__identifier("??_7Rva0020E394@@6B@")) {}
	~TmpBE4320() {}
};

class PendingBattleVisitor;

class LivingWorldRegionManager
{
public:
	void UpdateBattleMarkers();
	LivingWorldBattle *SelectPendingBattle();
	void EnumeratePendingBattles(PendingBattleVisitor &visitor) const;
private:
	unsigned char m_pad[0x14];
	LivingWorldBattle **m_begin;
	LivingWorldBattle **m_end;
};

void LivingWorldRegionManager::UpdateBattleMarkers()
{
	if (!((unsigned int)(m_end - m_begin) > 0))
		return;
	if ((unsigned char)((Rva002B254F *)g_009FEF10)->rva002B254F()) {
		((Rva003F81FDProxy *)((Rva002B256E *)g_009FEF10)->rva002B256E())->rva003F830F(this);
	}
	int n = g_009FEF10->rva002B5256(false);
	if (n <= 1)
		return;
	LivingWorldBattle **begin = m_begin;
	LivingWorldBattle **end = m_end;
	for (; begin != end; ++begin) {
		LivingWorldBattle *livingWorldBattle = *begin;
		if (livingWorldBattle->rva003F4831() == n) {
			if (!livingWorldBattle)
				break;
			TmpBE433C tmp(livingWorldBattle);
			EnumeratePendingBattles(*(PendingBattleVisitor *)&tmp);
			return;
		}
	}
	LivingWorldBattle *pendingBattle = SelectPendingBattle();
	if (!pendingBattle)
		return;
	void *q = *(void **)((char *)g_009FEF10 + 0x98);
	if (!q)
		return;
	if (pendingBattle->rva003F48EF(q)) {
		TmpBE433C tmp(pendingBattle);
		EnumeratePendingBattles(*(PendingBattleVisitor *)&tmp);
	}
	else {
		TmpBE4320 tmp;
		EnumeratePendingBattles(*(PendingBattleVisitor *)&tmp);
	}
}
