// cl: /O1 /MD
// ?rva002C5FE8@Rva002C5FE8@@QAEPAXH@Z 0x002C5FE8 34B search pointer table at +0x20/+0x24 for entry whose first dword equals key
// Evidence: retail loops eax=[ecx+0x20] to edx=[ecx+0x24], double-derefs each element and compares to stack arg, returns entry or null; caller 0x005AB7C4 passes its own arg through
class Rva002C5FE8
{
public:
	void *rva002C5FE8(int key);
	void rva002C60A9(unsigned int key);
	char m_lead[0x20];
	void **m_begin;
	void **m_end;
};
void *Rva002C5FE8::rva002C5FE8(int key)
{
	void **end = m_end;
	for (void **p = m_begin; p != end; ++p)
	{
		if (*(int *)*p == key)
			return *p;
	}
	return 0;
}

namespace _STL {
template <class _Tp> class allocator {};
template <class _Tp, class _Alloc> class vector {
public:
	void **erase(void **__pos);
};
}
void __cdecl operator delete(void *p);

void Rva002C5FE8::rva002C60A9(unsigned int key)
{
	typedef _STL::vector<void *, _STL::allocator<void *> > Vec;
	Vec *vec = (Vec *)&m_begin;
	for (void **p = m_begin; p != m_end;)
	{
		if (*(int *)*p == (int)key)
		{
			void *elem = *p;
			if (elem)
				operator delete(elem);
			p = vec->erase(p);
		}
		else
		{
			++p;
		}
	}
}
