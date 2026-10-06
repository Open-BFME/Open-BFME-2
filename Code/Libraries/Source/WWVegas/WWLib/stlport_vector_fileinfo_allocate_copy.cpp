// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Typed STLport vector helper.  The element identity is established by the
// worker at 0x000642AF, which copies MixFileCreator::FileInfoStruct through
// the matched copy constructor at 0x00063CBC -> 0x00217624.  The record is
// three dwords followed by an AsciiString, hence the proven 16-byte stride.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

#include "ascii_string.h"


class MixFileCreator
{
public:
    struct FileInfoStruct
    {
        FileInfoStruct();
        FileInfoStruct(const FileInfoStruct &src);
        FileInfoStruct &operator=(const FileInfoStruct &src);
        unsigned long CRC;
        unsigned long Offset;
        unsigned long Size;
        AsciiString Filename;
    };
};

template class _STL::vector<MixFileCreator::FileInfoStruct,
                            _STL::allocator<MixFileCreator::FileInfoStruct> >;
