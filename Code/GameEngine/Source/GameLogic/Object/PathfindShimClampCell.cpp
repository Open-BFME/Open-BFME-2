// cl: /DNDEBUG /MD /EHsc
// ?Rva002E7917@Pathfinder@@QAEXPAUICoord2D@@_NPBUCoord3D@@@Z @0x002E7917 77B
// Pathfinder clamp wrapper around the free converter at 0x002E7875.
// Calls Rva002E7875WorldToCell then clamps to m_extent at this+0x14.
// cmov form needs /arch:SSE (cl 13.10 emits cmov only under /arch:SSE).

typedef int Int;
typedef float Real;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

ICoord2D* __cdecl Rva002E7875WorldToCell(ICoord2D* out, bool center, const Coord3D* pos);

class Pathfinder
{
public:
	void Rva002E7917(ICoord2D* out, bool center, const Coord3D* pos);
private:
	unsigned char m_pad[0x14];
	IRegion2D m_extent;
};

void Pathfinder::Rva002E7917(ICoord2D* out, bool center, const Coord3D* pos)
{
	ICoord2D tmp;
	Rva002E7875WorldToCell(&tmp, center, pos);
	if (tmp.x < m_extent.lo.x)
		tmp.x = m_extent.lo.x;
	if (tmp.y < m_extent.lo.y)
		tmp.y = m_extent.lo.y;
	if (tmp.x > m_extent.hi.x)
		tmp.x = m_extent.hi.x;
	if (tmp.y > m_extent.hi.y)
		tmp.y = m_extent.hi.y;
	*out = tmp;
}
