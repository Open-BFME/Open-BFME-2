// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva005681CE@@QAE@XZ @0x005681CE 63B
// Evidence: chain via 0x00567FA3 Destroy stride16; 63B Destroy-plus-free shape same as 0x004F887C; caller 0x0056820D.
extern "C" void __cdecl free(void *block);

struct Rva004F691E;
void __cdecl Rva00567FA3Destroy(Rva004F691E *first, Rva004F691E *last);

template <class E> struct Rva005681CEBase
{
	E *m_start;
	E *m_finish;
	E *m_endOfStorage;
	~Rva005681CEBase()
	{
		if (m_start)
			free(m_start);
	}
};

struct Rva005681CE : Rva005681CEBase<Rva004F691E>
{
	~Rva005681CE();
};

Rva005681CE::~Rva005681CE()
{
	Rva00567FA3Destroy(m_start, m_finish);
}
