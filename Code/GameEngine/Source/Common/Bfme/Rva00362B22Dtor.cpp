// cl: /EHs /MD
//
// ??1Rva00362AB5@@QAE@XZ retail 0x00362B22 56 bytes. Dtor calls clear then
// frees header with EH prolog. Evidence: chain from 0x00362AB5, rowed _free,
// no stack args, null check before free. Holder models conditional free as
// member lifetime to recover EH frame per shape-lever cleanup-member recipe.

extern "C" void __cdecl free(void *block);

struct Rva003628A6Node
{
	int m_00;
	void *m_04;
	Rva003628A6Node *m_08;
	Rva003628A6Node *m_0C;
};

struct HeaderHolder
{
	~HeaderHolder() { if (m_ptr != 0) free(m_ptr); }
	Rva003628A6Node *m_ptr;
};

class Rva00362AB5
{
public:
	void rva00362AB5();
	~Rva00362AB5();
private:
	HeaderHolder m_00;
	int m_04;
};

Rva00362AB5::~Rva00362AB5()
{
	rva00362AB5();
}
