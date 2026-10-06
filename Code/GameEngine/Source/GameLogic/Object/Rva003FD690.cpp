// cl: /DNDEBUG /MD /GX
// ?rva003FD690@Rva003FD690@@QAEXPBUCoord@@@Z @0x003FD690 45B
// Copies 12B Coord from arg to +0x20 via 3x movsd, then if +0x04 helper
// calls vtable slot 0x1C with same arg then slot 0x0C with no args.
// Callers at 0x00212196 and 0x00212222. Layout: pointer at +0x04,
// Coord at +0x20.
struct Coord
{
	float x;
	float y;
	float z;
};

class Helper
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7(const Coord *p);
};

class Rva003FD690
{
public:
	void rva003FD690(const Coord *p);
private:
	char m_00[4];
	Helper *m_04;
	char m_08[24];
	Coord m_20;
};

void Rva003FD690::rva003FD690(const Coord *p)
{
	m_20 = *p;
	if (m_04) {
		m_04->v7(p);
		m_04->v3();
	}
}
