// cl: /DNDEBUG /MD /EHsc
// ?rva0046AC30@Rva0046AC30@@QAEPAXABVRva00469BEA@@@Z @ 0x0046AC30 34B unlock _M_create_node style.
// Evidence: allocate 0x24 via row 0x000307F0 ?allocate@?$allocator@D@_STL@@SAPADIPBX@Z plus Construct row 0x0046A9FF ??$_Construct@VRva00469BEA@@V1@@_STL@@YAXPAVRva00469BEA@@ABV1@@Z at +0x10; caller 0x0046E455 passes this in ecx plus key pointer.
class Rva00469BEA
{
public:
	Rva00469BEA(const Rva00469BEA &that);
};

namespace _STL
{
template <class T> class allocator
{
public:
	static T *allocate(unsigned int n, const void *hint);
};

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);
}

class Rva0046AC30
{
public:
	void *rva0046AC30(const Rva00469BEA &v);
};

void *Rva0046AC30::rva0046AC30(const Rva00469BEA &v)
{
	char *mem = _STL::allocator<char>::allocate(0x24, 0);
	_STL::_Construct((Rva00469BEA *)(mem + 0x10), v);
	return mem;
}
