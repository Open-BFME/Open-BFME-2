// cl: /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?? W3DShroud::W3DShroud retail 0x00073320..0x000733D8 (184B). Identity: WB
// 0x7FC3xx names the class (PartialShroudedRenderingMethod ref at +0x40, dirty
// set at +0x4c); ZH W3DShroud::W3DShroud (W3DShroud.cpp:76) is the member list
// donor. Retail target evidence: 0x10-byte counted method object stored at
// +0x40 (vtable 0x00BC6568, count 1, owner back-pointer), border level byte
// from GlobalData+0xBEA, dirty set via rowed 0x000D3A71 (Taint's allocator).
#include <set>

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
// converged global at 0x00DFE750; declared as its real type and viewed through
// BfmeTaintManager at the use site.
class Rva000729CC
{
public:
	void rva00073CC0(int x, int y, UnsignedByte level, bool textureOnly);
};
class BfmeTaintManager
{
public:
	UnsignedByte rva006C0840(int x, int y);
};
class TaintManager;
extern TaintManager *TheTaintManager;
class BaseHeightMapRenderObjClass
{
public:
	char m_pad00[0x387c];
	Rva000729CC *m_387c;
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

class __declspec(novtable) Rva00073320Base
{
public:
	Rva00073320Base() : m_count(1), m_ref(0) {}
	virtual void destroy();
	virtual ~Rva00073320Base();
	int m_count;
	void *m_ref;
};

class Rva00073320Method : public Rva00073320Base
{
public:
	Rva00073320Method(W3DShroud *owner) : m_owner(owner) {}
	virtual void destroy();
	virtual ~Rva00073320Method();
	W3DShroud *m_owner;
};

class Rva00073320Ptr
{
public:
	Rva00073320Ptr(Rva00073320Method *p) : m_ptr(p) {}
	~Rva00073320Ptr();
	Rva00073320Method *m_ptr;
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
	Rva00073320Ptr m_method;
	int m_pad44;
	unsigned char m_trackDirtyCells;
	_STL::set<int, _STL::less<int>, Rva0054E8DCAllocator<int> > m_dirty;
};

// ??0W3DShroud@@QAE@XZ
W3DShroud::W3DShroud()
 : m_numCellsX(0), m_numCellsY(0), m_numMaxVisibleCellsX(0), m_numMaxVisibleCellsY(0),
 m_cellWidth(10.0f), m_cellHeight(10.0f), m_shroudData(0),
 m_dstTextureWidth(0), m_dstTextureHeight(0), m_shroudFilter(4),
 m_drawOriginX(0.0f), m_drawOriginY(0.0f), m_drawFogOfWar(0), m_clearDstTexture(1),
 m_borderShroudLevel(TheWritableGlobalData->m_shroudAlpha),
 m_finalFogData(0), m_currentFogData(0),
 m_method(new Rva00073320Method(this)), m_pad44(0), m_trackDirtyCells(1)
{
}

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
		if (taintBuffer && *reinterpret_cast<BfmeTaintManager **>(&TheTaintManager))
			taintBuffer->rva00073CC0(x, y,
				(*reinterpret_cast<BfmeTaintManager **>(&TheTaintManager))->rva006C0840(x, y), true);
	}
}
