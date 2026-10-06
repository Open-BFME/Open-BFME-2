// cl: /DNDEBUG /MD /EHsc
// ?rva0043B1C9@Rva0043B1C9Tree@@QAEPAV1@PBX@Z @0x0043B1C9 39B
// Header-handle alloc helper mirroring AnimationSoundTree::rva004CA018
// (39B, proxy 0x14F3C4 + byte allocator 0x307F0): proxy at this with stack
// uint temp and null, then 0x9c header via rowed allocate stored at +0,
// returning this. Called from 0x0043B214 which becomes ready. Class proven
// by 0x9c size matching BfmePod156 neighbour and sentinel init in caller;
// honest Rva names.
class Rva002390CB;
namespace _STL
{
void __cdecl free(void *block);
template <class _Tp> class allocator
{
public:
	static _Tp *allocate(unsigned int __n, void const *__hint);
};
template <class _P, class _T, class _A> class _STLP_alloc_proxy
{
public:
	_STLP_alloc_proxy(const _A &__a, _P __p);
	_P _M_data;
};
}

inline void *__cdecl operator new(unsigned int, void *__p)
{
	return __p;
}

typedef unsigned int ProxyUInt;

class Rva0043B1C9HeaderHandle
{
public:
	~Rva0043B1C9HeaderHandle()
	{
		if (m_header)
			_STL::free(m_header);
	}

	void *m_header;
};

class Rva0043B1C9Tree
{
public:
	Rva0043B1C9Tree *rva0043B1C9(void const *dummy);
	Rva0043B1C9Tree *rva0043B214(void const *d1, void const *d2);

private:
	Rva0043B1C9HeaderHandle m_handle;
	unsigned int m_count;
};

Rva0043B1C9Tree *Rva0043B1C9Tree::rva0043B1C9(void const *dummy)
{
	(void)dummy;
	_STL::allocator<ProxyUInt> tmp;
	_STL::_STLP_alloc_proxy<ProxyUInt *, ProxyUInt, _STL::allocator<ProxyUInt> > *proxy =
		(_STL::_STLP_alloc_proxy<ProxyUInt *, ProxyUInt, _STL::allocator<ProxyUInt> > *)this;
	__assume(proxy != 0);
	new (proxy) _STL::_STLP_alloc_proxy<ProxyUInt *, ProxyUInt, _STL::allocator<ProxyUInt> >(tmp, (ProxyUInt *)0);
	*(char **)this = _STL::allocator<char>::allocate(0x9c, 0);
	return this;
}

// ?rva0043B214@Rva0043B1C9Tree@@QAEPAV1@PBX0@Z @0x0043B214 42B
// Header init mirroring AnimationSoundTree::rva004CA13D (42B): runs rowed
// rva0043B1C9 alloc with second dummy, zeroes count at +4 and repairs 0x9c
// header sentinel (zero at +0/+4, self at +8/+0xC), returning this. Called
// from 0x0043B69C which becomes ready. Same class/flags as sibling.
Rva0043B1C9Tree *Rva0043B1C9Tree::rva0043B214(void const *d1, void const *d2)
{
	(void)d1;
	rva0043B1C9(d2);
	m_count = 0;
	*(char *)m_handle.m_header = 0;
	*(unsigned int *)((char *)m_handle.m_header + 4) = 0;
	*(void **)((char *)m_handle.m_header + 8) = m_handle.m_header;
	*(void **)((char *)m_handle.m_header + 0x0C) = m_handle.m_header;
	return this;
}
