// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0Rva0023E8D8@@QAE@PAX@Z 0x0023E8D8 53B retail ctor wrapper holding refcounted impl with func ptr
void *__cdecl operator new(unsigned int);
inline void *__cdecl operator new(unsigned int, void *p) { return p; }

class Rva0023E8D8Impl
{
public:
	virtual ~Rva0023E8D8Impl();
	int m_ref;
	void *m_func;
	Rva0023E8D8Impl(void *p) : m_ref(0) { m_func = *(void **)p; }
};

class Rva0023E8D8
{
	Rva0023E8D8Impl *m_ptr;
public:
	Rva0023E8D8(void *p);
};

Rva0023E8D8::Rva0023E8D8(void *p)
{
	Rva0023E8D8Impl *q = new Rva0023E8D8Impl(p);
	m_ptr = q;
	if (q)
		++q->m_ref;
}
