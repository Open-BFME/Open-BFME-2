// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??1H1F8167@@QAE@XZ @0x001F8167 88B (the pin spelling). Owner of a pointer
// vector at +0: every element is destroyed through its virtual slot 0 (flag 0)
// and the returned block goes to operator delete (the null element passes a
// null), then the vector buffer frees inline; the EH funclet calls the
// out-of-line pointer-vector dtor 0x0047FAB3. Identity of the pointee and the
// owner is unproven.
#include <stdlib.h>
void Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <vector>
#undef free

void __cdecl operator delete(void *block);

class H1F8167Pointee
{
public:
	virtual void *destroy(int flag);
};

class H1F8167
{
public:
	~H1F8167();
private:
	_STL::vector<H1F8167Pointee *> m_v;
};

H1F8167::~H1F8167()
{
	for (H1F8167Pointee **it = m_v.begin(); it != m_v.end(); ++it)
	{
		H1F8167Pointee *p = *it;
		operator delete(p ? p->destroy(0) : 0);
	}
}
