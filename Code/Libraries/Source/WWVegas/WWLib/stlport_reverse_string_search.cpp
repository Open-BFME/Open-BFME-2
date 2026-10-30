// cl: /DNDEBUG /MD /EHsc /Od /Ob2 /D_STLP_USE_STATIC_LIB
// stlport46
// STLport 4.6 (retail's linked release); first reconstructed from the STLport
// 4.5.3 BFME1 donor revision 1281192f682.
// Native 0x00028200..0x000284CB: reverse-iterator find_if with a
// not-within-char-range predicate. Its four-way unroll, reverse steps,
// predicate calls to 0x00026C60 and returned iterator establish the identity.
// The char find_if the predicate calls is the 34B provider at 0x00026C60
// (BfmeTwoHundredFiftySeven_FindByte.cpp); it is declared extern below so this
// /Ob2 unit emits no second copy.
/*
 *
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#include <string>
extern template const char *_STL::find_if(const char *, const char *,
	_STL::_Eq_char_bound<_STL::char_traits<char> >);
namespace _STL {
template reverse_iterator<const char *> __find_if(reverse_iterator<const char *>, reverse_iterator<const char *>, _Not_within_traits<char_traits<char> >, const random_access_iterator_tag &);
// Native 0x00029EE0/61B is the public find_if dispatch into the core above.
// Vendor reverse_iterator copy construction reproduces its outgoing slots;
// /Od /Ob2 retains the temporaries without inline assembly.
template reverse_iterator<const char *> find_if(reverse_iterator<const char *>, reverse_iterator<const char *>, _Not_within_traits<char_traits<char> >);
}

// Native0x0002A420/254B establishes find_last_not_of: three arguments,
// length/position bound, reverse predicate dispatch and npos fallback.
// Specialized from _string.c solely to emit this overloaded member reliably.
namespace _STL {
template<> unsigned int string::find_last_not_of(const char* __s, unsigned int __pos, unsigned int __n) const
{
  typedef char_traits<char>::char_type _CharType;
  const size_type __len = size();

  if (__len < 1)
    return npos;
  else {
    const_iterator __last = begin() + (min) (__len - 1, __pos) + 1;
    const_reverse_iterator __rlast = const_reverse_iterator(__last);
    const_reverse_iterator __rresult =
      find_if(__rlast, rend(),
			 _Not_within_traits<char_traits<char> >((const _CharType*)__s, 
						     (const _CharType*)__s + __n));
    return __rresult != rend() ? (__rresult.base() - 1) - begin() : npos;
  }
}

}

// Native 0x00027540/117B is the three-argument find: (pos + n) bound against
// size(), the needle searched in [begin + pos, end) and npos on a miss. The
// search it calls is native 0x00026C90/365B, the forward _Eq_traits search
// core; both reproduce exactly under this TU's /Od /Ob2 settings.
namespace _STL {
template string::size_type string::find(const char *, string::size_type, string::size_type) const;
}
