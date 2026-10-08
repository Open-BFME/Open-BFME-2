// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /O1
//
// ?onStandingWaterAreaTextureNameChanged@RenderableStandingWaterArea@@QAEXPAXH@Z @ 0x00081E36 (114B), Ghidra boundary.
// Target bytes show a two-argument thiscall body using the second argument as
// an index: clear this+0x14+4*index; call 0x0007EDBC on this-0x3C; fetch the
// indexed AsciiString through the matched lea helper at 0x0030812E; append it
// to an AssetList through 0x0006C950; then merge that list through matched
// bfmeMergeReceiverKeys at 0x0061F010. The matched T1Base constructor in
// T1Base005F3750Ctor.cpp supplies the donor-backed AssetList/set layout and
// lifetime pattern. This body's owner and first parameter identity remain
// unknown; rva names preserve that uncertainty.

struct Rva001408C0Target;
class AsciiString;

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

class AssetList
{
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
public:
	AssetList() : m_treeLayoutPad(0), m_changed(true) {}
	AssetList &operator<<(const AsciiString &name);
};

class BfmeResetTextureRef
{
public:
	void clear();
};

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

class RenderableStandingWaterArea
{
	char m_pad00[4];
	Rva0030812E *m_assets;
public:
	void onStandingWaterAreaTextureNameChanged(void *unused, int index);
};

void RenderableStandingWaterArea::onStandingWaterAreaTextureNameChanged(void *, int index)
{
	((BfmeResetTextureRef *)((char *)this + 0x14 + index * 4))->clear();
	((Rva0007EDBC *)((char *)this - 0x3C))->rva0007EDBC(index);

	AssetList assets;
	assets << *(const AsciiString *)m_assets->rva0030812E(index);
	bfmeMergeReceiverKeys((int)&assets);
}

// Native 0x000820CA..0x00082140, RET8. The same AssetList lifetime and
// merge as the rowed standing-water callback; this receiver is the +0x3C
// view of the RiverArea accepted by the rowed createTexture provider.
// Callback name and first argument identity are unresolved. Reads +4,
// clears the indexed holder at +8, and writes the dirty byte at +0x1C.
class RenderableRiverArea {
public:
 void createTexture(int index);
};
class Rva0030BBA9 {
public:
 void *rva0030BBA9(int index);
};
class Rva000820CA {
 char m_pad00[4];
 Rva0030BBA9 *m_assets;
 char m_pad08[0x1C-8];
 bool m_dirty;
public:
 void rva000820CA(void *unused, int index);
};
void Rva000820CA::rva000820CA(void *, int index) {
 ((BfmeResetTextureRef *)((char *)this + 8 + index * 4))->clear();
 ((RenderableRiverArea *)((char *)this - 0x3C))->createTexture(index);
 AssetList assets;
 assets << *(const AsciiString *)m_assets->rva0030BBA9(index);
 bfmeMergeReceiverKeys((int)&assets);
 m_dirty = true;
}
