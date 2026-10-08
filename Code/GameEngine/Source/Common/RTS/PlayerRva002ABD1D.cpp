// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002ABD1D@Player@@QAEHHH@Z, RVA 0x002ABD1D, size 43: Player count of KindOf up to limit via iterateObjects.
// Evidence: ecx pass-through to Player::iterateObjects pinned at 0x002AB08B; callback at 0x002AA531 tests Object::isKindOf and counts to limit; caller 0x003C2FEF passes kind in edi and limit 0x7ffffffe with Player in ecx and sums result.

enum KindOfType;

class Rva002AA559ThingInfo
{
public:
	char m_pad00[0x109];
	unsigned char m_flag109;
	char m_pad10A[0x114 - 0x10A];
	unsigned int m_flag114;
};

class Object
{
public:
	bool isKindOf(KindOfType t) const;
	void *rva0028BD17() const;
	void *rva0028BCF4() const;
	char m_pad00[4];
	Rva002AA559ThingInfo *m_thing;
	char m_pad08[0x74 - 0x08];
	int m_word74;
};
typedef int (__cdecl *ObjectIterateFunc)(Object *obj, void *userData);

class Player
{
public:
	int iterateObjects(ObjectIterateFunc func, void *userData) const;
	int rva002ABD1D(int kind, int limit);
};

struct Rva002ABD1DContext
{
	int m_kind;
	int m_count;
	int m_limit;
};

// The iterateObjects callback at 0x002AA531 (40B): it counts objects of the
// context's KindOf and returns 0 to stop the walk once the count passes the
// limit.
int __cdecl Rva002AA531(Object *obj, void *userData)
{
	Rva002ABD1DContext *ctx = (Rva002ABD1DContext *)userData;
	if (obj->isKindOf((KindOfType)ctx->m_kind))
	{
		if (++ctx->m_count > ctx->m_limit)
			return 0;
	}
	return 1;
}

// Retail 0x002AA559 (136 bytes): stdcall (ret 8) over two Object pointers. The
// first object's thing flags at +0x114 (bit 0x100) and +0x109 (bit 0x40) gate the
// work. The second object's dispatch at 0x28BD17 supplies the target whose slots
// 0x28 and 0x04 are called with 1; the first object's 0x28BCF4 result takes slot
// 0x08 with the second object's +0x74 word. Owner names stay address-derived.
class Rva002AA559Dispatch
{
public:
	virtual void slot00(int); virtual void slot04(int); virtual void slot08(int); virtual void slot0c(int);
	virtual void slot10(int); virtual void slot14(int); virtual void slot18(int); virtual void slot1c(int);
	virtual void slot20(int); virtual void slot24(int); virtual void slot28(int);
};

class Rva002AA559Tag
{
public:
	virtual void slot00(int); virtual void slot04(int); virtual void slot08(int);
};

void __stdcall Rva002AA559(Object *a, Object *b)
{
	if (a == 0 || b == 0)
		return;
	if (!(a->m_thing->m_flag114 & 0x100) && !(a->m_thing->m_flag109 & 0x40))
		return;
	Rva002AA559Dispatch *dispatch = (Rva002AA559Dispatch *)b->rva0028BD17();
	if (dispatch == 0)
		return;
	if (a->m_thing->m_flag114 & 0x100) {
		Rva002AA559Tag *tag = (Rva002AA559Tag *)a->rva0028BCF4();
		if (tag != 0) {
			tag->slot08(b->m_word74);
			dispatch->slot28(1);
			dispatch->slot04(1);
		}
	}
	if (a->m_thing->m_flag109 & 0x40)
		dispatch->slot28(1);
}

int Player::rva002ABD1D(int kind, int limit)
{
	Rva002ABD1DContext ctx;
	ctx.m_kind = kind;
	ctx.m_count = 0;
	ctx.m_limit = limit;
	iterateObjects((ObjectIterateFunc)Rva002AA531, &ctx);
	return ctx.m_count;
}
