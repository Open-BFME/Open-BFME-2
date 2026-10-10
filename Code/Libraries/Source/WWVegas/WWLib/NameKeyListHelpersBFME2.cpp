// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native 0x149002 parses NameKey values into a four-byte-element vector.
// Its 49-byte push and 179-byte overflow are full relocation twins of the
// existing ScienceType instantiations. This is a container fold, not evidence
// that the two application enums have the same meaning.
#include <vector>
enum NameKeyType { NAMEKEY_INVALID = 0 };
template void _STL::vector<NameKeyType>::push_back(const NameKeyType &);
template void _STL::vector<NameKeyType>::_M_insert_overflow(NameKeyType *,
    const NameKeyType &, const _STL::__false_type &, unsigned int, bool);
