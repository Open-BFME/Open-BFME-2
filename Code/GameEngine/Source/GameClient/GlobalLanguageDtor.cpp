// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??1GlobalLanguage@@UAE@XZ retail 0x001EABAB 446 bytes.
// GlobalLanguage destructor: vtable 0x007DEFC8 then list at +0x138 via rowed
// List_base dtor 0x001EA97D then 28 string members via rowed releaseBuffer
// 0x00036410 then base GameEngineDeletingBase dtor 0x001B4E74. Layout from
// retail offsets: 5 AsciiStrings at +0xC-0x1C then 23 FontDescs at
// +0x20-0x128 (AsciiString at +0) then Real at +0x134 then list at +0x138.
// Identity: vtable followed by Language string plus same class as rowed
// adjustFontSize 0x001EA40D plus initSubsystem<GlobalLanguage> literal
// 0x00DFDC84 plus callers feeding getFont. ZH donor GlobalLanguage.h plus
// BFME1 GlobalLanguage.cpp field table; BFME2 adds members so retail offsets
// rule. Base size 0xC from GameEngineDeletingBaseDtor.cpp row.
#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <list>

#include "ascii_string.h"


struct FontDesc
{
	AsciiString name;
	int size;
	bool bold;
};

struct Rva001EA443
{
	StringBase<char> m_text0;
	StringBase<char> m_text1;
	Rva001EA443();
	Rva001EA443(const Rva001EA443 &);
	~Rva001EA443();
};

inline bool operator==(const Rva001EA443 &x, const Rva001EA443 &y) { return false; }
inline bool operator<(const Rva001EA443 &x, const Rva001EA443 &y) { return false; }


// Preserve retail's inline node/buffer free; the public allocator is supplied by its verified owner.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<_List_node< ::Rva001EA443 > >::deallocate(_List_node< ::Rva001EA443 > *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[4];
	AsciiString m_member08;
};

class GlobalLanguage : public GameEngineDeletingBase
{
public:
	virtual ~GlobalLanguage();
private:
	AsciiString m_s00C;
	AsciiString m_s010;
	AsciiString m_s014;
	AsciiString m_s018;
	AsciiString m_s01C;
	FontDesc m_f020;
	FontDesc m_f02C;
	FontDesc m_f038;
	FontDesc m_f044;
	FontDesc m_f050;
	FontDesc m_f05C;
	FontDesc m_f068;
	FontDesc m_f074;
	FontDesc m_f080;
	FontDesc m_f08C;
	FontDesc m_f098;
	FontDesc m_f0A4;
	FontDesc m_f0B0;
	FontDesc m_f0BC;
	FontDesc m_f0C8;
	FontDesc m_f0D4;
	FontDesc m_f0E0;
	FontDesc m_f0EC;
	FontDesc m_f0F8;
	FontDesc m_f104;
	FontDesc m_f110;
	FontDesc m_f11C;
	FontDesc m_f128;
	float m_res134;
	_STL::list<Rva001EA443, _STL::allocator<Rva001EA443> > m_list138;
};

GlobalLanguage::~GlobalLanguage() {}
void famgenDeleteGlobalLanguage(GlobalLanguage *p) { delete p; }
