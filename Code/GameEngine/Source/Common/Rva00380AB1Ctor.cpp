// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0Rva00380AB1@@QAE@PAX@Z @ 0x00380AB1 (53B): ctor wrapper holding refcounted impl with func ptr twin of Rva0023E8D8. Retail new 0xc stores vtable 0x00C18F08 refcount func from *arg then AddRef. Caller 0x00380BE7.
#include <new.h>
#include <new>

#include "../../Include/Common/Rva00080221RefImpl.h"
class Rva00380AB1Impl : public Rva00080221RefImpl
{
public:
	void *m_func;
	Rva00380AB1Impl(void *p) { m_func = *(void **)p; }
};

class Rva00380AB1
{
	Rva00380AB1Impl *m_ptr;
public:
	Rva00380AB1(void *p);
};

// Select-any like the identical consumer copies (AptGuiFXInit.cpp,
// AptGlobalCallbackRegistration.cpp); a strong copy here duplicated them at
// link. The anchor keeps the body emitted.
inline Rva00380AB1::Rva00380AB1(void *p)
{
	Rva00380AB1Impl *q = new Rva00380AB1Impl(p);
	m_ptr = q;
	if (q)
		++q->m_ref;
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitRva00380AB1Ctor@@YAXPAVRva00380AB1@@PAX@Z absent-from-retail
void bfmeEmitRva00380AB1Ctor(Rva00380AB1 *p, void *q)
{
	new (p) Rva00380AB1(q);
}
