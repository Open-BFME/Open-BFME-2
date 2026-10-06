// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva000C065B@Rva000C065B@@QAEXXZ @0x000C065B 30B
// Range clear via rowed Rva00405337Clear 0x00405337 plus free 0x00030830.
// Evidence: push [esi+4] push [esi] call 0x405337 mov esi [esi] test free; same 30B shape as rowed _M_clear 0xC060A; 3 callers unblocked.
extern "C" void __cdecl free(void *p);
void __cdecl Rva00405337Clear(void *begin, void *end);
class Rva000C065B
{
public:
	void rva000C065B();
private:
	void *m_start;
	void *m_finish;
};
void Rva000C065B::rva000C065B()
{
	Rva00405337Clear(m_start, m_finish);
	void *tmp = m_start;
	if (tmp)
		free(tmp);
}
