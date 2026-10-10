// cl: /O1 /G7 /arch:SSE
// ??RRva00078F95Cmp@@QBE_NPBURva00078F95Item@@0@Z @0x00078F95 380B
//
// Sort predicate of the sort<Rva00078F95Item**> family (rowed in
// stlport_sort_rva00078f95.cpp; its 12 comparator call sites are this pin).
// Orders items by the dword at +4 (descending) then the owner pointer when it
// is zero; otherwise by the owner's drawable float at +0x200 then the +0x18
// handle then the rowed 0x00078C10 LOD query and finally two 28-byte slots at
// +0x110 (key/rank/order/flag) and their summed amounts. WorldBuilder twin
// 0x91dc60 in W3DHordeModelDraw.cpp (asserts "lhs drawable NULL" and "rhs
// drawable NULL") gives the comparison order; its single byte result local
// (local_65) is the shared result variable kept here.
class Rva00078C10
{
public:
	bool rva00078C10(Rva00078C10 const *other, int *out2, int *out3);

	struct Drawable
	{
		char m_pad00[0x200];
		float m_200;
	};
	struct Slot
	{
		void *m_key;
		float m_amount;
		char m_pad08[8];
		int m_order;
		int m_rank;
		unsigned char m_flag;
	};

	Drawable *getDrawable() const { return m_08; }

	char m_pad00[8];
	Drawable *m_08;
	char m_pad0C[0x0C];
	void *m_18;
	char m_pad1C[0x110 - 0x1C];
	Slot m_slots[2];
};

struct Rva00078F95Item
{
	Rva00078C10 *m_draw;
	int m_priority;
};

struct Rva00078F95Cmp
{
	bool operator()(const Rva00078F95Item *lhs, const Rva00078F95Item *rhs) const;
};

bool Rva00078F95Cmp::operator()(const Rva00078F95Item *lhs, const Rva00078F95Item *rhs) const
{
	bool result;
	if (lhs->m_priority != rhs->m_priority)
		{ result = lhs->m_priority > rhs->m_priority; goto done; }
	if (lhs->m_priority == 0)
		{ result = lhs->m_draw < rhs->m_draw; goto done; }
	{
	Rva00078C10::Drawable *ld = lhs->m_draw->getDrawable();
	if (!ld)
		{ result = true; goto done; }
	Rva00078C10::Drawable *rd = rhs->m_draw->getDrawable();
	if (!rd)
		{ result = true; goto done; }
	if (ld->m_200 != rd->m_200)
		{ result = ld->m_200 < rd->m_200; goto done; }
	}
	if (lhs->m_draw->m_18 != rhs->m_draw->m_18)
		{ result = lhs->m_draw->m_18 < rhs->m_draw->m_18; goto done; }
	{
	int lv, rv;
	if (lhs->m_draw->rva00078C10(rhs->m_draw, &lv, &rv))
	{
		if (lv != rv)
			{ result = lv < rv; goto done; }
		result = lhs->m_draw < rhs->m_draw; goto done;
	}
	}
	{
	for (int i = 0; i <= 1; ++i)
	{
		const Rva00078C10::Slot &l = lhs->m_draw->m_slots[i];
		const Rva00078C10::Slot &r = rhs->m_draw->m_slots[i];
		if (l.m_key != r.m_key)
			{ result = l.m_key < r.m_key; goto done; }
		if (l.m_key == 0)
			continue;
		if (l.m_rank != r.m_rank)
			{ result = l.m_rank < r.m_rank; goto done; }
		if (l.m_order != r.m_order)
			{ result = l.m_order < r.m_order; goto done; }
		if (l.m_flag != r.m_flag)
			{ result = l.m_flag; goto done; }
	}
	}
	{
	const Rva00078C10::Slot &l0 = lhs->m_draw->m_slots[0];
	const Rva00078C10::Slot &l1 = lhs->m_draw->m_slots[1];
	const Rva00078C10::Slot &r0 = rhs->m_draw->m_slots[0];
	const Rva00078C10::Slot &r1 = rhs->m_draw->m_slots[1];
	float lsum = (l1.m_key ? l1.m_amount : 0.0f) + l0.m_amount;
	float rsum = (r1.m_key ? r1.m_amount : 0.0f) + r0.m_amount;
	if (lsum != rsum)
		{ result = lsum < rsum; goto done; }
	result = lhs->m_draw < rhs->m_draw;
	}
done:
	return result;
}
