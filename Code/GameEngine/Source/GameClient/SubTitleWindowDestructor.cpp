// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// Native260865..260A3C /471B and260A3C..260AD6 /154B.
// WB DA4FD0 names SubTitleWindow destructor; constructor callers47F79/51353
// allocate6C and forward font/floats/count. Those target accesses establish
// nonvirtual layout and the display-manager/registry relationship.
// Constructor loops and pixel arithmetic are reconstructed from retail.
// Pointer-only record-vector base initialization uses its existing29B provider;
// record cleanup keeps the owned Rva00260826 destructor. Original record name
// is unknown. Both measurement locals precede the temporary-text block:
// this gives retail width-14 and height8 while its EH temporaries reuse1C.
// Both full bodies and their EH data verify. No donor identity is asserted.
// stlport
#define _STLP_BFME_COPY_TRIVIAL_EXTERN
#include "unicode_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <algorithm>
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEX:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_insert_overflow(const ModuleData **, const ModuleData *const &, const __true_type &, size_t, bool); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAPBVModuleData@@PBV1@V?$allocator@PBVModuleData@@@_STL@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> const ModuleData **_STLP_alloc_proxy<const ModuleData **, const ModuleData *, allocator<const ModuleData *> >::allocate(size_t); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@PBVModuleData@@@_STL@@QBEPAPBVModuleData@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> const ModuleData **allocator<const ModuleData *>::allocate(size_t, const void *) const; }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PBVModuleData@@@_STL@@QBEXPAPBVModuleData@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void allocator<const ModuleData *>::deallocate(const ModuleData **, size_t) const; }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_clear(); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::end() { return this->_M_finish; } }

class GameFont;
class ModuleData;

struct BfmeStringRecord005DDD40 { UnicodeString text; unsigned word; };

// Keep the registry and record cleanup bound to their existing providers.
namespace _STL {
template <> _Vector_base<BfmeStringRecord005DDD40, allocator<BfmeStringRecord005DDD40> >::~_Vector_base();
template <> void allocator<BfmeStringRecord005DDD40>::deallocate(BfmeStringRecord005DDD40 *, size_t) const;
template <> void vector<const ModuleData *, allocator<const ModuleData *> >::push_back(const ModuleData *const &);
}

class DisplayString
{
public:
	virtual void s00();
	virtual void setText(UnicodeString s);
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void setFont(GameFont *font);
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void getSize(int *w, int *h);
};

class DisplayStringManager
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual DisplayString *newDisplayString();
	virtual void freeDisplayString(DisplayString *s);
};

extern DisplayStringManager *TheDisplayStringManager;


class BfmeItemKA;
extern BfmeItemKA **g_bfmeBegKA, **g_bfmeEndKA;


struct Rva00260826 : _STL::_Vector_base<BfmeStringRecord005DDD40,_STL::allocator<BfmeStringRecord005DDD40> > {
 __forceinline Rva00260826():_STL::_Vector_base<BfmeStringRecord005DDD40,_STL::allocator<BfmeStringRecord005DDD40> >(_STL::allocator<BfmeStringRecord005DDD40>()){}
 ~Rva00260826();
};

class SubTitleWindow
{
public:
 ~SubTitleWindow();
	SubTitleWindow(GameFont *font, float originX, float bottomY, int boxWidth, int count, int i6, int i7);
private:
	DisplayString *m_00;
	GameFont *m_04;
	Rva00260826 m_vec;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	DisplayString **m_34;
	DisplayString **m_38;
	int m_3c;
	int m_40;
	float m_44;
	float m_48;
	float m_4c;
	float m_50;
	float m_54;
	float m_58;
	float m_5c;
	float m_60;
	float m_64;
	float m_68;
};


SubTitleWindow::SubTitleWindow(GameFont *font, float originX, float bottomY, int boxWidth, int count, int i6, int i7)
	: m_00(0)
	, m_04(font)
	, m_vec()
	, m_14(4)
	, m_18(i6)
	, m_1c(0)
	, m_20(boxWidth)
	, m_24(count)
	, m_28(0)
	, m_2c(i7)
	, m_30(0)
	, m_34(0)
	, m_38(0)
	, m_3c(0)
	, m_40(0)
	, m_44(0.0f)
	, m_48(0.0f)
	, m_4c(0.0f)
	, m_50(0.0f)
	, m_54(0.0f)
	, m_58(0.0f)
	, m_5c(0.0f)
	, m_60(0.0f)
	, m_64(0.0f)
	, m_68(0.0f)
{
	m_34 = new DisplayString *[count];
	m_38 = new DisplayString *[m_24];
	for (int i = 0; i < m_24; ++i) {
		m_34[i] = TheDisplayStringManager->newDisplayString();
		m_34[i]->setFont(m_04);
	}
	int textWidth;
	int lineHeight;
	{
		m_34[0]->setText(UnicodeString((const unsigned short*)L" "));
		m_34[0]->getSize(&textWidth, &lineHeight);
		m_30=lineHeight;
        m_48=(float)lineHeight*(1.0f/15.0f);
        m_4c=originX;
        m_50=bottomY-(float)((m_24-1)*lineHeight);
        m_54=(float)m_20+originX;
        m_58=bottomY;
        m_5c=(float)(lineHeight>>1)+originX;
        m_60=(float)(lineHeight>>1)+m_50;
        m_64=(float)m_20-(float)lineHeight+m_5c;
        m_68=(float)((m_24-2)*lineHeight)+m_60;
	}
	((_STL::vector<const ModuleData *>*)&g_bfmeBegKA)->push_back((const ModuleData *)this);
	DisplayString *cur = TheDisplayStringManager->newDisplayString();
	m_00 = cur;
	cur->setFont(font);
}

SubTitleWindow::~SubTitleWindow() {
 if(TheDisplayStringManager) {
  for(int i=0;i<m_24;++i)
   TheDisplayStringManager->freeDisplayString(m_34[i]);
  if(m_00)
   TheDisplayStringManager->freeDisplayString(m_00);
 }
 m_00=0;
 delete[] m_34;
 SubTitleWindow *self=this;
 SubTitleWindow **found=_STL::find((SubTitleWindow**)g_bfmeBegKA,(SubTitleWindow**)g_bfmeEndKA,self);
 if(found!=(SubTitleWindow**)g_bfmeEndKA)
  ((_STL::vector<void*>*)&g_bfmeBegKA)->erase((void**)found);
}

