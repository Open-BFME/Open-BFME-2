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
	int rva002E9871(const Coord3D *pos);
	bool rva002E9897(int a, int b);
	bool rva002E98C6(int a, int b);
	int rva002E98EA(int a, int b);
	int rva002E9919(int a, int b);
	bool rva002E940F(int a, bool b);
	bool rva002E9948(int a, int b);
	bool rva002E996E(int a, bool b, bool c, int d);
	void rva002E99BD(int a1, void *a2, void *a3, void *a4, int a5);
private:
	char m_pad000[0x10];
	int m_unk0010; // +0x10 null-guard read by rva002E9871
};
struct Rva001E3647Result
{
	char m_pad[0x0C];
	unsigned int m_flags;
};
// ?rva002E9871@Pathfinder@@QAEHPBUCoord3D@@@Z @0x002E9871 38B: +0x10-gated
// cell-field query: guard or null -> 1, else (flags>>4)&0x3F. Converts the
// existing same-name pin into a row.
int Pathfinder::rva002E9871(const Coord3D *pos)
{
	if (m_unk0010 != 0)
	{
		Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647Pos(1, pos);
		if (rec != 0)
			return (rec->m_flags >> 4) & 0x3F;
	}
	return 1;
}
// ?rva002E996E@Pathfinder@@QAE_NH_N_NH@Z @0x002E996E 79B: 4-arg combined
// query: null->true; flag=(tag==2); unless b, flag|=tag in {1,7}; unless c,
// flag|=tag==5.
// ?Pathfinder::rva002E996E present-unmatched
bool Pathfinder::rva002E996E(int a, bool b, bool c, int d)
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
// ?rva002E99BD@Pathfinder@@QAEXHPAXPAXPAXH@Z @0x002E99BD 60B: ebp-frame
// split-out: *a2=nonnull, *a4=tag, *a3=bit18.
void Pathfinder::rva002E99BD(int a1, void *a2, void *a3, void *a4, int a5)
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
// ?rva002E9897@Pathfinder@@QAE_NHH@Z @0x002E9897 47B: tag&0xf in {1,7}.
bool Pathfinder::rva002E9897(int a, int b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647Pos(b, (const Coord3D *)a);
	if (rec != 0)
	{
		int tag = rec->m_flags & 0x0F;
		return tag == 1 || tag == 7;
	}
	return false;
}
// ?rva002E98C6@Pathfinder@@QAE_NHH@Z @0x002E98C6 36B: tag&0xf == 2.
bool Pathfinder::rva002E98C6(int a, int b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647Pos(b, (const Coord3D *)a);
	return rec != 0 ? (rec->m_flags & 0x0F) == 2 : false;
}
// ?rva002E98EA@Pathfinder@@QAEHHH@Z @0x002E98EA 47B: tag==4 && bit17.
int Pathfinder::rva002E98EA(int a, int b)
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
// ?rva002E9919@Pathfinder@@QAEHHH@Z @0x002E9919 47B: tag==2 && !bit16.
int Pathfinder::rva002E9919(int a, int b)
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
// ?rva002E9948@Pathfinder@@QAE_NHH@Z @0x002E9948 38B: null->true else tag==5.
bool Pathfinder::rva002E9948(int a, int b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647Pos(b, (const Coord3D *)a);
	return rec != 0 ? (rec->m_flags & 0x0F) == 5 : true;
}
// ?rva002E940F@Pathfinder@@QAE_NH_N@Z @0x002E940F 51B: mid>0x10 and
// (b==0 or low==0). Forwards (a 1) to rowed 0x001E3647 with ecx passthrough.
// Evidence: ret 8 two args; test eax null; (flags>>4)&0x3F>0x10 via cl;
// byte test of second arg; test al 0xf. Callers at 0x002CBF72 0x00345748.
bool Pathfinder::rva002E940F(int a, bool b)
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
