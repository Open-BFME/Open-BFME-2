// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
//
// ?rva00414148@Rva00414148@@QAEXXZ, retail 0x00414148, 30 bytes. Honest
// range-destroy then free: destroys [this+0, this+4) via rowed 0x0022D941
// then frees [this+0] via rowed _free 0x00030830. Evidence: chain packet
// calls just-landed 0x0022D941; caller at 0x0041423A passes this; same
// destroy-then-free shape as 0x0022DBAA.
struct Rva0022CD2A
{
	~Rva0022CD2A();
};

void __cdecl Rva0022D941Destroy(struct Rva0022CD2A *first, struct Rva0022CD2A *last) throw();
extern "C" void __cdecl free(void *block) throw();

class Rva00414148
{
public:
	void rva00414148();
private:
	struct Rva0022CD2A *m_first;
	struct Rva0022CD2A *m_last;
};

void Rva00414148::rva00414148()
{
	Rva0022D941Destroy(m_first, m_last);
	if (m_first != 0)
		free(m_first);
}
