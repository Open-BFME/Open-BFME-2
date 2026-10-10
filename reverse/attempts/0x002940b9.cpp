// ?rva002940B9@Object@@QAE_NPBVUpgradeTemplate@@@Z
// partial score=0.93 date=2026-10-11
// ?bfmeHas985C@BfmeArg985@@QAEDH@Z
// partial score=0.93 date=2026-10-06
// cl: /O1 /G7
// stlport
// ?bfmeHas985C@BfmeArg985@@QAEDH@Z RVA 0x002940B9 305B
// Evidence: LINK BONUS 5 files call this name; pin-only callee of BfmeC985::bfmeGo985C at 0x00261130; Object::affectedByUpgrade per CommandButtonIsReady donor ZH Object.cpp affectedByUpgrade and BFME1 ObjectUpgrades.cpp; callers TeamRva0039E8EB HordeContain CommandButtonIsReady Rva003972D3Apply Rva00397357; prev 0x00293E64 next 0x0029439D share /O1 /G7.
struct BfmeFixedStorage128
{
	BfmeFixedStorage128(const BfmeFixedStorage128&);
	unsigned char bytes[128];
};

namespace _STL
{
template<unsigned N> struct _Base_bitset;
template<> struct _Base_bitset<32>
{
	void _M_do_or(const _Base_bitset<32>&);
	unsigned long _M_w[32];
};
}

class BfmeTab1026
{
};

class Player;
class Object;

class UpgradeTemplate
{
public:
	char m_pad00[0x38];
	int m_bit38;
	char m_pad3C[0x80 - 0x3C];
	BfmeTab1026 m_tab80;
};

class Player
{
public:
	bool rva002AB2D9(BfmeTab1026 *tab, bool flag) const;
	bool rva002AB390(BfmeTab1026 *tab) const;
private:
	char m_pad00[0x13C];
public:
	BfmeFixedStorage128 m_mask13C;
};

class BehaviorUpgrade
{
public:
	virtual void s00();
	virtual void s01();
	virtual bool wouldUpgrade(const BfmeFixedStorage128 &mask) const;
};

class BehaviorInterface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual BehaviorUpgrade *getUpgrade();
};

class BfmeObjectModule
{
public:
	virtual void slot0();
private:
	unsigned int m_data[2];
};

class BehaviorModule : public BfmeObjectModule, public BehaviorInterface
{
};

struct Out
{
	void *a;
	void *b;
};

struct Node
{
	Node *m_next;
	void *m_unk4;
	Object *m_obj;
};

template<int N> class Slots : public Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template<> class Slots<0>
{
};

class ContainIface : public Slots<70>
{
public:
	virtual void getList(Out *out) = 0;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	bool rva002931BA();
	Object *rva002931F5(bool checkProducer);
	bool rva0028D9E5(int bit) const;
public:
	char m_pad00[0x244];
	BehaviorModule **m_modules244;
	char m_pad248[0x250 - 0x248];
	ContainIface *m_contain250;
	char m_pad254[0x284 - 0x254];
	_STL::_Base_bitset<32> m_mask284;
};

class BfmeArg985
{
public:
	char bfmeHas985C(int v);
};

char BfmeArg985::bfmeHas985C(int v)
{
	UpgradeTemplate *upgrade = (UpgradeTemplate *)v;
	Object *self = (Object *)this;
	if (upgrade == 0)
		return 0;
	Player *player = self->getControllingPlayer();
	if (player == 0)
		return 0;
	if (self->rva002931BA())
	{
		Object *related = self->rva002931F5(false);
		if (related != 0)
		{
			if (related->rva0028D9E5(upgrade->m_bit38))
				goto haveMask;
		}
	}
checkPlayer:
	{
		BfmeTab1026 *tab = &upgrade->m_tab80;
		if (player->rva002AB2D9(tab, true))
			goto haveMask;
		if (!player->rva002AB390(tab))
			return 0;
	}
haveMask:
	{
		const BfmeFixedStorage128 &srcMask = player->m_mask13C;
		BfmeFixedStorage128 mask(srcMask);
		const _STL::_Base_bitset<32> &otherMask = (const _STL::_Base_bitset<32> &)self->m_mask284;
		((_STL::_Base_bitset<32> *)&mask)->_M_do_or(otherMask);
		unsigned int bit = (unsigned int)upgrade->m_bit38;
		((unsigned int *)&mask)[bit >> 5] |= 1u << (bit & 31);
		for (BehaviorModule **m = self->m_modules244; *m; ++m)
		{
			BehaviorInterface *beh = *m;
			BehaviorUpgrade *up = beh->getUpgrade();
			if (up == 0)
				continue;
			if (up->wouldUpgrade(mask))
				return 1;
		}
		self = (Object *)self->m_contain250;
		if (self == 0)
			return 0;
		Out out;
		((ContainIface *)self)->getList(&out);
		Node *head = *(Node **)out.b;
		Node *cur = head->m_next;
		if (cur == head)
			return 0;
		do
		{
			Object *o = cur->m_obj;
			if (((BfmeArg985 *)o)->bfmeHas985C(v) != 0)
				return 1;
			cur = cur->m_next;
		} while (cur != *(Node **)out.b);
		return 0;
	}
}
