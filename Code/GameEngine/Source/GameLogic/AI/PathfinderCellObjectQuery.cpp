// cl: /O1 /DNDEBUG /MD
// Native query: ?rva002E9D09 @0x002E9D09 414B. Guarded object query:
// an Rva002E8BCF-gated Rva002E6DC4 check, cell-flag tag/bit dispatch on the
// cell flags, then a for-walk over the cell-info node list with relationship,
// KindOf-bit, counter and retest filters. Original query identity is unknown.
// Existing opaque visitor ABI in symbols.csv uses Object* for the first word;
// preserve that borrowed signature for rectangle 002EED80 and polygon callers.
// Actual cell flags +0x0C and cell-info node head +0x14 are independent target
// facts and use explicit pointer-only views, not an Object layout claim.
// Object/ThingTemplate accessed offsets follow native414 and current helpers.
// Bank donor 002E9D09 supplied the complete control flow; explicit else node=0
// preserves retail's shared XOR EDI/PUSH EDI and final loop test.
// Native 002E9D09..002E9EA7 RET12 proves all 414 bytes and caller ABI.
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
	bool IsAtGoalPosition() const;
	bool rva0029493F(Object *other, int test);
	Object *rva002931F5(bool flag);
	Relationship getRelationship(const Object *other) const;
	char m_pad00[4];
	ObjectSub4 *m_4;
	char m_pad08[0x74 - 8];
	int m_74;
};

struct Rva002E9D09CellInfoView { char m_pad00[0x14]; Rva002E9D09Node *m_nodes14; };
struct Rva002E9D09CellView { Rva002E9D09CellInfoView *m_info; char m_pad04[8]; unsigned m_flagsC; };

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
// 0x002E6C23 is the row ?IsObstaclePresent@PathfindCell@@QBE_NW4ObjectID@@@Z
// (Rva002E6C23Obstacle.cpp, WB lead PathfindCell::IsObstaclePresent).
enum ObjectID {};
class PathfindCell
{
public:
	bool IsObstaclePresent(ObjectID objID) const;
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
	unsigned flags = (unsigned)((Rva002E9D09CellView *)a1)->m_flagsC;
	if ((flags & 0xF) == 5)
		return 1;
	unsigned char b18 = (unsigned char)(flags >> 18);
	if ((b18 & 1) != 0)
	{
		if (m_holder4->rva0028AFBB())
			return 1;
	}
	int tag = ((Rva002E9D09CellView *)a1)->m_flagsC & 0xF;
	if (tag == 2)
		return 1;
	if (tag == 4)
		return ((PathfindCell *)a1)->IsObstaclePresent((ObjectID)m_10) == 0;
	if (tag == 5)
		return 1;
	if (tag == 6)
		return 1;
	if (m_14 != 0)
		return 0;
Object *a1copy = a1;
Rva002E9D09Node *node = 0;
Object *res = m_holder4->rva002931F5(false);
Rva002E9D09CellInfoView *sub = ((Rva002E9D09CellView *)a1copy)->m_info;
a1 = res;
if(sub) node=sub->m_nodes14; else node=0;
for (;node;node=node->m_next)
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
			if (!o->IsAtGoalPosition())
				continue;
			if (m_holder4->rva0029493F(o, 2))
				continue;
			if ((m_holder4->m_4->m_117 & 0x20) == 0)
				return 1;
			if ((o->m_4->m_109 & 1) == 0)
				return 1;
		}
	}
	return 0;
}
