// cl: /O1 /MD
// ?Rva003F636DFill@@YAXPAXI0@Z @0x003F636D 27B evidence: leaf free wrapper via rowed fill-n 0x003F631B object-symbol plus caller 0x003F6C74
struct BfmeStringRecord00111ACF;
namespace _STL
{
	struct __false_type {};
}
void __cdecl dup_003f631b(void);
typedef void (__cdecl *FillNFn)(BfmeStringRecord00111ACF *, unsigned int, const BfmeStringRecord00111ACF &, const _STL::__false_type &);

void Rva003F636DFill(void *first, unsigned int n, void *x)
{
	_STL::__false_type t;
	((FillNFn)&dup_003f631b)((BfmeStringRecord00111ACF *)first, n, *(const BfmeStringRecord00111ACF *)x, t);
}
