// cl: /O1 /DNDEBUG /MD
//
// ?rva002E10BD@Rva002E10BDOwner@@QAEXPAVCreateAHeroData@@@Z @0x002E10BD 65B:
// vector find-erase-forward (thiscall, 1 arg, void). Finds the arg in
// m_1b8 via pinned 0x0020E873 (same body as rowed _STL::find); if
// present erases it via pinned 0x001FF51F (ICF-shared erase address)
// and forwards [arg+0x78] through pinned GameLogic 0x0023D007.
// Plain begin/end struct to avoid STL codegen variance; pins carry
// honest ICF notes. Exact identities unproven.
class CreateAHeroData;

class GameLogic
{
public:
	void rva0023D007(int x);
};
extern GameLogic *TheGameLogic;

struct Rva002E10BDVec
{
	void *m_begin;
	void *m_end;
	void rva001FF51FErase(int it);
};

void *rva0020E873Find(int b, int e, int v);

class Rva002E10BDOwner
{
public:
	void rva002E10BD(CreateAHeroData *o);
	void rva002E10FE(int p);

private:
	char m_pad[0x1b8];
	Rva002E10BDVec m_1b8;
};

// ?rva002E10BD@Rva002E10BDOwner@@QAEXPAVCreateAHeroData@@@Z
void Rva002E10BDOwner::rva002E10BD(CreateAHeroData *o)
{
	void *end = *(void **)((char *)this + 0x1bc);
	Rva002E10BDVec *v = &m_1b8;
	void *it = rva0020E873Find((int)v->m_begin, (int)end, (int)&o);
	if (it == end)
		return;
	v->rva001FF51FErase((int)it);
	TheGameLogic->rva0023D007(*(const int *)((const char *)o + 0x78));
}

// ?rva002E10FE@Rva002E10BDOwner@@QAEXH@Z
void Rva002E10BDOwner::rva002E10FE(int p)
{
	int o = **(int **)p;
	TheGameLogic->rva0023D007(*(const int *)(o + 0x78));
	Rva002E10BDVec *v = &m_1b8;
	v->rva001FF51FErase(*(int *)p);
}
