// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva00587F69@@UAE@XZ, retail 0x00587F69 59B.
// Dtor: derived from Rva005D6FCC (vptr+held at +0, vtbl 0x00C75C38) with char* at +8
// freed via rowed _free 0x00030830 then base dtor (ICF twin of rowed apply 0x005D6FDE).
// Caller 0x00587F4D 28B is ??_G (push esi call test flag call delete) which becomes ready.
extern "C" void __cdecl free(void *block) throw(...);

class Rva005D6FCC
{
public:
	Rva005D6FCC(void *held);
	virtual ~Rva005D6FCC();
	void *m_held;
};

class __declspec(novtable) Rva00587F69 : public Rva005D6FCC
{
public:
	virtual ~Rva00587F69();
private:
	char *m_08;
};

Rva00587F69::~Rva00587F69()
{
	if (m_08)
		free(m_08);
}
