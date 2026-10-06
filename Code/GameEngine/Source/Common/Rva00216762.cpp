// cl: /DNDEBUG /MD /EHsc
// ?rva00216762@Rva00216762@@QAEPAXABU?$pair@$$CBVAsciiString@@VGen_003A8BE0@@@_STL@@@Z, retail 0x00216762, 37 bytes.
// Evidence: allocate 0x14 via row 0x000307F0 plus _Construct row 0x002165EB at +4 with and [esi],0 head;
// caller 0x00216D87 passes this in ecx plus pair ref; twin of Rva0046AC30 _M_create_node style.
class AsciiString;
class Gen_003A8BE0;

namespace _STL
{
template <class _T1, class _T2> struct pair;
template <class _T> class allocator
{
public:
	static _T *allocate(unsigned int n, const void *hint);
};
template <class _T1, class _T2> void _Construct(_T1 *p, const _T2 &value);
}

class Rva00216762
{
public:
	void *rva00216762(const _STL::pair<const AsciiString, Gen_003A8BE0> &v);
};

void *Rva00216762::rva00216762(const _STL::pair<const AsciiString, Gen_003A8BE0> &v)
{
	char *mem = _STL::allocator<char>::allocate(0x14, 0);
	*(int *)mem = 0;
	_STL::_Construct((_STL::pair<const AsciiString, Gen_003A8BE0> *)(mem + 4), v);
	return mem;
}
