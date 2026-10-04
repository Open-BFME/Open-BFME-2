// cl: /DNDEBUG /MD /EHsc /Od /Ob2 /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3, BFME1 donor revision 1281192f682.
// Native 0x00028200..0x000284CB: reverse-iterator find_if with a
// not-within-char-range predicate. Its four-way unroll, reverse steps,
// predicate calls to 0x00026C60 and returned iterator establish the identity.
// The char find_if / __find_if instantiations independently reproduce the
// existing 34B/349B providers at 0x00026C60/0x00025B80.
#include <string>
namespace _STL {
template reverse_iterator<const char *> __find_if(reverse_iterator<const char *>, reverse_iterator<const char *>, _Not_within_traits<char_traits<char> >, const random_access_iterator_tag &);
// Native 0x00029EE0/61B is the public find_if dispatch into the core above.
// Vendor reverse_iterator copy construction reproduces its outgoing slots;
// /Od /Ob2 retains the temporaries without inline assembly.
template reverse_iterator<const char *> find_if(reverse_iterator<const char *>, reverse_iterator<const char *>, _Not_within_traits<char_traits<char> >);
}
