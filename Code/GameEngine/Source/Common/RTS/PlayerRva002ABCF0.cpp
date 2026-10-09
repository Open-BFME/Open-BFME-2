// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002ABCF0@Player@@QAEHEPAH@Z, RVA 0x002ABCF0, size 45: Player iterate with byte flag and int result via iterateObjects.
// Evidence: ecx pass-through to Player::iterateObjects pinned at 0x002AB08B; callback at 0x002AB01C (FUN_006ab01c) with 8B userdata {flag result}; caller 0x003BCEA7 passes flag and out pointer with Player in ecx and uses return; neighbours PlayerRva002ABD1D.cpp.
//
// ?Rva002AA497Compare@@YAHPBVObject@@0@Z @0x002AA497 (132B): orders two
// objects. Objects whose template has bit 0x20000 of the +0x108 kind word
// rank above the rest and among themselves by id (+0x74); otherwise by
// the template figure at pinned 0x0033A69A (controlling player, 0, -1),
// zero for a template-less object. Callers: the 0x002AB01C callback below
// and the unclaimed 0x003BCE69. The figure is read through an inline helper:
// a local template pointer tested once in the body lets cl drop the null
// test after the earlier dereference, which retail keeps.
//
// ?Rva002AB01C@@YAHPAVObject@@PAX@Z @0x002AB01C (78B): the callback below
// keeps the best-ranked object whose template has +0x108 bit 0x80 and whose
// +0x438 flags lack bit 0 (and bit 3 when the context flag is set); it
// always answers 1. Names are address-derived.

class Player;
class Object;

class ThingTemplate
{
public:
	int rva0033A69A(const class Player *who, int a, int b) const;	// row 0x0033A69A spelling

	char m_pad[0x108];
	unsigned int m_kindOf108;
};

class Object
{
public:
	Player *getControllingPlayer() const;

	char m_pad0[4];
	const ThingTemplate *m_template;
	char m_pad8[0x74 - 8];
	int m_id;
	char m_pad78[0x438 - 0x78];
	unsigned char m_flags438;
};

typedef int (__cdecl *ObjectIterateFunc)(Object *obj, void *userData);

class Player
{
public:
	int iterateObjects(ObjectIterateFunc func, void *userData) const;
	int rva002ABCF0(unsigned char flag, int *out);
};

struct Rva002ABCF0Context
{
	unsigned char m_flag;
	Object *m_best;
};

static inline int costOf(const Object *obj)
{
	const ThingTemplate *tmpl = obj->m_template;
	return tmpl ? tmpl->rva0033A69A((const class Player *)obj->getControllingPlayer(), 0, -1) : 0;
}

int Rva002AA497Compare(const Object *a, const Object *b)
{
	if (a->m_template->m_kindOf108 & 0x20000)
	{
		if (b->m_template->m_kindOf108 & 0x20000)
			return b->m_id - a->m_id;
		return 1;
	}
	if (b->m_template->m_kindOf108 & 0x20000)
		return -1;
	return costOf(a) - costOf(b);
}

int __cdecl Rva002AB01C(Object *obj, void *userData)
{
	if (obj)
	{
		Rva002ABCF0Context *ctx = (Rva002ABCF0Context *)userData;
		if ((!ctx->m_flag || !(obj->m_flags438 & 8))
			&& (obj->m_template->m_kindOf108 & 0x80)
			&& !(obj->m_flags438 & 1))
		{
			if (!ctx->m_best || Rva002AA497Compare(obj, ctx->m_best) > 0)
				ctx->m_best = obj;
		}
	}
	return 1;
}

int Player::rva002ABCF0(unsigned char flag, int *out)
{
	Rva002ABCF0Context ctx;
	ctx.m_best = 0;
	ctx.m_flag = flag;
	iterateObjects(Rva002AB01C, &ctx);
	if (out)
		*out = (int)ctx.m_best;
	return (int)ctx.m_best;
}
