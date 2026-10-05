// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.
// ?rva003724B8@BfmeC986@@QAEDHHHHH@Z, retail 0x003724B8, 137 bytes.
// BfmeC986-family guarded dispatch (same callee trio as rowed bfmeGo986C
// at 0x00372541: bfmeReady986C 0x36E357, bfmePrep986C 0x36D6B4,
// bfmeSend986C 0x371166): after the ready check, walk the member list at
// +4 for any entry whose +4 field has +0x78 set (via pinned
// Object::rva0028AC4E), then prep, a two-arg check (pinned 0x36D3A3), a
// two-arg step (pinned 0x5494A0) and the five-arg send. Identity of the two
// middle callees not recovered; address-derived BfmeC986 pins.

struct Coord3D;

// The argument block 0x00372571 takes (built inline by its callers).
struct Rva00372571Params
{
	const Coord3D *m_pos;
	bool m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	bool m_1C;
};

class AIGroup
{
public:
	void rva00372571(Rva00372571Params *params, int source);
};

struct Rva0028AC4EField
{
	char m_pad[0x78];
	int m_78;
};

struct Rva0028AC4EEntry
{
	char m_pad00[4];
	Rva0028AC4EField *m_04;
};

class Object
{
public:
	const Rva0028AC4EEntry *rva0028AC4E() const;
};

struct ListNode
{
	ListNode *m_next;
	char m_pad04[4];
	Object *m_obj;
};

class BfmeC986
{
public:
	void bfmeGo986C(int a, int b, int c, int d);
	char bfmeReady986C();
	void bfmePrep986C();
	char rva0036D3A3(int a, int b);
	void rva005494A0(int a, int b);
	void bfmeSend986C(int a, int b, int c, int d, int e);
	char rva003724B8(int a, int b, int c, int, int e);
	void rva00372C22(int a, int b, int c, int d);
	void rva00372C74(int a, int b, int c, int d);
	void rva00372B09(int a, int b, int c);

private:
	char m_pad00[4];
	ListNode *m_head;
};

void BfmeC986::bfmeGo986C(int a, int b, int c, int d)
{
	if (!bfmeReady986C())
		return;

	bfmePrep986C();
	bfmeSend986C(a, b, 0, c, d);
}

char BfmeC986::rva003724B8(int a, int b, int c, int, int e)
{
	if (bfmeReady986C()) {
		char any = 0;
		for (ListNode *node = m_head->m_next; node != m_head; node = node->m_next) {
			Object *obj = node->m_obj;
			if (obj == 0)
				continue;
			const Rva0028AC4EEntry *entry = obj->rva0028AC4E();
			if (entry == 0)
				continue;
			if (entry->m_04->m_78 == 0)
				continue;
			any = 1;
		}
		if (!any)
			return 0;
		bfmePrep986C();
		if (!rva0036D3A3(a, b))
			return 0;
		rva005494A0(b, c);
		bfmeSend986C(a, b, c, e, 0);
	}
	return 1;
}

void BfmeC986::rva00372C22(int a, int b, int c, int d)
{
	if (rva003724B8(a, b, 0, c, d))
		return;
	Rva00372571Params params;
	params.m_14 |= -1;
	params.m_pos = (const Coord3D *)a;
	params.m_04 = false;
	params.m_08 = 0;
	params.m_0C = 0;
	params.m_10 = 0;
	params.m_18 = 0;
	params.m_1C = false;
	((AIGroup *)this)->rva00372571(&params, b);
}

void BfmeC986::rva00372C74(int a, int b, int c, int d)
{
	if (rva003724B8(a, b, 1, c, d))
		return;
	rva00372B09(a, 0x7FFFFFFF, b);
}
