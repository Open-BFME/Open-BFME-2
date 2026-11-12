// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0Rva0023E8D8@@QAE@PAX@Z 0x0023E8D8 53B retail ctor wrapper holding refcounted impl with func ptr
#include <new.h>
#include <new>

#include "../../../../GameEngine/Include/Common/Rva00080221RefImpl.h"
class Rva0023E8D8Impl : public Rva00080221RefImpl
{
public:
	void *m_func;
	Rva0023E8D8Impl(void *funcHolder) { m_func = *(void **)funcHolder; }
};

class Rva0023E8D8
{
	Rva0023E8D8Impl *m_ptr;
public:
	Rva0023E8D8(void *funcHolder);
};

// Select-any like the four identical consumer copies (this retail body comes
// first in link order, so it is the copy the link keeps); the anchor keeps the
// body emitted.
inline Rva0023E8D8::Rva0023E8D8(void *funcHolder)
{
	Rva0023E8D8Impl *impl = new Rva0023E8D8Impl(funcHolder);
	m_ptr = impl;
	if (impl)
		++impl->m_ref;
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitRva0023E8D8Ctor@@YAXPAVRva0023E8D8@@PAX@Z absent-from-retail
void bfmeEmitRva0023E8D8Ctor(Rva0023E8D8 *storage, void *funcHolder)
{
	new (storage) Rva0023E8D8(funcHolder);
}
