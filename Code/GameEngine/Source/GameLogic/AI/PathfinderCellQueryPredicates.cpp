// cl: /O1 /DNDEBUG /MD
// Dump lane range 13: contiguous Pathfinder cell-query predicates around
// 0x002E9897. Each forwards (this, b, a) to the rowed lookup 0x001E3647
// (forward push order), then tests the low nibble of the dword at +0x0C
// (plus bit 16/17) of the returned record. thiscall with ecx passthrough;
// ?rva names: class lead from the 0x002E9871 Pathfinder pin, identities unproven.
struct Coord3D
{
	float x, y, z;
};
class Pathfinder
{
public:
 	void *rva001E3647Pos(int a, const Coord3D *pos);
	int GetGroundLayer(const Coord3D *pos);
	bool IsWaterCell(int a, int b);
	bool IsCliffCell(int a, int b);
	int isBlockedGateObstacleCell(int a, int b);
	int IsNonPinchedCliffCell(int a, int b);
	bool IsPointOnWall(int a, bool b);
	bool IsImpassableCell(int a, int b);
	bool IsBuildRestrictedCell(int a, bool b, bool c, int d);
	void GetCellType(int a1, void *a2, void *a3, void *a4, int a5);
private:
	char m_pad000[0x10];
	int m_unk0010; // +0x10 null-guard read by GetGroundLayer
};
struct Rva001E3647Result
{
	char m_pad[0x0C];
	unsigned int m_flags;
};
// ?GetGroundLayer@Pathfinder@@QAEHPBUCoord3D@@@Z @0x002E9871 38B: +0x10-gated
// cell-field query: guard or null -> 1, else (flags>>4)&0x3F. Converts the
// existing same-name pin into a row.
int Pathfinder::GetGroundLayer(const Coord3D *pos)
{
	if (m_unk0010 != 0)
	{
		Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647Pos(1, pos);
		if (rec != 0)
			return (rec->m_flags >> 4) & 0x3F;
	}
	return 1;
}
// ?IsBuildRestrictedCell@Pathfinder@@QAE_NH_N_NH@Z @0x002E996E 79B: 4-arg combined
// query: null->true; flag=(tag==2); unless b, flag|=tag in {1,7}; unless c,
// flag|=tag==5.
// ?Pathfinder::IsBuildRestrictedCell present-unmatched
bool Pathfinder::IsBuildRestrictedCell(int a, bool b, bool c, int d)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647Pos(d, (const Coord3D *)a);
	bool out;
	if (rec == 0)
		out = true;
	else
	{
		unsigned val = rec->m_flags;
		val &= 0x0F;
		bool flag = val == 2;
		if (!b)
		{
			if (flag || val == 1 || val == 7)
				flag = true;
		}
		if (!c)
		{
			if (flag || val == 5)
				flag = true;
		}
		out = flag;
	}
	return out;
}
// ?GetCellType@Pathfinder@@QAEXHPAXPAXPAXH@Z @0x002E99BD 60B: ebp-frame
// split-out: *a2=nonnull, *a4=tag, *a3=bit18.
void Pathfinder::GetCellType(int a1, void *a2, void *a3, void *a4, int a5)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647Pos(a5, (const Coord3D *)a1);
	if (rec == 0)
	{
		*(unsigned char *)a2 = 0;
	}
	else
	{
		*(unsigned char *)a2 = 1;
		unsigned int val = rec->m_flags;
		*(unsigned int *)a4 = val & 0x0F;
		unsigned int val2 = rec->m_flags;
		*(unsigned char *)a3 = (unsigned char)((val2 >> 18) & 1);
	}
}
// ?IsWaterCell@Pathfinder@@QAE_NHH@Z @0x002E9897 47B: tag&0xf in {1,7}.
bool Pathfinder::IsWaterCell(int a, int b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647Pos(b, (const Coord3D *)a);
	if (rec != 0)
	{
		int tag = rec->m_flags & 0x0F;
		return tag == 1 || tag == 7;
	}
	return false;
}
// ?IsCliffCell@Pathfinder@@QAE_NHH@Z @0x002E98C6 36B: tag&0xf == 2.
bool Pathfinder::IsCliffCell(int a, int b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647Pos(b, (const Coord3D *)a);
	return rec != 0 ? (rec->m_flags & 0x0F) == 2 : false;
}
// ?isBlockedGateObstacleCell@Pathfinder@@QAEHHH@Z @0x002E98EA 47B: tag==4 && bit17.
int Pathfinder::isBlockedGateObstacleCell(int a, int b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647Pos(b, (const Coord3D *)a);
	if (rec != 0)
	{
		int val = rec->m_flags;
		if ((val & 0x0F) == 4)
		{
			unsigned sh = (unsigned)val;
			int r = 0;
			sh >>= 17;
			r = 1;
			if (r & (char)sh)
				return r;
		}
	}
	return 0;
}
// ?IsNonPinchedCliffCell@Pathfinder@@QAEHHH@Z @0x002E9919 47B: tag==2 && !bit16.
int Pathfinder::IsNonPinchedCliffCell(int a, int b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647Pos(b, (const Coord3D *)a);
	if (rec != 0)
	{
		int val = rec->m_flags;
		if ((val & 0x0F) == 2)
		{
			unsigned sh = (unsigned)val;
			int r = 0;
			sh >>= 16;
			r = 1;
			if ((r & (char)sh) == 0)
				return r;
		}
	}
	return 0;
}
// ?IsImpassableCell@Pathfinder@@QAE_NHH@Z @0x002E9948 38B: null->true else tag==5.
bool Pathfinder::IsImpassableCell(int a, int b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647Pos(b, (const Coord3D *)a);
	return rec != 0 ? (rec->m_flags & 0x0F) == 5 : true;
}
// ?IsPointOnWall@Pathfinder@@QAE_NH_N@Z @0x002E940F 51B: mid>0x10 and
// (b==0 or low==0). Forwards (a 1) to rowed 0x001E3647 with ecx passthrough.
// Evidence: ret 8 two args; test eax null; (flags>>4)&0x3F>0x10 via cl;
// byte test of second arg; test al 0xf. Callers at 0x002CBF72 0x00345748.
bool Pathfinder::IsPointOnWall(int a, bool b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647Pos(1, (const Coord3D *)a);
	if (rec == 0)
		return false;
	unsigned int flags = rec->m_flags;
	signed char mid = (signed char)((flags >> 4) & 0x3F);
	if ((int)mid > 0x10 && (b == 0 || (flags & 0x0F) == 0))
		return true;
	return false;
}

