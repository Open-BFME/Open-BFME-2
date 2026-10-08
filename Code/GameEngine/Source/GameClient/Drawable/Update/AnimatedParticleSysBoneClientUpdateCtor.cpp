// cl: /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Identity: ModuleFactory registers this module as "W3DTornadoDraw" (addModule pairs
// the name with its factories); formerly misnamed AnimatedParticleSysBoneClientUpdate.
// stlport
//
// ??0W3DTornadoDraw@@QAE@PAVThing@@PBVModuleData@@@Z at
// retail 0x000D181D (67B). Its base is DrawModule, whose ctor is the row at
// 0x000B19A1 (also called by W3DRopeDraw's ctor 0x000CA752), modeled opaque here
// (12 bytes: vptr plus pad). The trailing bone-index list at +0x0C default-constructs through
// the list_base<int> at 0x004EC36C (matched row).
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class Thing;
class ModuleData;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

// Opaque 12-byte ClientUpdate-derived intermediate; ctor resolves to the
// opaque pin at 0x000B19A1. Single vptr plus pad to the list at +0x0C.
class DrawModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DrawModule();

protected:
	unsigned char m_pad04[4];
	BFMERopeDrawable *m_ropeDrawable;
};

class RadiusDecal
{
public:
	~RadiusDecal();
	void setPosition(const Coord3D &pos);
	void update();
};

class W3DTornadoDraw : public DrawModule
{
public:
	W3DTornadoDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DTornadoDraw();

private:
	void rva000D1743();
	void rva000D17BA(int dummy);

public:
	void rva000D17EF(int a, int b, int c);

private:
	_STL::list<int> m_boneIndices;
};

W3DTornadoDraw::W3DTornadoDraw(Thing *thing, const ModuleData *moduleData)
	: DrawModule(thing, moduleData)
{
}

// W3DTornadoDraw::~W3DTornadoDraw: defined in W3DTornadoDrawDtor.cpp (its row's unit).

void W3DTornadoDraw::rva000D1743()
{
	for (_STL::list<int>::iterator it = m_boneIndices.begin(); it != m_boneIndices.end(); ++it) {
		RadiusDecal *decal = reinterpret_cast<RadiusDecal *>(*it);
		if (decal)
			delete decal;
	}
	m_boneIndices.clear();
}

void W3DTornadoDraw::rva000D17EF(int a, int b, int c)
{
	for (_STL::list<int>::iterator it = m_boneIndices.begin(); it != m_boneIndices.end(); ++it) {
		RadiusDecal *decal = reinterpret_cast<RadiusDecal *>(*it);
		decal->setPosition(*m_ropeDrawable->getPosition());
	}
}

void W3DTornadoDraw::rva000D17BA(int dummy)
{
	for (_STL::list<int>::iterator it = m_boneIndices.begin(); it != m_boneIndices.end(); ++it) {
		RadiusDecal *decal = reinterpret_cast<RadiusDecal *>(*it);
		decal->setPosition(*m_ropeDrawable->getPosition());
		decal->update();
	}
}
