// ?rva0059904A@Rva0059904A@@QAEXXZ
// cl: /GX- /Oy- /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?rva0059904A@Rva0059904A@@QAEXXZ 0x0059904A 149B
// Clear two polymorphic pointer vectors via virtual destroy plus delete then
// vector clear plus hero unregister via rowed 0x002A8F24 plus rowed 0x004DFB55.
// Evidence: callees 0x0002FD60 plus 0x0031BD55 plus 0x002A8F24 plus 0x004DFB55
// all rowed; caller ctor at 0x005990DF; g_00DFEEF8 global.
// The destroy result is materialised into a delete argument that is always
// passed (mem = zero; if (obj) mem = obj->destroy(zero); operator delete(mem)),
// reproducing retail's xor-eax-cmp plus push-eax and the unconditional delete.
// The trailing clear() is load-bearing: STLport's clear is the form that
// materialises andm_08 into edi and reuses edi for andm_14, as retail does,
// whereas erase(begin, end) makes MSVC7.1 recompute the args from esi and swap
// edi/ebx. See reverse/re_attempts.log for both shapes.
#include <vector>

struct Polymorph004F
{
	virtual void *destroy(unsigned int flags);
};

class Player;
class CreateAHeroData;

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
};

class Rva004DFB55
{
public:
	void rva004DFB55(CreateAHeroData *p);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva0059904A
{
public:
	void rva0059904A();
private:
	char m_00[8];
	_STL::vector<void *> m_08;
	_STL::vector<void *> m_14;
	Player *m_20;
};

void Rva0059904A::rva0059904A()
{
	unsigned int zero = 0;
	void **finish1 = m_08.end();
	for (void **p = m_08.begin(); p != finish1; ++p)
	{
		Polymorph004F *obj = (Polymorph004F *)*p;
		void *mem = (void *)zero;
		if (obj != (Polymorph004F *)zero)
			mem = obj->destroy(zero);
		::operator delete(mem);
	}
	m_08.clear();
	void **finish2 = m_14.end();
	for (void **p = m_14.begin(); p != finish2; ++p)
	{
		Polymorph004F *obj = (Polymorph004F *)*p;
		void *mem = (void *)zero;
		if (obj != (Polymorph004F *)zero)
			mem = obj->destroy(zero);
		::operator delete(mem);
	}
	m_14.clear();
	void *holder = g_00DFEEF8->rva002A8F24(m_20);
	((Rva004DFB55 *)holder)->rva004DFB55((CreateAHeroData *)((char *)this - 12));
}
