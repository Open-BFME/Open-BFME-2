// ??1Rva001DEF6B@@QAE@XZ
// partial score=0.97 date=2026-10-04
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva001DEF6B@@QAE@XZ @0x001DEF6B 30B evidence: calls rowed __destroy_aux for Rva00414BDBElement at 0x001DEEE0 plus rowed _free 0x00030830; same Destroy-plus-free shape as 63B 0x001DEEF9 without EH and as rowed 0x0032BF1B; callers at 0x001DEFD1/0x001DF2B5
struct Rva00414BDBElement {
	char m_opaque[48];
	Rva00414BDBElement(const Rva00414BDBElement &);
	Rva00414BDBElement &operator=(const Rva00414BDBElement &);
	~Rva00414BDBElement();
};

namespace _STL {
template <class _ForwardIterator>
void _Destroy(_ForwardIterator, _ForwardIterator);
}

extern "C" void __cdecl free(void *p);

class Rva001DEF6B
{
public:
	~Rva001DEF6B();
private:
	Rva00414BDBElement *m_start;
	Rva00414BDBElement *m_finish;
};

// ??1Rva001DEF6B@@QAE@XZ present-unmatched
Rva001DEF6B::~Rva001DEF6B()
{
	_STL::_Destroy(m_start, m_finish);
	Rva00414BDBElement *s = m_start;
	if (s)
		free(s);
}
