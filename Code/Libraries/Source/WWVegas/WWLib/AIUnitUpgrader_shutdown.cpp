// ?shutdown@AIUnitUpgrader@@QAEXXZ
// cl: /GX- /Oy- /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?shutdown@AIUnitUpgrader@@QAEXXZ 0x0059904A 149B
// Clear two polymorphic pointer vectors via virtual destroy plus delete then
// vector clear plus hero unregister via rowed 0x002A8F24 plus rowed 0x004DFB55.
// Evidence: callees 0x0002FD60 plus 0x0031BD55 plus 0x002A8F24 plus 0x004DFB55
// all rowed; caller ctor at 0x005990DF; TheSkirmishAIManager global.
// The destroy result is materialised into a delete argument that is always
// passed (mem = zero; if (obj) mem = obj->destroy(zero); operator delete(mem)),
// reproducing retail's xor-eax-cmp plus push-eax and the unconditional delete.
// The trailing clear() is load-bearing: STLport's clear is the form that
// materialises andm_08 into edi and reuses edi for andm_14, as retail does,
// whereas erase(begin, end) makes MSVC7.1 recompute the args from esi and swap
// edi/ebx. See reverse/re_attempts.log for both shapes.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>

// vector<void*> begin/end/clear are expanded inline here; their out-of-line copies
// would differ from retail's. Declared imported and force-inlined, they are not emitted.
// Keep vector<void*> accessors inline without emitting this unit's COMDAT
// copies: retail's out-of-line ones are the /Od bodies at 0x00023B90-0x00023C20.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void *const *vector<void*>::begin() const { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end() { return this->_M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const { return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n) { return *(begin() + __n); }
template <> __declspec(dllimport) __forceinline
void *const &vector<void*>::operator[](size_t __n) const { return *(begin() + __n); }
}
namespace _STL {
template <> void **vector<void *>::erase(void **first, void **last);
template <> __declspec(dllimport) __forceinline
void vector<void *>::clear() { erase(begin(), end()); }
}

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

extern Rva002A8F24 *TheSkirmishAIManager;

class AIUnitUpgrader
{
public:
	void shutdown();
private:
	char m_00[8];
	_STL::vector<void *> m_08;
	_STL::vector<void *> m_14;
	Player *m_20;
};

void AIUnitUpgrader::shutdown()
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
	void *holder = TheSkirmishAIManager->rva002A8F24(m_20);
	((Rva004DFB55 *)holder)->rva004DFB55((CreateAHeroData *)((char *)this - 12));
}
