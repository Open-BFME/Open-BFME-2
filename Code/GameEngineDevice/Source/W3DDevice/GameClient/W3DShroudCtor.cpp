// cl: /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?? W3DShroud::W3DShroud retail 0x00073320..0x000733D8 (184B). Identity: WB
// 0x7FC3xx names the class (PartialShroudedRenderingMethod ref at +0x40, dirty
// set at +0x4c); ZH W3DShroud::W3DShroud (W3DShroud.cpp:76) is the member list
// donor. Retail target evidence: 0x10-byte counted method object stored at
// +0x40 (vtable 0x00BC6568, count 1, owner back-pointer), border level byte
// from GlobalData+0xBEA, dirty set via rowed 0x000D3A71 (Taint's allocator).
#include <set>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
// Keep the int-node deallocate inline, as W3DTaint.cpp does, so this unit emits
// no copy of it and its set<int> erase/destructor copies match that unit's
// (it follows this one in link order). dllimport + forceinline: no __imp_ remains.
namespace _STL { template <> __declspec(dllimport) __forceinline void allocator<_Rb_tree_node<int> >::deallocate(_Rb_tree_node<int> *p,size_t n)const { _STLP_ASSERT((p==0)==(n==0)) if(p) ::free((void*)p); } }
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

typedef unsigned char UnsignedByte;

class GlobalData
{
	unsigned char m_pad00[0xbea];
public:
	UnsignedByte m_shroudAlpha;
};
extern GlobalData *TheWritableGlobalData;

// Taint hooks reached from setShroudLevel (retail 0x00073CC0 / 0x006C0840 take
// byte arguments, see W3DDisplaySmallSlots.cpp). TheTaintManager is the
// data-ledger global at 0x00DFE750, declared with its owned BfmeTaintManager type.
class Rva000729CC
{
public:
	void rva000729CC(bool on);
	void rva00073CC0(int x, int y, unsigned char level, bool textureOnly);
	char m_pad00[0x35];
private:
	bool m_flag35; // +0x35
	bool m_flag36; // +0x36
};
class BfmeTaintManager
{
public:
	UnsignedByte rva006C0840(int x, int y);
};
extern BfmeTaintManager *TheTaintManager;
class WorldHeightMap;
class BaseHeightMapRenderObjClass
{
public:
	WorldHeightMap *getMap() const {return m_map;}
	char m_pad00[0x37C0];
	WorldHeightMap *m_map; // +0x37C0
	char m_pad37C4[0xB8];
	Rva000729CC *m_387c; // +0x387C
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
unsigned short __cdecl Rva00072D5DShroudPixel(unsigned char level);

template<class T> class Rva0054E8DCAllocator : public _STL::allocator<T>
{
public:
 template<class U> struct rebind { typedef Rva0054E8DCAllocator<U> other; };
 Rva0054E8DCAllocator() throw() {}
 Rva0054E8DCAllocator(const Rva0054E8DCAllocator &) throw() {}
 template<class U> Rva0054E8DCAllocator(const Rva0054E8DCAllocator<U> &) throw() {}
};
namespace _STL {
template<class T, class U> struct _Alloc_traits<T, Rva0054E8DCAllocator<U> > {
 typedef Rva0054E8DCAllocator<U> _Orig;
 typedef Rva0054E8DCAllocator<T> allocator_type;
 static allocator_type create_allocator(const _Orig &a) { return allocator_type(a); }
};
}

class W3DShroud;

class TextureClass { public: void Release_Ref(); };
class ShroudTextureHandle
{
public:
	ShroudTextureHandle() : m_p(0) {}
	~ShroudTextureHandle() { if (m_p) m_p->Release_Ref(); }
	TextureClass *m_p;
};

class __declspec(novtable) BfmeDynamicVBRefCount
{
public:
	__declspec(dllimport) __forceinline BfmeDynamicVBRefCount() : m_count(1) {}
	virtual void DeleteThis();
	virtual ~BfmeDynamicVBRefCount();
	int m_count;
};

class __declspec(novtable) Rva0072AED : public BfmeDynamicVBRefCount
{
public:
	Rva0072AED() : m_ref(0) {}
	virtual ~Rva0072AED();
	void *m_ref;
};

class Rva00072FE1 : public Rva0072AED
{
public:
	__declspec(dllimport) __forceinline Rva00072FE1(W3DShroud *owner) : m_owner(owner) {}
	virtual ~Rva00072FE1();
	W3DShroud *m_owner;
};

class Rva00087A93
{
public:
	Rva00087A93(Rva00072FE1 *p) : m_ptr(p) {}
	~Rva00087A93();
	Rva00072FE1 *m_ptr;
};

class W3DShroud
{
public:
	W3DShroud();
	void setShroudLevel(int x, int y, UnsignedByte level, bool textureOnly);
private:
	int m_numCellsX, m_numCellsY;
	int m_numMaxVisibleCellsX, m_numMaxVisibleCellsY;
	float m_cellWidth, m_cellHeight;
	unsigned short *m_shroudData;
	ShroudTextureHandle m_dstTexture;
	int m_dstTextureWidth, m_dstTextureHeight;
	int m_shroudFilter;
	float m_drawOriginX, m_drawOriginY;
	unsigned char m_drawFogOfWar, m_clearDstTexture, m_borderShroudLevel, m_pad37;
	unsigned char *m_finalFogData, *m_currentFogData;
	Rva00087A93 m_method;
	int m_pad44;
	unsigned char m_trackDirtyCells;
	_STL::set<int, _STL::less<int>, Rva0054E8DCAllocator<int> > m_dirty;
};


// ?setShroudLevel@W3DShroud@@QAEXHHE_N@Z, retail 0x000731F4 (184B, RET 16).
// Identity: W3DDisplay slot 0x00044FF2 is ZH's W3DDisplay::setShroudLevel and
// calls it through getShroud(); Open-BFME-1's W3DShroudBfme.cpp setShroudLevel
// is the same body (shroud floor, final fog store, dirty-set insert, 4444
// pixel via 0x00072D5D) and BFME 2 additionally refreshes the taint cell. The
// taint tail reads the +0x387C helper without a render-object null check and
// reaches TheTaintManager through its real global's BfmeTaintManager view.
void W3DShroud::setShroudLevel(int x, int y, UnsignedByte level, bool textureOnly)
{
	if (m_shroudData == 0)
		return;

	if (x < m_numCellsX && y < m_numCellsY)
	{
		if (level < TheWritableGlobalData->m_shroudAlpha)
			level = TheWritableGlobalData->m_shroudAlpha;

		if (!textureOnly)
		{
			int cell = x + y * m_numCellsX;
			m_finalFogData[cell] = level;
			if (m_trackDirtyCells)
				m_dirty.insert(cell);
		}

		m_shroudData[x + y * m_numCellsX] = Rva00072D5DShroudPixel(level);

		Rva000729CC *taintBuffer = TheTerrainRenderObject->m_387c;
		if (taintBuffer && TheTaintManager)
			taintBuffer->rva00073CC0(x, y,
				TheTaintManager->rva006C0840(x, y), true);
	}
}
