// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?erase@?$vector@URva003B8B61Elem@@V?$allocator@URva003B8B61Elem@@@_STL@@@_STL@@QAEPAURva003B8B61Elem@@PAU3@@Z
// @ 0x003F4B51 (56B): single erase over 104-byte vector with virtual destroy.
// If pos+1 != finish, shifts tail down with rowed CopyDispatch 0x003B8B44,
// decrements finish by 0x68, destroys the vacated tail via virtual slot0 with 0,
// returns pos. Follows pod28 single erase shape; prvalue tag keeps tag at [ebp+0xb].
struct Rva003B8B61Elem {
	virtual void destroy(int);
	unsigned char m_pad[0x68 - 4];
};

struct RvaCopyIteratorTag {};
struct RvaVector104Tag : RvaCopyIteratorTag {};

extern "C" void *Rva003B8B44CopyDispatch(void *first, void *last, void *result, const RvaCopyIteratorTag &tag);

namespace _STL {
template <class Type> class allocator {};
template <class Type, class Allocator> class vector {
public:
	typedef Type *iterator;
	iterator erase(iterator pos);
private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};
}

_STL::vector<Rva003B8B61Elem, _STL::allocator<Rva003B8B61Elem> >::iterator
_STL::vector<Rva003B8B61Elem, _STL::allocator<Rva003B8B61Elem> >::erase(iterator pos)
{
	iterator fin = m_finish;
	if (pos + 1 != fin)
		Rva003B8B44CopyDispatch(pos + 1, fin, pos, RvaVector104Tag());
	--m_finish;
	m_finish->destroy(0);
	return pos;
}
