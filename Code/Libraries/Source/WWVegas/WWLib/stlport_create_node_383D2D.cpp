// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// Free node create at 0x00383D2D 34B calling rowed byte allocate plus rowed Construct for Rva003829E5. Evidence: prev same flags plus callees 0x000307F0 plus 0x0038350D plus ret 4 plus callers 0x00384240 plus 0x00384259.
#include <memory>

class Rva003829E5
{
public:
	Rva003829E5(const Rva003829E5 &other);
};

void *__stdcall Rva00383D2DCreate(const void *value)
{
	char *raw = _STL::allocator<char>::allocate(0x34, 0);
	Rva003829E5 *slot = (Rva003829E5 *)(raw + 0x10);
	_STL::_Construct<Rva003829E5, Rva003829E5>(slot, *(const Rva003829E5 *)value);
	return raw;
}
