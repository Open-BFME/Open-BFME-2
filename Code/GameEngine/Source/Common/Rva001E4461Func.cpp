// cl: /DNDEBUG /MD
// ?rva001E4461@Pathfinder@@QAEPAXHH@Z @0x001E4461 44B evidence: forwards this plus two ints to pinned Pathfinder lookup ?rva001E3647@Pathfinder@@QAEPAXHH@Z @0x001E3647 then tag check low nibble of +0xC equals 4 plus null checks plus return of +0x28 else 0; callers unclaimed; abuts prev 0x001E4445 and next 0x001E448D
struct Coord3D;
class Pathfinder
{
public:
	void *rva001E3647Pos(int a1, const Coord3D *pos);
	void *rva001E4461(int a1, int a2);
};

struct Rva001E4461Rec
{
	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
};

void *Pathfinder::rva001E4461(int a1, int a2)
{
	Rva001E4461Rec *rec = (Rva001E4461Rec *)rva001E3647Pos(a1, (const Coord3D *)a2);
	if (!rec)
		return 0;
	if (((rec->m_0C & 0xF) != 4))
		return 0;
	if (rec->m_00)
		return *(void **)((char *)rec->m_00 + 0x28);
	return 0;
}
