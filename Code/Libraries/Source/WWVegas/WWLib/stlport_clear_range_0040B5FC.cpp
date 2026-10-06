// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0040B5FC@Rva0040B5FC@@QAEXXZ @ 0x0040B5FC (30B). Clear holder over 0x68 elements via rowed _Destroy.
// Evidence: retail pushes [esi+4] [esi] then calls rowed ??$_Destroy@PAURva0040AFF3 0x0040B547 then frees [esi]; caller 0x0040B8E8 vector assign; same 30B shape as rowed 0x0040B5DE.
struct Rva0040AFF3;

namespace _STL
{
template <class I> void __cdecl _Destroy(I first, I last);
}

extern "C" void __cdecl free(void *p);

class Rva0040B5FC
{
public:
	void rva0040B5FC();
private:
	Rva0040AFF3 *m_begin;
	Rva0040AFF3 *m_finish;
};

void Rva0040B5FC::rva0040B5FC()
{
	_STL::_Destroy(m_begin, m_finish);
	void *storage = m_begin;
	if (storage)
		free(storage);
}
