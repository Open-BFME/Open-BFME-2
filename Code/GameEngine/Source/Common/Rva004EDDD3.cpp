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
private:
	char m_pad04[0x14 - 0x04];
	Rva004EDDD3Node *m_begin;
	Rva004EDDD3Node *m_end;
	char m_pad1C[0x38 - 0x1C];
	Coord3D m_38;
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
