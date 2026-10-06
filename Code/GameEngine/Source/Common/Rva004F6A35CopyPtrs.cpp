// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??$__copy_ptrs@PAUTreeHintRef00217D4C@@PAU1@@_STL@@YAPAUTreeHintRef00217D4C@@PAU1@00ABU__false_type@0@@Z @0x004F6A35 29B chain dispatcher via rowed 5-arg __copy.
// Evidence: retail pushes 0 plus local tag and forwards 3 pointers to rowed 5-arg
// _STL::__copy at 0x005E1A87; 4-arg callers at 0x004F6E47 0x004F70D1 0x000819EC pass tag;
// same 29B shape as rowed __copy_ptrs 0x00204A13 via __copy and Rva002CF830Copy 29B dispatcher.
struct TreeHintRef00217D4C
{
	void *m_target;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};

namespace _STL
{
struct __false_type
{
};
struct random_access_iterator_tag
{
};
template <class _In, class _Out, class _Dist>
_Out __copy(_In, _In, _Out, const random_access_iterator_tag &, _Dist *);
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
}

template <>
__declspec(noinline) TreeHintRef00217D4C *_STL::__copy_ptrs<TreeHintRef00217D4C *, TreeHintRef00217D4C *>(TreeHintRef00217D4C *first, TreeHintRef00217D4C *last, TreeHintRef00217D4C *result, const _STL::__false_type &tag)
{
	_STL::random_access_iterator_tag tmp;
	return _STL::__copy(first, last, result, tmp, (int *)0);
}

TreeHintRef00217D4C *Rva004F6E47Copy(TreeHintRef00217D4C *first, TreeHintRef00217D4C *last, TreeHintRef00217D4C *result)
{
	_STL::__false_type tag;
	return _STL::__copy_ptrs(first, last, result, tag);
}
