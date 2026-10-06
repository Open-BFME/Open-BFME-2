// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva00055864Free@@YGXPAURva00055864Node@@@Z @ 0x00055864 (28B).
// Opaque node deleter calling pinned dtor ??1Rva005333F then rowed free.
// Evidence: sole caller is deque clear loop 0x00056DA2; same flags as neighbours.
class Rva005333F
{
public:
	virtual ~Rva005333F() throw();
};

struct Rva00055864Node
{
	void *m_next;
	Rva005333F m_val;
};

extern "C" void __cdecl free(void *block);

void __stdcall Rva00055864Free(Rva00055864Node *p)
{
	p->m_val.Rva005333F::~Rva005333F();
	if (p) {
		free(p);
	}
}
