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

// ??1Rva00362B5ADtor@@QAE@XZ retail 0x00362B5A 5 bytes: the destructor of the
// global at 0x00E01E7C (its atexit thunk is the rowed 0x007B7CC3), whose only
// non-trivial member sits at offset 0: a tail jump to ~Rva00362AB5.
class Rva00362B5ADtor
{
public:
	~Rva00362B5ADtor();
private:
	Rva00362AB5 m_00;
};

Rva00362B5ADtor::~Rva00362B5ADtor()
{
}
