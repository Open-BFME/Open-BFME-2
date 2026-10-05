// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@UFileInfoStruct@MixFileCreator@@V?$allocator@UFileInfoStruct@MixFileCreator@@@_STL@@@_STL@@QAEXABUFileInfoStruct@MixFileCreator@@@Z @0x00218DD2 55B
// STLport vector<MixFileCreator::FileInfoStruct>::push_back. Fast path calls
// the rowed dup _Construct at 0x0021781D; growth path calls the rowed
// _M_insert_overflow at 0x00218B20 with n=1 fill=1. Layout from
// MixFileCreatorFileInfoStructAssign and stlport_vector_fileinfo_allocate_copy
// (CRC Offset Size Filename, 16-byte stride). Chain from 0x00218B20;
// unblocks 0x00218E96.
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

typedef MixFileCreator::FileInfoStruct FileInfoStruct;

void __cdecl dup_0021781D();

typedef void (__cdecl *FileInfoCtorFn)(FileInfoStruct *, const FileInfoStruct &);

// Retail passes a __false_type prvalue as the tag; MSVC 7.1 /O1 materialises
// it in the dead padding of __x's argument slot ([ebp+0x0b]).
namespace _STL
{
template <>
void vector<FileInfoStruct>::push_back(const FileInfoStruct &__x)
{
	if (_M_finish != _M_end_of_storage._M_data)
	{
		((FileInfoCtorFn)dup_0021781D)(_M_finish, __x);
		++_M_finish;
	}
	else
	{
		this->_M_insert_overflow(_M_finish, __x, __false_type(), 1, true);
	}
}

template void vector<FileInfoStruct>::push_back(const FileInfoStruct &);
}
