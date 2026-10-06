// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ?_M_clear@?$vector@V?$vector@UBfmePod88@@V?$allocator@UBfmePod88@@@_STL@@@_STL@@V?$allocator@V?$vector@UBfmePod88@@V?$allocator@UBfmePod88@@@_STL@@@_STL@@@2@@_STL@@IAEXXZ @0x00500EDC 30B: outer vector _M_clear.
// Evidence: callers 0x00500EFA and 0x0050129F call here as this->_M_clear before _M_set; callees rowed 0x00500AF8 and 0x00030830; shape matches rowed _M_clear 0x003F5EF7.

struct BfmePod88
{
	char m_body[88];
};

struct Rva004FABE2
{
	void *m_start;
	void *m_finish;
	void *m_end;
};

void __cdecl Rva00500AF8Destroy(Rva004FABE2 *first, Rva004FABE2 *last);
extern "C" void __cdecl free(void *block);

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_clear();

private:
	Type *m_start;
	Type *m_finish;
	void *m_endOfStorage;
};

typedef vector<BfmePod88, allocator<BfmePod88> > Pod88Vec;
typedef vector<Pod88Vec, allocator<Pod88Vec> > OuterVec;
}

void _STL::vector<_STL::Pod88Vec, _STL::allocator<_STL::Pod88Vec> >::_M_clear()
{
	Rva00500AF8Destroy((Rva004FABE2 *)m_start, (Rva004FABE2 *)m_finish);
	if (m_start)
		free((void *)m_start);
}
