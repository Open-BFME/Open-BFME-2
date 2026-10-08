// ?rva0073BEA0@Rva0073BEA0@@UAEXHH@Z
// partial score=0.85 date=2026-10-03
// cl: /O2 /MD /Oy /EHs
//
// Address-derived recovery of the 0x0073BEA0 virtual (106B), one of the two
// sibling cell-to-screen notifier functors whose constructors sit at
// 0x0073B4E0/0x0073B500 and whose one-slot vtables are 0x00CF13A0/0x00CF13A4.
// Target evidence: field +4 points at a grid whose float originX/originY sit
// at +4/+8 and whose float scale sits at +0x1C; field +0xC is an object whose
// vtable slot 0 takes the two-float point built here; the real literal 0.5 is
// the qword constant at 0x007C26F8 and the int casts go through the pinned
// CRT helper 0x00629228 (__ftol2). The class/member names are address-derived:
// no string names this functor family.
//
// PARTIAL: size is exact (106B) and every instruction shape matches, but
// retail keeps the Y int in the [esp+8] slot and converts both coordinates at
// the end (point.x then point.y), where this body converts Y to point.y as
// soon as it is computed. 16 disassembly lines differ, all in that scheduling
// and the resulting frame offsets.

class BfmeGrid73BE
{
public:
	char m_pad00[4];
	float m_originX;		// +0x04
	float m_originY;		// +0x08
	char m_pad0C[0x10];
	float m_scale;			// +0x1C
};

class BfmeOut73BE
{
public:
	virtual void notify(const void *point);
};

struct BfmePoint73BE
{
	float x;
	float y;
	float z;
};

class Rva0073BEA0
{
public:
	virtual void rva0073BEA0(int a, int b);

private:
	BfmeGrid73BE *m_grid;	// +0x04
	int m_8;				// +0x08
	BfmeOut73BE *m_out;		// +0x0C
};

void Rva0073BEA0::rva0073BEA0(int a, int b)
{
	BfmePoint73BE point;
	point.y = (int)(b * m_grid->m_scale + m_grid->m_originY + m_grid->m_scale * 0.5);
	point.x = (int)(a * m_grid->m_scale + m_grid->m_originX + m_grid->m_scale * 0.5);
	m_out->notify(&point);
}
