// ?Rva003F71D4Distance@@YGMPBURva003F71D4Point@@0@Z
// partial score=0.93 date=2026-10-06
// cl: /DNDEBUG /MD /O1 /arch:SSE /G7 /Oy-
// ?Rva003F71D4Distance@@YGMPBURva003F71D4Point@@0@Z @0x003F71D4 53B.
// 2D distance between the +0x10/+0x14 floats of two objects via Coord2D::length.
// Evidence: REF table slots 0x007E4340/44 plus retail ebp-frame movss subss
// plus stack Coord2D plus rowed length 0x00003755 plus ret 8 plus no caller.
struct Rva003F71D4Point
{
	char m_pad[0x10];
	float m_x;
	float m_y;
};

struct Coord2D
{
	float x;
	float y;
	float length() const;
};

float __stdcall Rva003F71D4Distance(const Rva003F71D4Point *a, const Rva003F71D4Point *b)
{
	register float ax = a->m_x;
	register float ay = a->m_y;
	Coord2D d = {ax - b->m_x, ay - b->m_y};
	return d.length();
}
