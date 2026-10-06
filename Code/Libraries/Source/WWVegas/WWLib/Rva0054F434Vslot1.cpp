// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva0054F434@@UAE@XZ @0x0054F434 123B
// Evidence: virtual dtor with vtable 0x0086AA10 clears AsciiString at +0x64 via
// rowed releaseBuffer 0x00036410 then tree at +0x58 via rowed 0x000730DE then
// list at +0x48 via rowed 0x002FECBC then frees ptr at +0x3C via rowed _free
// 0x00030830 then vector at +0x30 via rowed 0x0002CC70 then list at +0x04 via
// rowed 0x002FECBC. Caller 0x0054F41B which is its ??_G. Unblocks 0x0054F418.
#include <vector>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


#include "ascii_string.h"

extern "C" void __cdecl free(void *block);

class Rva00072FE6
{
public:
	~Rva00072FE6();
private:
	void *m_header;
	int m_flag;
};

class Rva0054F434Buf
{
public:
	~Rva0054F434Buf() { if (m_ptr != 0) ::free(m_ptr); }
private:
	void *m_ptr;
};

class Rva0054F434Base
{
public:
	virtual ~Rva0054F434Base();
};

// ??1Rva0054F434Base@@UAE@XZ present-unmatched
inline Rva0054F434Base::~Rva0054F434Base()
{
}

class Rva0054F434 : public Rva0054F434Base
{
public:
	virtual ~Rva0054F434();
	virtual _STL::list<AsciiString, _STL::allocator<AsciiString> > rva0054F3E2();
private:
	_STL::_List_base<AsciiString, _STL::allocator<AsciiString> > m_list04;
	char m_padA[0x30 - 0x04 - sizeof(_STL::_List_base<AsciiString, _STL::allocator<AsciiString> >)];
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_vec30;
	Rva0054F434Buf m_buf3C;
	char m_padB[0x48 - 0x3C - sizeof(Rva0054F434Buf)];
	_STL::_List_base<AsciiString, _STL::allocator<AsciiString> > m_list48;
	char m_padC[0x58 - 0x48 - sizeof(_STL::_List_base<AsciiString, _STL::allocator<AsciiString> >)];
	Rva00072FE6 m_tree58;
	char m_padD[0x64 - 0x58 - sizeof(Rva00072FE6)];
	AsciiString m_str64;
};

Rva0054F434::~Rva0054F434()
{
}

#pragma optimize("y", off)
_STL::list<AsciiString, _STL::allocator<AsciiString> > Rva0054F434::rva0054F3E2()
{
	return *(_STL::list<AsciiString, _STL::allocator<AsciiString> > *)&m_list04;
}
#pragma optimize("", on)
