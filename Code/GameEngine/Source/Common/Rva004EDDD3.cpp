// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHs /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva004EDDD3@Rva00506909Item@@QAEXXZ at 0x004EDDD3 (276B).
// Item average: if v4()==0 return; else gather Team positions via TheTeamFactory+findInstance into vector<Coord3D> then average into +0x38.
// Evidence: virtual [eax+0x10] count guard; +0x14/+0x18 stride 0x14 nodes via TheTeamFactory 0x00A028BC and findInstance 0x0039F761; Team::rva0039E5B9 fills Coord3D then push_back 0x002CE7DC; sum into +0x38/+0x3C/+0x40 then 1.0/g_Va00BBB8D8 divide with unsigned fild+fadd g_00BC26EC then free 0x00030830; caller 0x004EDF89 in Item 0x004EDF03; prev/next Rva004EDCE9Dtor.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Team;
class TeamFactory;
extern TeamFactory *TheTeamFactory;

class Rva0039F761Owner
{
public:
	Team *findInstance(void *p);
};

class Team
{
public:
	void rva0039E5B9(Coord3D *pos);
};

struct BfmePod20
{
	int a[5];
};
inline bool operator==(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] < y.a[0]; }
struct PodVec
{
	BfmePod20 *begin;
	BfmePod20 *end;
};
namespace _STL {
template <class _InputIter, class _Tp>
_InputIter find(_InputIter, _InputIter, const _Tp &);
}
class Rva004ED3A2
{
public:
	void *rva004ED3A2(void *pos);
};
class Rva004ECECD
{
public:
	void rva004ED748(int a, int b);
};

extern "C" void __cdecl free(void *p);
extern float g_Va00BBB8D8;
extern float g_00BC26EC;

struct Rva004EDDD3Node
{
	void *m_model;
	char m_pad[0x10];
};

class Rva00506909Item
{
public:
	virtual ~Rva00506909Item();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual unsigned v4();
	void rva004EDDD3();
	void rva004EDD4D(struct Rva005059A1Unit *arg);
private:
	char m_pad04[0x10 - 0x04];
	unsigned char m_10;
	char m_pad11[0x14 - 0x11];
	Rva004EDDD3Node *m_begin;
	Rva004EDDD3Node *m_end;
	char m_pad1C[0x28 - 0x1C];
	unsigned char m_28;
	char m_pad29[0x34 - 0x29];
	unsigned char m_34;
	char m_pad35[0x38 - 0x35];
	Coord3D m_38;
};
struct Rva005059A1Unit
{
	char m_pad[0x34];
	int m_34;
};

void Rva00506909Item::rva004EDDD3()
{
	if (v4() <= 0)
		return;
	_STL::vector<Coord3D> tmp;
	Rva004EDDD3Node *end = m_end;
	for (Rva004EDDD3Node *it = m_begin; it != end; ++it)
	{
		Team *team = ((Rva0039F761Owner *)TheTeamFactory)->findInstance(it->m_model);
		Coord3D pos;
		pos.x = 0.0f;
		pos.y = 0.0f;
		pos.z = 0.0f;
		team->rva0039E5B9(&pos);
		tmp.push_back(pos);
	}
	m_38.x = 0.0f;
	m_38.y = 0.0f;
	m_38.z = 0.0f;
	for (Coord3D *p = tmp.begin(); p != tmp.end(); ++p)
	{
		float *dx = &m_38.x;
		*dx += p->x;
		m_38.y += p->y;
		m_38.z += p->z;
	}
	unsigned n = (unsigned)tmp.size();
	float inv = g_Va00BBB8D8 / (float)n;
	m_38.x *= inv;
	m_38.y *= inv;
	m_38.z *= inv;
}
// ?rva004EDD4D@Rva00506909Item@@QAEXPAURva005059A1Unit@@@Z @ 0x004EDD4D 93B.
// Leaf: if m_28 return; find Pod20 by Unit+0x34 in vector at +0x14,
// erase via rowed 0x004ED3A2, if not empty return; if m_34==0 and m_10!=0
// return else rowed rva004ED748(0,0). Same class as rva004EDDD3.
// Evidence: pin QAEXPAURva005059A1Unit; caller 0x00505AE6; callees rowed
// find 0x002198AD erase 0x004ED3A2 plus pin rva004ED748 0x004ED748.
void Rva00506909Item::rva004EDD4D(Rva005059A1Unit *arg)
{
	if (m_28 != 0)
		return;
	int key = arg->m_34;
	BfmePod20 *end = (BfmePod20 *)m_end;
	PodVec *vec = (PodVec *)&m_begin;
	BfmePod20 *found = _STL::find(vec->begin, end, *(const BfmePod20 *)&key);
	if (found != end)
		((Rva004ED3A2 *)vec)->rva004ED3A2((void *)found);
	if (vec->begin != vec->end)
		return;
	if (m_34 == 0)
	{
		if (m_10 != 0)
			return;
	}
	((Rva004ECECD *)this)->rva004ED748(0, 0);
}
