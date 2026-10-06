// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva004534A1Create@@YGPAXABVRva004530ED@@@Z @ 0x004534A1 34B: list node create allocating 0x1c via rowed 0x000307F0 and constructing Rva004530ED at +8 via rowed 0x0045323C. Evidence: caller 0x00453AB8 list insert links node; same shape as Rva00397CC9Alloc 0x00397CC9 and Rva002FE8AA 0x002FE8AA.
namespace _STL
{
	template <class T> class allocator
	{
	public:
		static char *allocate(unsigned int n, const void *hint);
	};
}
class Rva004530ED;
void __cdecl Rva0045323CCopy(Rva004530ED *dst, const Rva004530ED &src);
void *__stdcall Rva004534A1Create(const Rva004530ED &src)
{
	char *p = _STL::allocator<char>::allocate(0x1c, 0);
	Rva0045323CCopy((Rva004530ED *)(p + 8), src);
	return p;
}
