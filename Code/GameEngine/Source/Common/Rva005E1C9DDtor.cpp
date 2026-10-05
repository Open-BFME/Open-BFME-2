// cl: /O1 /DNDEBUG /MD /GX
// ??1Rva005E1C9D@@QAE@XZ @ 0x005E1C9D (63B). Vector-like dtor over TreeHintRef range destroys via rowed 0x005F97BC then base frees via 0x00030830 with null guard. Evidence: callers 0x005E1D23 plus chain from 0x005E1D07 prev next same dir pattern follows RvaVectorDtorFamily 63B dtors.
extern "C" void __cdecl free(void *block);
namespace _STL
{
template <class I> void __cdecl _Destroy(I first, I last);
}
struct TreeHintRef00217D4C
{
	void *m_target;
};
struct Rva005E1C9DBase
{
	TreeHintRef00217D4C *m_start;
	TreeHintRef00217D4C *m_finish;
	TreeHintRef00217D4C *m_endOfStorage;
	~Rva005E1C9DBase()
	{
		if (m_start)
			free(m_start);
	}
};
struct Rva005E1C9D : Rva005E1C9DBase
{
	~Rva005E1C9D();
};
Rva005E1C9D::~Rva005E1C9D()
{
	_STL::_Destroy(m_start, m_finish);
}
