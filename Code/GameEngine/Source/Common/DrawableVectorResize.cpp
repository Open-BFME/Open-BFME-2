// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
//
// ?resize@?$vector@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@QAEXIPAVDrawable@@@Z, retail 0x000E6D39 63B.
// Evidence: unlock lane making 2 ready; rowed erase 0x0031BD55 plus Drawable fill-insert 0x00233A5A; ret-8 by-value shape with lea-push forwarding; 63B Pod8 and ObjectID resize precedents.
#include <vector>

class Drawable;

_STLP_BEGIN_NAMESPACE
template <>
class vector<Drawable *, allocator<Drawable *> > : public _Vector_base<Drawable *, allocator<Drawable *> >
{
public:
// ?size@?$vector@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@QBEIXZ present-unmatched
	unsigned int size() const
	{
		return (unsigned int)(_M_finish - _M_start);
	}

	void resize(unsigned int n, Drawable *x);
	void _M_fill_insert(Drawable **position, unsigned int count, Drawable *const &value);
};
_STLP_END_NAMESPACE

typedef _STL::vector<Drawable *, _STL::allocator<Drawable *> > DrawablePtrVector;

// ?resize@?$vector@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@QAEXIPAVDrawable@@@Z
void DrawablePtrVector::resize(unsigned int n, Drawable *drawable)
{
	if (n < size())
		reinterpret_cast<_STL::vector<void *, _STL::allocator<void *> > *>(this)->erase(
			reinterpret_cast<void **>(_M_start + n),
			reinterpret_cast<void **>(_M_finish));
	else
		_M_fill_insert(_M_finish, n - size(), drawable);
}
