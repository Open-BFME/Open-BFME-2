// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// AIFlankAttackTacticImp::DoXfer @0x005AA4C1 156B (WorldBuilder: the route's
// m_positions count then each position, asserting the count at
// AIFlankAttackTactic.cpp:132; called from AIFlankAttackTactic's xfer). Identity: fill vector from virtual enumeration then zero-fill via push_back.
// Evidence: vector<Coord3D> at +4 div 12; virtual slots 0x78 0x8 0x60 0x4; rowed push_back 0x002CE7DC; caller 0x005AA622 same page.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

struct Coord3D
{
	float x;
	float y;
	float z;
	Coord3D() {}
	Coord3D(const Coord3D &that) throw();
};

// Declaration-only _Construct: retail's push_back calls the pinned out-of-line
// helper (0x002CA82C) instead of inlining the element copy (row 35 family-LK3).
namespace _STL {
template <> void _Construct<Coord3D, Coord3D>(Coord3D *, const Coord3D &);
}

class Xfer
{
public:
	virtual void v00();
	virtual bool v01();
	virtual bool v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24(const Coord3D *p);
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30(void *p);
};

class AIFlankAttackTacticImp
{
public:
	virtual ~AIFlankAttackTacticImp();
	void DoXfer(Xfer *p);
private:
	_STL::vector<Coord3D> m_04;
};

void AIFlankAttackTacticImp::DoXfer(Xfer *p)
{
	p->v30(this);
	AIFlankAttackTacticImp *self = this;
	_STL::vector<Coord3D> *vec = &m_04;
	unsigned int count = (unsigned int)(vec->end() - vec->begin());
	p->v30(&count);
	if (p->v02()) {
		_STL::vector<Coord3D>::iterator end = self->m_04.end();
		_STL::vector<Coord3D>::iterator it = vec->begin();
		for (; it != end; ++it)
			p->v24(&(*it));
		return;
	}
	if (!p->v01())
		return;
	for (unsigned int i = 0; i < count; ++i) {
		Coord3D zero;
		zero.x = 0.0f;
		zero.y = 0.0f;
		zero.z = 0.0f;
		p->v24(&zero);
		vec->push_back(zero);
	}
}
