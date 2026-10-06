// cl: /DNDEBUG /MD /GX
// ??1Rva003378D0@@QAE@XZ @0x003378D0 63B vector destroy plus free.
// Evidence: retail 63B EH with __EH_prolog FuncInfo 0x00B7C33A; callees rowed Destroy 0x003376D1 and rowed game free 0x00030830; caller 0x00337B1A lea ecx esi+B0 in outer dtor 0x00337AA8; pattern follows RvaVectorDtorFamily 63B dtors with /GX for or [ebp-4],-1.
extern "C" void __cdecl free(void *block);
namespace _STL
{
template <class I> void __cdecl _Destroy(I first, I last);
}
class Rva003371B1;
template <class E> struct Rva003378D0Base
{
	E *m_start;
	E *m_finish;
	E *m_endOfStorage;
	~Rva003378D0Base()
	{
		if (m_start)
			free(m_start);
	}
};
struct Rva003378D0 : Rva003378D0Base<Rva003371B1>
{
	~Rva003378D0();
};
Rva003378D0::~Rva003378D0()
{
	_STL::_Destroy(m_start, m_finish);
}
