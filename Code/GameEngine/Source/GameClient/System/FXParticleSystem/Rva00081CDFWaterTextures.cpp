// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /O1 /arch:SSE /G7
// stlport
//
// ?rva00081CDF@Rva00081CDF@@QAEXXZ @ 0x00081CDF (343B), Ghidra boundary.
// Water texture init plus asset collection: loads one global-driven texture
// into +0x44 then WaterSurfaceBubbles.tga into +0x48 and Noise0000.tga into
// +0x4C via rowed BFME2LoadParticleTexture 0x00132D89 plus rowed RefCountPtr
// op= 0x000424D0, collects the global AsciiString plus the two literals plus
// two indexed AsciiStrings via rowed 0x0006C950 and rowed 0x0006C995, loops
// twice via pinned 0x0007EDBC and rowed 0x0030812E, then rowed
// bfmeMergeReceiverKeys 0x0061F010. Evidence: callers 0x0008302B, strings
// WaterSurfaceBubbles.tga Noise0000.tga plus empty-string fallback, global
// g_00DFF488 with +0x04 override chain via pinned getFinalOverride 0x001E35DF
// and AsciiString at +0x3C via shared str(), prev/next neighbours and the
// Rva00081E36/Rva0007EEBE precedents for AssetList and texture slots.
// Row 0x0006C995 types as Target* but retail passes string literals here;
// declared as rowed and noted.
#include "ascii_string.h"

struct Rva001408C0Target;

namespace _STL
{
template <class T> struct _Identity {};
template <class T> struct less {};
template <class T> class allocator {};

template <class Key, class Value, class Identity, class Compare, class Allocator>
class _Rb_tree
{
public:
	~_Rb_tree();
private:
	void *m_storage[3];
};

template <class T, class Compare, class Allocator>
class set
{
	typedef _Rb_tree<T, T, _Identity<T>, Compare, Allocator> Tree;
	Tree m_tree;
public:
	set();
	~set() {}
};
}

typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key,
	_STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

struct AssetList00208F90
{
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
	AssetList00208F90() : m_treeLayoutPad(0), m_changed(true) {}
	AssetList00208F90 &operator<<(const AsciiString &name);
};

class Rva0006C995 : public AssetList00208F90
{
public:
	Rva0006C995 *rva0006C995(Rva001408C0Target *p);
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vtable;
	const Overridable *m_next04;
};

struct Rva00200BD9Holder
{
	int m_00;
	Overridable *m_04;
	char m_pad08[0x3C - 0x08];
	AsciiString m_str3C;
};
extern Rva00200BD9Holder *g_rva00200BD9Holder;

class TextureClass
{
public:
	void Release_Ref();
};

template <class T>
class RefCountPtr
{
public:
	const RefCountPtr &operator=(const RefCountPtr &other);
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
	T *m_ptr;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

BFME2ParticleTextureHandle __cdecl BFME2LoadParticleTexture(const char *filename, int a, int b);

class Rva0007EDBC
{
public:
	void rva0007EDBC(int index);
};

class Rva0030812E
{
public:
	void *rva0030812E(int index);
};

void bfmeMergeReceiverKeys(int value);

class Rva00081CDF
{
	char m_pad00[0x40];
	Rva0030812E *m_holder40;
	BFME2ParticleTextureHandle m_tex44;
	BFME2ParticleTextureHandle m_tex48;
	BFME2ParticleTextureHandle m_tex4C;
public:
	void rva00081CDF();
};

void Rva00081CDF::rva00081CDF()
{
	Rva0006C995 assets;
	Rva00200BD9Holder *p = g_rva00200BD9Holder;
	if (!p)
		p = 0;
	else if (p->m_04)
		p = (Rva00200BD9Holder *)p->m_04->getFinalOverride();
	// NOTE: retail loads the texture name from the final override's AsciiString
	// at +0x3C via shared str() (m_text ? m_text+8 : ""); the holder above
	// carries that string for byte identity. Row 0x0006C995 types as Target*
	// but this body passes the two .tga literals; kept rowed as served.
	m_tex44 = BFME2LoadParticleTexture(p->m_str3C.str(), 0, 0);

	p = g_rva00200BD9Holder;
	if (!p)
		p = 0;
	else if (p->m_04)
		p = (Rva00200BD9Holder *)p->m_04->getFinalOverride();
	assets << p->m_str3C;

	m_tex48 = BFME2LoadParticleTexture("WaterSurfaceBubbles.tga", 0, 0);
	assets.rva0006C995((Rva001408C0Target *)"WaterSurfaceBubbles.tga");

	m_tex4C = BFME2LoadParticleTexture("Noise0000.tga", 0, 0);
	assets.rva0006C995((Rva001408C0Target *)"Noise0000.tga");

	for (int i = 0; i < 2; ++i) {
		((Rva0007EDBC *)(char *)this)->rva0007EDBC(i);
		assets << *(const AsciiString *)m_holder40->rva0030812E(i);
	}

	bfmeMergeReceiverKeys((int)&assets);
}
