// cl: /MD
//
// ?rva004A57DB@Rva004A54A8@@QAEXMM@Z @0x004A57DB 112B: ranged FX loop with bit gate.
// Loads virt via m08 plus 0x254 slot 0x3C, saves result, iterates array at
// m04 plus 0xAC to 0xB0 step 8 filtering float at +0 against low/high args
// plus bit test of result plus 0x10 via mask 1 plus flags at m04 plus 0x4C,
// then rowed FXList doFXObj 0x000B2235 with elem plus 4 plus m08 plus null.
// Evidence: retail ebp frame plus movss/comiss plus call-indirect plus
// dec/inc/shl bit plus add-8/cmp loop, neighbours Rva004A54A8 xfer/dtor,
// caller 0x004A613B, callee doFXObj row.
class Object;
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

struct BitHolder004A57DB
{
	char m_pad00[0x10];
	int m_bit10;
};

class Virt004A57DB
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual BitHolder004A57DB *f15();
};

struct Obj004A57DB
{
	char m_pad00[0x254];
	Virt004A57DB *m_virt254;
};

struct Elem004A57DB
{
	float m_thresh00;
	const FXList *m_fx04;
};

struct Mod004A57DB
{
	char m_pad00[0x4C];
	unsigned int m_flags4C;
	char m_pad50[0xAC - 0x50];
	Elem004A57DB *m_beginAC;
	Elem004A57DB *m_endB0;
};

class Rva004A54A8
{
public:
	virtual ~Rva004A54A8();
	void rva004A57DB(float low, float high);
private:
	Mod004A57DB *m_mod04;
	Obj004A57DB *m_obj08;
};

void Rva004A54A8::rva004A57DB(float low, float high)
{
	Mod004A57DB *mod = m_mod04;
	BitHolder004A57DB *bh = m_obj08->m_virt254->f15();
	for (Elem004A57DB *it = mod->m_beginAC; it != mod->m_endB0; ++it)
	{
		if (!(it->m_thresh00 > low))
			continue;
		if (!(it->m_thresh00 <= high))
			continue;
		if (bh)
		{
			int bit = bh->m_bit10;
			unsigned int mask = 0;
			--bit;
			++mask;
			mask <<= bit;
			if (!(mod->m_flags4C & mask))
				continue;
		}
		FXList::doFXObj(it->m_fx04, (const Object *)m_obj08, 0);
	}
}
