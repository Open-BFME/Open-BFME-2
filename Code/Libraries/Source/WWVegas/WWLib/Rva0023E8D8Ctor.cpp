// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0Rva0023E8D8@@QAE@PAX@Z 0x0023E8D8 53B retail ctor wrapper holding refcounted impl with func ptr
#include <new.h>
#include <new>

struct Rva00080221RefImpl { virtual ~Rva00080221RefImpl() {} int m_ref; Rva00080221RefImpl() : m_ref(0) {} };
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
	Rva0023E8D8Impl *q = new Rva0023E8D8Impl(funcHolder);
	m_ptr = q;
	if (q)
		++q->m_ref;
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitRva0023E8D8Ctor@@YAXPAVRva0023E8D8@@PAX@Z absent-from-retail
void bfmeEmitRva0023E8D8Ctor(Rva0023E8D8 *p, void *q)
{
	new (p) Rva0023E8D8(q);
}
