// cl: /O1 /Ob0 /EHsc /MD
// stlport
// ?rva00506A52@Rva00506A52@@QAEXXZ @ 0x00506A52 168B (placeholder, real signature TBD)
// Chain from 0x005AD6C3: iterates hash_map buckets via rowed bucket_count,
// fetches Object* per index via rowed rva0025BFF8, filters via rowed
// rva00506A0C plus +0x520==12, news 0x10 Rva005AD6C3 from Object and
// push_backs into vector at this+4. Evidence: calls at 0x00506A6B/75/8B/99/
// AC4/DB, new 0x10 at 0x00506AAE, vector at [edi+4], Player at [edi].
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
#include <hash_map>

class Player;
class Object;
class ModuleData;

struct Rva00506A0COther
{
	char m_pad[0x74];
	int m_74;
};

struct Rva005DCC4BSource
{
	char m_bytes00[0x74];
	int m_field74;
};

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *p);
};

class Rva0025BFF8
{
public:
	Object *rva0025BFF8(int index);
};

class Rva00506A0C
{
public:
	bool rva00506A0C(const Rva00506A0COther *other);
};

class Rva005DCC4B
{
public:
	Rva005DCC4B(const Rva005DCC4BSource *source);
	virtual ~Rva005DCC4B();

	int m_field04;
};

class Rva005AD6C3 : public Rva005DCC4B
{
public:
	Rva005AD6C3(const Rva005DCC4BSource *source);
	virtual ~Rva005AD6C3();

	int m_field08;
	int m_field0C;
};

class Object
{
public:
	void *m_04;
	char m_pad08[0x74 - 0x08];
	int m_74;
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva00506A52
{
public:
	void rva00506A52();
private:
	Player *m_00;
	_STL::vector<const ModuleData *> m_04;
};

void Rva00506A52::rva00506A52()
{
	void *ret = g_00DFEEF8->rva002A8F24(m_00);
	Rva0025BFF8 *maps = *(Rva0025BFF8 **)((char *)ret + 4);
	unsigned int count = (( _STL::hash_map<int, int> *)maps)->bucket_count();
	for (unsigned int i = 0; i < count; ++i) {
		Object *obj = maps->rva0025BFF8((int)i);
		if (obj == 0)
			continue;
		if (((Rva00506A0C *)this)->rva00506A0C((const Rva00506A0COther *)obj))
			continue;
		void *inner = *(void **)((char *)obj + 4);
		if (*(int *)((char *)inner + 0x520) != 12)
			continue;
		Rva005AD6C3 *nw = new Rva005AD6C3((const Rva005DCC4BSource *)obj);
		const ModuleData *tmp = (const ModuleData *)nw;
		m_04.push_back(tmp);
	}
}
