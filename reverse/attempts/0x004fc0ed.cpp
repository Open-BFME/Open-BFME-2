// ?rva004FC0ED@Rva004FC0ED@@QAEXABV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z
// partial score=0.89 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
//
// ?rva004FC0ED@Rva004FC0ED@@QAEXABV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z @0x004FC0ED 94B.
// Pushes each non-null element of the argument vector into this+8 through rowed
// push_back 0x004DFCB0, then passes whether rowed 0x002B2B66 on TheLivingWorldLogic
// equals rowed 0x004FBED6 on this to rowed 0x004FBDB0. Owner class unproven.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include <vector>

class ModuleData;

class Rva002BA8F1Logic;

class Rva002B2B66
{
public:
	int rva002B2B66();
};

class RegionAwardDispute
{
public:
	int GetResolvableBy();
};

class Rva004FBDB0
{
public:
	void rva004FBDB0(int arg);
};

class Rva004FC0ED
{
public:
	void rva004FC0ED(const _STL::vector<const ModuleData *> &src);
private:
	char m_pad08[8];
	_STL::vector<const ModuleData *> m_items;
};

void Rva004FC0ED::rva004FC0ED(const _STL::vector<const ModuleData *> &src)
{
	for (unsigned i = 0; i < src.size(); ++i)
		if (src[i] != 0)
			m_items.push_back(src[i]);
	int logic = ((Rva002B2B66 *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->rva002B2B66();
	((Rva004FBDB0 *)this)->rva004FBDB0(logic == ((RegionAwardDispute *)this)->GetResolvableBy());
}
