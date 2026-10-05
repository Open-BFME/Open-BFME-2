// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva004F9378@@QAE@XZ retail 0x004F9378 56B
// Rb-tree dtor shell: outline clear 0x004F8DD4 plus null-checked header free via inlined base.
// Evidence: sole callee 0x004F8DD4 rowed in Rva004F8AECErase.cpp plus free 0x00030830 rowed; same 56B EH shape as typed tree dtors 0x0038103F 0x0021B775 0x004D21B4; caller jmp at 0x004F9630.
extern "C" void __cdecl free(void *block);

class Rva004F8DD4
{
public:
	void rva004F8DD4();
};

struct Rva004F9378Base
{
	void *m_header;
	~Rva004F9378Base();
};

// ??1Rva004F9378Base@@QAE@XZ present-unmatched
inline Rva004F9378Base::~Rva004F9378Base()
{
	void *p = m_header;
	if (p)
		free(p);
}

class Rva004F9378 : public Rva004F9378Base
{
	unsigned m_count;
public:
	~Rva004F9378();
};

Rva004F9378::~Rva004F9378()
{
	((Rva004F8DD4 *)this)->rva004F8DD4();
}
