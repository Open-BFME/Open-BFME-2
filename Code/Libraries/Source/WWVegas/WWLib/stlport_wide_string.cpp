// cl: /Ireference/shims/bfmealloc /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
// STLport 4.6 wide-string instantiations.

#include <string>
// bfme link decl-only begin
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::reserve(unsigned int); }
// The retail insert helper is emitted by stlport_wide_string_insert_aux.cpp.
// Calls here must use that body instead of this header's competing copy.
namespace _STL { template <> unsigned short *basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_insert_aux(unsigned short *, unsigned short); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAGPAG@_STL@@YAPAGPAG00ABU__true_type@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned short *__uninitialized_copy<unsigned short *, unsigned short *>(unsigned short *, unsigned short *, unsigned short *, const __true_type &); }
// Suppress this TU's non-retail copy of ?_M_deallocate_block@?$_String_base@GV?$allocator@G@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<unsigned short, allocator<unsigned short> >::_M_deallocate_block(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@G@_STL@@QAEXPAGI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<unsigned short>::deallocate(unsigned short *, size_t); }


// Retail assignment calls erase at 0x13110 instead of inlining it.
// Preserve STLport's erase body and its separately verified 65-byte copy.
namespace _STL {
template <> __declspec(noinline) inline basic_string<unsigned short>::iterator
basic_string<unsigned short>::erase(iterator first, iterator last)
{
    if (first != last) {
        traits_type::move(first, last, (this->_M_finish - last) + 1);
        pointer newFinish = this->_M_finish - (last - first);
        _Destroy(newFinish + 1, this->_M_finish + 1);
        this->_M_finish = newFinish;
    }
    return first;
}
}

// The range append provider is shared with the verified assignment worker.
// Specialize the member template for this string type, retaining its iterator
// parameter, as supported by VC7.1.
namespace _STL {
template <> template <class InputIter> basic_string<unsigned short> &
basic_string<unsigned short>::append(
    InputIter, InputIter, const forward_iterator_tag &);
template <> template <class InputIter> inline basic_string<unsigned short> &
basic_string<unsigned short>::_M_assign_dispatch(
    InputIter first, InputIter last, const __false_type &)
{
    unsigned short *current = _M_start;
    while (first != last && current != _M_finish) {
        traits_type::assign(*current, *first);
        ++first;
        ++current;
    }
    if (first == last)
        erase(current, end());
    else {
        forward_iterator_tag tag;
        append((const unsigned short *)first, (const unsigned short *)last, tag);
    }
    return *this;
}
}

// Instantiate only the members this unit's rows cover; a whole-class
// instantiation also emitted wrong copies of append, op= and friends that
// outrank retail's in link order.
typedef _STL::basic_string<wchar_t, _STL::char_traits<wchar_t>, _STL::allocator<wchar_t> > WideString;
typedef _STL::__char_traits_base<wchar_t, wchar_t> WideCharTraitsBase;
template void WideString::push_back(wchar_t);
template WideString::iterator WideString::insert(WideString::iterator, wchar_t);
template WideString::iterator WideString::erase(WideString::iterator, WideString::iterator);
template WideString::size_type WideString::capacity() const;
template WideString &WideString::assign(wchar_t *, wchar_t *);
template WideString &WideString::operator=(const WideString &);
template void WideString::_M_terminate_string_aux(const _STL::__false_type &);
template void WideString::_M_terminate_string();
template void WideString::_M_construct_null_aux(wchar_t *, const _STL::__true_type &);
template void WideString::_M_construct_null(wchar_t *);
template size_t WideCharTraitsBase::length(const wchar_t *);
template wchar_t *WideCharTraitsBase::move(wchar_t *, const wchar_t *, size_t);
template wchar_t *WideCharTraitsBase::copy(wchar_t *, const wchar_t *, size_t);
template wchar_t *WideCharTraitsBase::assign(wchar_t *, size_t, wchar_t);
template void WideCharTraitsBase::assign(wchar_t &, const wchar_t &);
// Keep the rowed placement constructor that the insert helper used to instantiate.
template void _STL::_Construct<wchar_t, wchar_t>(wchar_t *, const wchar_t &);
template bool _STL::_Eq_traits<_STL::char_traits<wchar_t> >::operator()(const wchar_t &, const wchar_t &) const;
typedef WideString::const_reverse_iterator WideCRI;
// The out-of-line reverse_iterator distance cannot be explicitly instantiated
// under MSVC 7.1 (dependent return type); a noinline caller instantiates it.
// ?bfmeExposeWideReverseDistance absent-from-retail
__declspec(noinline) int bfmeExposeWideReverseDistance(const WideCRI &a, const WideCRI &b)
{
	return a - b;
}
