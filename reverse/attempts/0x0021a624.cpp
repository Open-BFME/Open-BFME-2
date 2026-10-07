// ?UnregisterCreateAHeroAtRva0021A624@@YAXPAVCreateAHeroData@@@Z
// partial score=0.978 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE /G7
// stlport
// ?UnregisterCreateAHeroAtRva0021A624@@YAXPAVCreateAHeroData@@@Z @0x0021A624 45B.
// Removes a CreateAHeroData* from the global hero registry vector at
// 0x009FE358 via find plus vector erase. Evidence: pin
// ?UnregisterCreateAHeroAtRva0021A624@@YAXPAVCreateAHeroData@@@Z; caller
// 0x004092BA in ??1CreateAHeroData@@UAE@XZ; rowed find 0x0020E873 plus rowed
// vector erase 0x001FF51F; globals g_00DFE358 begin plus g_00DFE35C end.
#include <vector>
#include <algorithm>
class CreateAHeroData;
extern unsigned g_00DFE358;
void __cdecl UnregisterCreateAHeroAtRva0021A624(CreateAHeroData *p);
void __cdecl UnregisterCreateAHeroAtRva0021A624(CreateAHeroData *p)
{
	typedef _STL::vector<CreateAHeroData *> Vec;
	Vec &v = *(Vec *)&g_00DFE358;
	CreateAHeroData **beg = (CreateAHeroData **)g_00DFE358;
	CreateAHeroData **end = (CreateAHeroData **)*(unsigned int *)((char *)&g_00DFE358 + 4);
	CreateAHeroData **found = _STL::find(beg, end, p);
	if (found == end)
		return;
	((_STL::vector<void *> *)&v)->erase((void **)found);
}
