// ?rva002E9D09@Rva002E9D09@@QAEHPAVObject@@HH@Z
// partial score=0.99 date=2026-10-06
// ?rva002E9D09@Rva002E9D09@@QAEHPAVObject@@HH@Z
// partial score=0.7 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
// Dump lane range 13: ?rva002E9D09 @0x002E9D09 414B. Guarded object query:
// an Rva002E8BCF-gated Rva002E6DC4 check, cell-flag tag/bit dispatch on the
// target, then a for-walk over the target's node list with relationship,
// KindOf-bit, counter and retest filters. Identities unproven.
enum Relationship
{
	REL_0 = 0,
	REL_1 = 1,
	REL_2 = 2
};
class Object;
struct Rva002E9D09Node
{
	Rva002E9D09Node *m_next;
	char m_pad4[4];
	Object *m_obj;
};
struct ObjectSub4
{
	char m_pad0[0x109];
	unsigned char m_109;
	char m_pad10A[0xD];
	unsigned char m_117;
	char m_pad118[7];
	unsigned char m_11F;
	int m_120;
	char m_pad124[0x448];
	int m_56C;
	char m_pad570[0xC4];
	bool m_634;
};
class Object
{
public:
	bool rva0028AFBB() const;
	bool rva0028ADB0() const;
	Object *rva002931F5(bool flag);
	Relationship getRelationship(const Object *other) const;
	Object *m_0;
	ObjectSub4 *m_4;
	Object *m_8;
	int m_flagsC;
	int m_pad10;
	Rva002E9D09Node *m_node14;
	char m_pad18[0x5C];
	int m_74;
};
struct Rva002E8BCFSrc
{
	char _00[0x10];
	int m10;
	char _14;
	bool m15;
};
class Rva002E8BCF
{
public:
	Rva002E8BCF(Rva002E8BCFSrc const *src, bool a, int b, bool c);
	int m0;
	bool m4;
	bool m5;
	int m8;
	bool mC;
};
class Rva002E6DC4
{
public:
	bool rva002E6DC4(void *a_raw, void *b_raw);
};
class Rva002E6C23
{
public:
	bool rva002E6C23(int v);
};
class Rva0029493F
{
public:
	bool rva0029493F(int a, int b);
};
class Rva002E9D09
{
public:
		int rva002E9D09(Object *a1, int a2, int a3);
private:
	Rva002E6DC4 *m_check0;
	Object *m_holder4;
	int *m_counter8;
	bool m_cC;
	int m_10;
	bool m_14;
	Rva002E8BCFSrc *m_18;
};
// ?rva002E9D09@Rva002E9D09@@QAE_NPAVObject@@HH@Z @0x002E9D09 414B.
int Rva002E9D09::rva002E9D09(Object *a1, int a2, int a3)
{
	if (m_18 != 0)
	{
		if ((m_holder4->m_4->m_11F & 4) != 0)
		{
			unsigned count = m_holder4->m_4->m_56C;
			unsigned char b0b = m_holder4->m_4->m_634;
			Rva002E8BCF tmp(m_18, b0b == 0, count - 1, m_holder4->rva0028AFBB());
			if (!m_check0->rva002E6DC4(&tmp, a1))
				return 1;
		}
	}
	unsigned flags = (unsigned)a1->m_flagsC;
	if ((flags & 0xF) == 5)
		return 1;
	unsigned char b18 = (unsigned char)(flags >> 18);
	if ((b18 & 1) != 0)
	{
		if (m_holder4->rva0028AFBB())
			return 1;
	}
	int tag = a1->m_flagsC & 0xF;
	if (tag == 2)
		return 1;
	if (tag == 4)
		return ((Rva002E6C23 *)a1)->rva002E6C23(m_10) == 0;
	if (tag == 5)
		return 1;
	if (tag == 6)
		return 1;
	if (m_14 != 0)
		return 0;
	Object *a1copy = a1;
	bool go = false;
	Rva002E9D09Node *node = 0;
	Object *res = m_holder4->rva002931F5(go);
	Object *sub = a1copy->m_0;
	a1 = res;
	if (sub != (Object *)node)
		node = sub->m_node14;
	for (; node != 0; node = node->m_next)
	{
		if (node->m_obj == m_holder4)
			continue;
		if (a1 != 0)
		{
			if (node->m_obj->rva002931F5(false) == a1)
				continue;
		}
		Object *o = node->m_obj;
		if (o->m_74 == m_10)
			continue;
		if (m_holder4->getRelationship(o) == REL_2)
		{
			if ((m_holder4->m_4->m_120 & 0x100000) != 0)
			{
				if ((o->m_4->m_120 & 0x100000) == 0)
					continue;
				return 1;
			}
			if (m_cC == 0)
				return 1;
			++*m_counter8;
		}
		else
		{
			if (!o->rva0028ADB0())
				continue;
			if (((Rva0029493F *)m_holder4)->rva0029493F((int)o, 2))
				continue;
			if ((m_holder4->m_4->m_117 & 0x20) == 0)
				return 1;
			if ((o->m_4->m_109 & 1) == 0)
				return 1;
		}
	}
	return 0;
}
