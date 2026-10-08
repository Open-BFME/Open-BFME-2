// cl: /MD /EHsc
// ??0Rva00431F61@@QAE@XZ @0x00431F61 84B: ctor storing vtable 0x0083C9B8 then helper new 8B with vtable 0x0083C97C plus parent then global. Evidence: unlock lane; EH_prolog row 0x00629188; new row 0x0002FDA0; vtables g_00C3C9B8 g_00C3C97C; global g_00E0322C; caller 0x0023A541.
extern const void *const g_00C3C9B8[];
extern const void *const g_00C3C97C[];

struct Rva00431F61Helper
{
	void *m_vptr;
	void *m_parent;
};

class EmptyBase00431F61
{
public:
	EmptyBase00431F61() {}
	~EmptyBase00431F61();
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
FormationTranslator * g_00E0322C = 0;

void *__cdecl operator new(unsigned int size);

FormationTranslator::FormationTranslator()
{
	m_vptr = (void *)g_00C3C9B8;
	m_04 = 0;
	m_05 = 0;
	void *mem = operator new(8);
	Rva00431F61Helper *h;
	if (mem != 0)
	{
		h = (Rva00431F61Helper *)mem;
		h->m_parent = this;
		h->m_vptr = (void *)g_00C3C97C;
	}
	else
	{
		h = 0;
	}
	m_08 = h;
	g_00E0322C = this;
}
