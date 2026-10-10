// ?rva002E9EA7@Pathfinder@@QAE_NPAVObject@@HHW4PathfindLayerEnum@@HHPAH@Z
// partial score=0.8203970778324837 date=2026-10-10
// ?rva002E9EA7@Pathfinder@@QAE_NPAVObject@@HHW4PathfindLayerEnum@@HHPAH@Z
// partial score=0.8 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// Dump lane range 13: ?rva002E9EA7 @0x002E9EA7 531B. Pathfinder
// bool query over a cell rectangle: flag/divisor setup from the Object
// inner (m_115 bit 0x20 gate with a TheTerrainLogic slot-50 probe, m_113
// bit 4 + m_109 bit 1 override), plus-one framing, then a getCell grid
// walk with tag-nibble dispatch, Object relationship/bool filters over
// two occupant lists, and a hit counter. Identity unproven beyond the
// rowed callees; names address-derived.
void __cdecl rva002E79A8(int a1, unsigned char a2, int a3, int a4, int a5);

struct Rva002E8BCFSrc
{
	char _00[0x10];
	int m10;
	char _14;
	bool m15;
};

// 0x2E79A8 writes 3 floats through a1 ([eax], [eax+4], [eax+8]).
struct Rva002E79A8Out
{
	float m_0;
	float m_4;
	float m_8;
};

enum Relationship
{
	REL_0 = 0,
	REL_1 = 1,
	REL_2 = 2
};

enum PathfindLayerEnum
{
	PF_LAYER_0 = 0
};

struct ObjectInner
{
	char _00[0x109];
	unsigned char m_109;
	char _10A[0x113 - 0x10A];
	unsigned char m_113;
	char _114;
	unsigned char m_115;
};

class Object
{
public:
	bool rva0028AFBB() const;
	Relationship getRelationship(const Object *other) const;
	bool IsAtGoalPosition() const;
	char _00[4];
	ObjectInner *m_04;
	char _08[0x74 - 8];
	int m_74;
	char _78[0x258 - 0x78];
	void *m_258;
	char _25C[0x274 - 0x25C];
	Object *m_274;
};

class Rva0006E009DwordField
{
public:
	int get() const;
};

struct Rva002E9EA7Occ1
{
	Rva002E9EA7Occ1 *m_next;
	char _04[4];
	Object *m_obj;
};

struct Rva002E9EA7Head1
{
	char _00[0x14];
	Rva002E9EA7Occ1 *m_14;
};

struct Rva002E9EA7Occ2
{
	Rva002E9EA7Occ2 *m_next;
	char _04[4];
	Object *m_obj;
};

class PathfindCell
{
public:
	PathfindCell *m_0;
	char _04[8];
	int m_C;
	char _10[0x10];
	Rva002E9EA7Occ2 *m_20;
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);
	bool rva002E9EA7(Object *a1, int a2, int a3, PathfindLayerEnum a4, int a5i, int a5b, int *a6);
};

class Rva002E6C23
{
public:
	bool rva002E6C23(int v);
};

// TheTerrainLogic vtable slot 50 (+0xC8) bool probe over the 0x1C-byte
// 0x2E79A8 output. Earlier slots unmodelled.
class __declspec(novtable) TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual bool rva002E9EA7Slot50(void *tmp) = 0;
};

extern TerrainLogic *TheTerrainLogic;

// ?rva002E9EA7@Pathfinder@@QAE_NPAVObject@@HHW4PathfindLayerEnum@@HEPAH@Z @0x002E9EA7 531B.
bool Pathfinder::rva002E9EA7(Object *a1, int a2, int a3, PathfindLayerEnum a4, int a5i, int a5b, int *a6)
{
	Rva002E79A8Out tmp;
	int u;
	unsigned char flag;
	int dv;
	if ((a1->m_04->m_115 & 0x20) != 0)
	{
		u = 1;
		if (a4 != u || (rva002E79A8((int)&tmp, 1, a2, a3, 1), TheTerrainLogic->rva002E9EA7Slot50(&tmp)))
		{
			dv = u;
			flag = 1;
		}
		else
		{
			flag = a5b;
			dv = a5i;
		}
	}
	else
	{
		u = 1;
		flag = a5b;
		dv = a5i;
	}
	if (((((Object *volatile&)a1)->m_04->m_113 & 4) != 0) && ((a1->m_04->m_109 & 1) != 0) && (a4 != u))
	{
		dv = u;
		flag = 0;
	}
	u = (flag != 0) ? dv + 1 : dv;
	*a6 = 0;
	a5i = 0;
	int v1 = 0;
	if (a1->m_258 != 0)
	{
		a5i = ((Rva0006E009DwordField *)a1->m_258)->get();
		v1 = a1->m_74;
	}
	int e = a2 - dv;
	int xEnd = a2 + u;
	a2 = e;
	if (e >= xEnd)
		return true;
	int e2 = a3 + u;
	a3 = a3 - dv;
	for (;;)
	{
		a5b = a3;
		if (a5b < e2)
		{
			do
			{
				PathfindCell *cell = getCell(a4, a2, a5b);
				if (cell == 0)
					return false;
				int tag = cell->m_C;
				if ((tag & 15) == 5)
					return false;
				if ((((unsigned char)(tag >> 18) & 1) != 0) && a1->rva0028AFBB())
					return false;
				int tag2 = cell->m_C;
				int k = tag2 & 15;
				if (k == 2)
					return false;
				if (k == 4)
				{
					if (((Rva002E6C23 *)cell)->rva002E6C23(a5i))
						continue;
					return false;
				}
				if (k == 5 || k == 6)
					return false;
				if ((((unsigned char)(tag2 >> 18) & 1) != 0) && a1->rva0028AFBB())
					return false;
				void *n1 = cell->m_0;
				Rva002E9EA7Occ1 *b = n1 ? ((Rva002E9EA7Head1 *)n1)->m_14 : 0;
				while (b != 0)
				{
					Object *o = b->m_obj;
					if (o->m_74 != v1 && o->m_74 != a5i && o->m_274 != a1)
					{
						if (a1->getRelationship(o) == REL_2)
							(*a6)++;
						else if (!o->IsAtGoalPosition())
							return false;
					}
					b = b->m_next;
				}
				cell = (PathfindCell *)cell->m_0;
				Rva002E9EA7Occ2 *s = cell ? cell->m_20 : 0;
				while (s != 0)
				{
					Object *o = s->m_obj;
					if (o->m_74 != v1 && o->m_274 != a1)
					{
						if (a1->getRelationship(o) == REL_2)
							*a6 += 3;
						else
							(*a6)++;
					}
					s = s->m_next;
				}
				a5b++;
			} while (a5b < e2);
		}
		a2++;
		if (a2 >= xEnd)
			break;
	}
	return true;
}
