// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }
// istreambuf_iterator<char>::equal is retail's 126-byte body at 0x0000FA00, owned by
// stlport_narrow_istreambuf_iterator_equal.cpp. This unit's copy (with _M_getc out of
// line) is not retail's and came before it in link order; the body still inlines
// here, imported, so the unit emits no copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool istreambuf_iterator<char, char_traits<char> >::equal(const istreambuf_iterator<char, char_traits<char> >& __i) const {
  if (this->_M_buf)
    this->_M_getc();
  if (__i._M_buf)
    __i._M_getc();
  return this->_M_eof == __i._M_eof;
}
}

#include <cstddef>
// __get_monetary_value is retail 0x00011E30 (stlport_narrow_get_monetary_value.cpp); this unit only calls it.
// bfme link decl-only begin
namespace _STL { template <> bool __get_monetary_value<istreambuf_iterator<char, char_traits<char> >, back_insert_iterator<basic_string<char, char_traits<char>, allocator<char> > >, char>(istreambuf_iterator<char, char_traits<char> > &, istreambuf_iterator<char, char_traits<char> >, back_insert_iterator<basic_string<char, char_traits<char>, allocator<char> > >, ctype<char> const &, char, int, char, basic_string<char, char_traits<char>, allocator<char> > const &, bool &); }
// Instantiate the rowed back-insert assignment directly.
template _STL::back_insert_iterator<_STL::basic_string<char> > &
_STL::back_insert_iterator<_STL::basic_string<char> >::operator=(const char &);
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
// bfme link decl-only end
// bfme link decl-only begin
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::_M_insert_aux(char *, char); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void allocator<char>::deallocate(char*, size_t);
template <> char *allocator<char>::allocate(size_t, const void *);
}
namespace _STL {
typedef istreambuf_iterator<char, char_traits<char> > MoneyGetCharIterator;
typedef istreambuf_iterator<wchar_t, char_traits<wchar_t> > MoneyGetWideIterator;

// Narrow consumers expand the standard loop; its standalone copy has no retail owner.
template <> __declspec(dllimport) __forceinline pair<MoneyGetCharIterator, char *>
mismatch(MoneyGetCharIterator first, MoneyGetCharIterator last, char *text)
{
    while (first != last && *first == *text) {
        ++first;
        ++text;
    }
    return pair<MoneyGetCharIterator, char *>(first, text);
}
template <> __declspec(dllimport) __forceinline pair<MoneyGetCharIterator, bool>
__get_string(MoneyGetCharIterator first, MoneyGetCharIterator last, char *text, char *end)
{
    pair<MoneyGetCharIterator, char *> result = mismatch(first, last, text);
    return make_pair(result.first, result.second == end);
}

// The helper's retail call reaches the wide-character mismatch body at 0x00012CA0.
template <> pair<MoneyGetWideIterator, const wchar_t *> mismatch(
    MoneyGetWideIterator, MoneyGetWideIterator, const wchar_t *);
}
template class _STL::money_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;
template _STL::pair<_STL::MoneyGetWideIterator, bool> _STL::__get_string(
    _STL::MoneyGetWideIterator, _STL::MoneyGetWideIterator, const wchar_t *, const wchar_t *);
namespace _STL {
template pair<MoneyGetCharIterator, bool> make_pair(const MoneyGetCharIterator &, const bool &);
template pair<MoneyGetCharIterator, char *>::pair(const MoneyGetCharIterator &, char *const &);
}
