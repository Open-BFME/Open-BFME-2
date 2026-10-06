// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva00281A06@@QAE@XZ, RVA 0x00281A06, 15 bytes.
// Holder dtor freeing pointer at +0x1C via rowed _free at 0x00030830.
// Evidence: mov eax [ecx+0x1C] test je push eax call free pop ecx ret;
// callers destroy array elements then operator delete (0x002827F3 loop).
extern "C" void __cdecl free(void *block);
struct Rva00281A06
{
	~Rva00281A06();
	char m_pad[0x1C];
	void *m_1C;
};

Rva00281A06::~Rva00281A06()
{
	if (m_1C)
		free(m_1C);
}
