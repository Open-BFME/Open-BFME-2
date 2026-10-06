// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
//
// ?rva002897A8@Rva0028951F@@QAEPBVOverridable@@PAXH@Z @0x002897A8 106B.
// Threshold-plus-best scan over circular list via final-override chase.
// Retail calls this->rva0028951F(key) 0x28951F for threshold at +0x18, then walks
// list at arg1 (*arg1=sentinel, *sentinel=head) via head at +0 until sentinel,
// chases rowed Overridable::friend_getFinalOverride 0x288609 on edi+8 filters via
// TU-local noinline copy of rowed Rva0028867DCheck 0x28867D logic for static ESI call shape
// keeps smallest +0x18 above threshold.
// Evidence: chain lane (calls 0x28951F just landed); caller 0x289BE0 passes
// ecx through plus pushes list ptr and int key (thiscall with ret 8).
extern class GameLogic *TheGameLogic;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	void *m_v0;
	Overridable *m_next;
	char m_pad08[0x10];
	int m_val18;
};

struct ListNode
{
	ListNode *m_next;
	int m_pad04;
	Overridable m_over;
};

struct Inner
{
	ListNode *m_head;
};

struct Outer
{
	Inner *m_inner;
};

class BfmeGlob939D
{
public:
	char bfmeCall939D();
};

#define TheBfmeGlob (*(BfmeGlob939D **)&TheGameLogic)

struct Rva0028867DData
{
	char m_pad[0x101];
	unsigned char m_b101;
	unsigned char m_b102;
};

__declspec(noinline) static bool Rva0028867DCheck(const void *p)
{
	const Rva0028867DData *d = (const Rva0028867DData *)p;
	if (TheBfmeGlob->bfmeCall939D())
		return d->m_b101 == 0;
	return d->m_b102 == 0;
}

class Rva0028951F
{
public:
	const Overridable *rva0028951F(int key);
	const Overridable *rva002897A8(void *outer, int key);
};

const Overridable *Rva0028951F::rva002897A8(void *outer, int key)
{
	const Overridable *f = rva0028951F(key);
	int threshold = 0;
	if (f)
		threshold = f->m_val18;
	const Overridable *best = 0;
	int bestVal = 0x7fffffff;
	Outer *o = (Outer *)outer;
	Inner *s = o->m_inner;
	ListNode *n = s->m_head;
	for (; n != (ListNode *)o->m_inner; n = n->m_next)
	{
		const Overridable *g = ((Overridable *)((char *)n + 8))->friend_getFinalOverride();
		if (!Rva0028867DCheck(g))
			continue;
		int v = g->m_val18;
		if (v <= threshold)
			continue;
		if (v >= bestVal)
			continue;
		bestVal = v;
		best = g;
	}
	return best;
}
