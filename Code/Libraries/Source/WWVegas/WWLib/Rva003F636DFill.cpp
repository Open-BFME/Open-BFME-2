// cl: /MD
// ?Rva003F636DFill@@YAXPAXI0@Z @0x003F636D 27B evidence: leaf free wrapper via rowed fill-n 0x003F631B object-symbol plus caller 0x003F6C74

namespace _STL
{
	struct __false_type {};
}
struct EvaMessageInfo;
namespace _STL
{
	template <class ForwardIter, class Size, class T>
	ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x, const __false_type &);
}

void Rva003F636DFill(void *first, unsigned int n, void *x)
{
	_STL::__false_type t;
	_STL::__uninitialized_fill_n((EvaMessageInfo *)first, n, *(const EvaMessageInfo *)x, t);
}
