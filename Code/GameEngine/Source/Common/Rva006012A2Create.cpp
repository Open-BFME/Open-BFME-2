// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva006012A2@Rva0060126D@@QAEPAXABURva00600F9CElement@@@Z @0x006012A2 34B lane=gap
// Evidence: between Rva0060126D erase 0x0060126D and clear 0x006012C4 same TU /O1 /EHs /MD; rowed allocate 0x000307F0 plus _Construct 0x00600F9C; callers 0x0060131F 0x00601338 in 0x006012ED; unblocks 0x006012ED.
#include <memory>
struct Rva00600F9CElement
{
	Rva00600F9CElement(const Rva00600F9CElement &that);
};
class Rva0060126D
{
public:
	void *rva006012A2(const Rva00600F9CElement &val);
};
void *Rva0060126D::rva006012A2(const Rva00600F9CElement &val)
{
	char *mem = _STL::allocator<char>::allocate(0x20, 0);
	_STL::_Construct((Rva00600F9CElement *)(mem + 0x10), val);
	return mem;
}
