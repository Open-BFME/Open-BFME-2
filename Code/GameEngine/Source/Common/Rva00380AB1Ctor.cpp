// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0Rva00380AB1@@QAE@PAX@Z @ 0x00380AB1 (53B): ctor wrapper holding refcounted impl with func ptr twin of Rva0023E8D8. Retail new 0xc stores vtable 0x00C18F08 refcount func from *arg then AddRef. Caller 0x00380BE7.
void *__cdecl operator new(unsigned int);
inline void *__cdecl operator new(unsigned int, void *p) { return p; }

class Rva00380AB1Impl
{
public:
	virtual ~Rva00380AB1Impl();
	int m_ref;
	void *m_func;
	Rva00380AB1Impl(void *p) : m_ref(0) { m_func = *(void **)p; }
};

class Rva00380AB1
{
	Rva00380AB1Impl *m_ptr;
public:
	Rva00380AB1(void *p);
};

Rva00380AB1::Rva00380AB1(void *p)
{
	Rva00380AB1Impl *q = new Rva00380AB1Impl(p);
	m_ptr = q;
	if (q)
		++q->m_ref;
}