// Rva002E9ACC::Rva002E9ACC, retail 0x002E9ACC (101 bytes; ret 0x14): an
// unnamed pathfinding functor (built by Pathfinder::CanApproachToTarget
// 0x002FA35D) holding (a1, object, locomotor source), the object's
// Rva002E8BCF locomotor-set view at +0x0C (template +0x634/+0x56C and
// Object::rva0028AFBB, as Rva002EAB6F builds it) and five flag bytes.
struct Rva002E8BCFSrc;
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
struct Rva002E9ACCTemplate
{
	char _00[0x56C];
	int m_56C;
	char _570[0x634 - 0x570];
	unsigned char m_634;
};
class Object
{
public:
	bool rva0028AFBB() const;
	char _00[4];
	Rva002E9ACCTemplate *m_04;
};
static unsigned char Rva002E9ACCFlag(const Object *obj)
{
	return obj->m_04->m_634;
}
static int Rva002E9ACCCount(const Object *obj)
{
	return obj->m_04->m_56C;
}
class Rva002E9ACC
{
public:
	Rva002E9ACC(void *a1, Object *obj, Rva002E8BCFSrc const *src,
		unsigned char a4, unsigned char a5);
	void *m_00;
	Object *m_04;
	Rva002E8BCFSrc const *m_08;
	Rva002E8BCF m_0C;
	unsigned char m_1C;
	unsigned char m_1D;
	unsigned char m_1E;
	unsigned char m_1F;
	unsigned char m_20;
};
Rva002E9ACC::Rva002E9ACC(void *a1, Object *obj,
	Rva002E8BCFSrc const *src, unsigned char a4, unsigned char a5)
	: m_00(a1), m_04(obj), m_08(src),
	m_0C(src, Rva002E9ACCFlag(obj) == 0, Rva002E9ACCCount(obj) - 1, obj->rva0028AFBB())
{
	m_1D = a4;
	m_20 = a5;
	m_1C = 0;
	m_1E = 1;
	m_1F = 0;
}
