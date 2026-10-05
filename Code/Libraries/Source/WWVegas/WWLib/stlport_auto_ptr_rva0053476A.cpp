// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002EAD62@Rva002EAD62@@QAEXXZ RVA 0x002EAD62 size 23: holder release deleting owned Rva0053476A via its rowed dtor and operator delete; callers are large free functions plus Unwind jmp refs; neighbour STLport vector TUs.
class Rva0053476A
{
public:
	~Rva0053476A() throw();
};

class Rva002EAD62
{
public:
	void rva002EAD62();
private:
	Rva0053476A *m_ptr;
};

void Rva002EAD62::rva002EAD62()
{
	delete m_ptr;
}
