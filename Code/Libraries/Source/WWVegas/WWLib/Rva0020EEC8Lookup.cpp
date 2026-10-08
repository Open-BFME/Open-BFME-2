// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?SetRegionReinforcements@LivingWorldRegionManager@@QAEXHHHHHHH@Z @0x0020EEC8 44B
// Index lookup then 6-arg forward: runs rowed 0x0020EAF6(idx) on this (passthrough this), returns on null, else runs pinned 0x003F1AB9(a2-a7) on the result. 7 int args keep HHHHHHH mangling; thiscall ret 0x1C.
class Rva0020E89C;
class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);
};
class Rva003F1AB9
{
public:
	void rva003F1AB9(int a1, int a2, int a3, int a4, int a5, int a6);
};
class Rva0020E89C;
class LivingWorldRegionManager
{
public:
	void SetRegionReinforcements(int idx, int a2, int a3, int a4, int a5, int a6, int a7);
};
void LivingWorldRegionManager::SetRegionReinforcements(int idx, int a2, int a3, int a4, int a5, int a6, int a7)
{
	Rva0020E89C *p = ((Rva0020EAF6View *)this)->rva0020EAF6(idx);
	if (p == 0)
		return;
	((Rva003F1AB9 *)p)->rva003F1AB9(a2, a3, a4, a5, a6, a7);
}