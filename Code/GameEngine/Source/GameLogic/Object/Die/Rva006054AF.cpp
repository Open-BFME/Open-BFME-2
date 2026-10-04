// cl: /O1 /MD
// ?rva006054AF@Rva006054AF@@QAEPAXPBD@Z, retail 0x006054AF (56B).
// Unlock: missing callee of 3 free functions; deque push_back helper that
// strdups via rowed new[] 0x0002FDE0 plus strlen 0x00629170 plus _mbscpy
// 0x00629176 then rowed deque push_back 0x00423BD8. Callers 0x006014A3
// 0x00601556 0x006045E1 0x00604667; neighbours 0x00605464 and 0x006054E7.
extern "C" unsigned int __cdecl strlen(const char *str);
extern "C" char *__cdecl _mbscpy(char *dst, const char *src);
void *__cdecl operator new[](unsigned int size);

namespace _STL {
template <class _Tp> class allocator
{
};
template <class _Tp, class _Alloc> class deque
{
public:
	void push_back(const _Tp &val);
};
}

class Rva006054AF
{
public:
	void *rva006054AF(const char *text);
};

void *Rva006054AF::rva006054AF(const char *text)
{
	unsigned int len = strlen(text);
	void *buf = operator new[](len + 1);
	_mbscpy((char *)buf, text);
	((_STL::deque<void *, _STL::allocator<void *> > *)this)->push_back(buf);
	return buf;
}
