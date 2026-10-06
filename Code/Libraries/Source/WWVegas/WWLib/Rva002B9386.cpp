// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva002B9386@Rva002B9386@@QAEXW4ScienceType@@@Z @0x002B9386 45B.
// Add-if-absent over ScienceType vector at +0x1C: find then push_back.
// Evidence: leaf lane; find pinned ScienceType alias plus push_back rowed
// 0x002E01C6 both at 0x0020E873 0x002E01C6; caller at 0x002BE717;
// same find-plus-push shape as Player addScience.
enum ScienceType
{
	SCIENCE_INVALID = -1
};

namespace _STL {
	template <class _Tp> class allocator
	{
	};
	template <class _Tp, class _Alloc> class vector
	{
	public:
		void push_back(const _Tp &v);
	public:
		_Tp * _M_start;
		_Tp * _M_finish;
		_Tp * _M_end;
	};
	template <class _InputIter, class _Tp>
	_InputIter find(_InputIter __first, _InputIter __last, const _Tp &__val);
}

class Rva002B9386
{
	char m_pad[0x1C];
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_vec1C;
public:
	void rva002B9386(ScienceType t);
};

void Rva002B9386::rva002B9386(ScienceType t)
{
	ScienceType *end = m_vec1C._M_finish;
	if (_STL::find(m_vec1C._M_start, end, t) == end)
		m_vec1C.push_back(t);
}
