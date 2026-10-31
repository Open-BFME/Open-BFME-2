// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Typed STLport vector helper.  The element identity is established by the
// worker at 0x000642AF, which copies MixFileCreator::FileInfoStruct through
// the matched copy constructor at 0x00063CBC -> 0x00217624.  The record is
// three dwords followed by an AsciiString, hence the proven 16-byte stride.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

#include "ascii_string.h"


#include "MixFileCreatorFileInfo.h"
// operator= is rowed in stlport_vector_fileinfo_assign.cpp (/O1); this TU's
// default-flag copy would compete with it at link time.
template <> _STL::vector<MixFileCreator::FileInfoStruct,
                         _STL::allocator<MixFileCreator::FileInfoStruct> > &
_STL::vector<MixFileCreator::FileInfoStruct,
             _STL::allocator<MixFileCreator::FileInfoStruct> >::operator=(
    const _STL::vector<MixFileCreator::FileInfoStruct,
                       _STL::allocator<MixFileCreator::FileInfoStruct> > &);

// Overflow is owned by the byte-verified 0x00218B20 unit.
template <> void _STL::vector<MixFileCreator::FileInfoStruct>::_M_insert_overflow(
    MixFileCreator::FileInfoStruct *, const MixFileCreator::FileInfoStruct &,
    const _STL::__false_type &, unsigned int, bool);

// Emit the rowed helpers without unrelated vector methods from this flags set.
template MixFileCreator::FileInfoStruct *_STL::vector<MixFileCreator::FileInfoStruct>::_M_allocate_and_copy<MixFileCreator::FileInfoStruct *>(unsigned int, MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *);
template MixFileCreator::FileInfoStruct *_STL::__copy_backward<MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *, int>(MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *, const _STL::random_access_iterator_tag &, int *);
// Keep the existing dependency of the separately rowed copy_backward wrapper.
template MixFileCreator::FileInfoStruct *_STL::__copy_backward_ptrs<MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *>(MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *, const _STL::__false_type &);
