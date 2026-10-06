// cl: /MD /Oy- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

#include <algorithm>
#include <deque>

class LightPoint;

struct Rva00425B75Deleter
{
	void operator()(LightPoint *p) const;
};

template Rva00425B75Deleter _STL::for_each(_STL::deque<LightPoint *>::iterator, _STL::deque<LightPoint *>::iterator, Rva00425B75Deleter);
