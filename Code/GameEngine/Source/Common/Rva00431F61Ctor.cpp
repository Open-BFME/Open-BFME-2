// cl: /MD /EHsc
// ??0Rva00431F61@@QAE@XZ @0x00431F61 84B: ctor storing vtable 0x0083C9B8 then helper new 8B with vtable 0x0083C97C plus parent then global. Evidence: unlock lane; EH_prolog row 0x00629188; new row 0x0002FDA0; vtables g_00C3C9B8 g_00C3C97C; global g_00E0322C; caller 0x0023A541.
extern "C" const void *const __identifier("??_7Rva00431FB5@@6B@")[];
extern "C" const void *const __identifier("??_7Rva004318FC@@6B@")[];

struct Rva00431F61Helper
{
	void *m_vptr;
	void *m_parent;
};

// Retail's unwind of this base subobject calls the rowed 0x00429191
// translator base destructor (??1Rva0042CBB6).
class Rva0042CBB6
{
public:
	virtual ~Rva0042CBB6();
};

class EmptyBase00431F61
{
public:
	EmptyBase00431F61() {}
	~EmptyBase00431F61() { ((Rva0042CBB6 *)this)->Rva0042CBB6::~Rva0042CBB6(); }
};

class FormationTranslator : public EmptyBase00431F61
{
	void *m_vptr;
	unsigned char m_04;
	unsigned char m_05;
	unsigned char m_pad06[2];
	Rva00431F61Helper *m_08;

public:
	FormationTranslator();
};

class FormationTranslator;
// g_00E0322C: matched references place it at VA 0xe0322c (retail .data initial value 0).
FormationTranslator * TheFormationTranslator = 0;

#include <new>

FormationTranslator::FormationTranslator()
{
	m_vptr = (void *)__identifier("??_7Rva00431FB5@@6B@");
	m_04 = 0;
	m_05 = 0;
	void *mem = operator new(8);
	Rva00431F61Helper *h;
	if (mem != 0)
	{
		h = (Rva00431F61Helper *)mem;
		h->m_parent = this;
		h->m_vptr = (void *)__identifier("??_7Rva004318FC@@6B@");
	}
	else
	{
		h = 0;
	}
	m_08 = h;
	TheFormationTranslator = this;
}
