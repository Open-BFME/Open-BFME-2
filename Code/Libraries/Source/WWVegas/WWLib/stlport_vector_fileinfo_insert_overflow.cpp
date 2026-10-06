// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@UFileInfoStruct@MixFileCreator@@V?$allocator@UFileInfoStruct@MixFileCreator@@@_STL@@@_STL@@IAEXPAUFileInfoStruct@MixFileCreator@@ABU34@ABU__false_type@2@I_N@Z @0x00218B20 180B
// Vector<FileInfoStruct> fill-insert overflow (false_type path). Same 5-arg
// ret-0x14 shape as Coord3D overflow 0x002CDF8A; callers push_back 0x00218DD2;
// unblocks 0x00218DD2. Callees are the honest FileInfoStruct helpers rowed at
// 0x0021784A (copy) 0x0021781D (dup Construct) 0x00217870 (fill) 0x0021887C
// (destroy-free) plus the 16-byte allocator pin at 0x002226BE. The extra tag
// pushes match retail because the honest callees ignore the trailing tag word,
// called here through casts exactly like Rva0021784ACopy calls dup_0021781D.
// Layout from MixFileCreatorFileInfoStructAssign.cpp (CRC Offset Size Filename).
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

// Honest callees: declared with their ledger-row signatures, invoked through
// casts so the emitted pushes match retail (trailing __false_type tag word).
FileInfoStruct *Rva0021784ACopy(FileInfoStruct *first, FileInfoStruct *last, FileInfoStruct *result);
void __cdecl dup_0021781D();
FileInfoStruct *Rva00217870Fill(FileInfoStruct *first, unsigned int count, const FileInfoStruct &value);

typedef FileInfoStruct *(__cdecl *FileInfoCopyFn)(
	FileInfoStruct *, FileInfoStruct *, FileInfoStruct *, const _STL::__false_type &);
typedef void (__cdecl *FileInfoCtorFn)(FileInfoStruct *, const FileInfoStruct &);
typedef FileInfoStruct *(__cdecl *FileInfoFillFn)(
	FileInfoStruct *, unsigned int, const FileInfoStruct &, const _STL::__false_type &);

class Rva0021887C
{
public:
	void rva0021887C();
};

// Retail materialises the tag in the dead padding of __atend's argument slot
// ([ebp+0x1b]): a named __false_type local takes a frame slot instead and a
// __false_type() prvalue emits a zeroing store retail lacks. Spelling the tag
// as the padding byte keeps the 8-byte frame and the lea+push shape.
#define FILEINFO_TAG \
	*reinterpret_cast<const __false_type *>(reinterpret_cast<const char *>(&__atend) + 3)

namespace _STL
{
template <>
void vector<FileInfoStruct>::_M_insert_overflow(
	vector<FileInfoStruct>::pointer __position,
	const FileInfoStruct &__x,
	const __false_type &,
	vector<FileInfoStruct>::size_type __fill_len,
	bool __atend)
{
	typedef vector<FileInfoStruct> _Self;
	typedef _Self::pointer pointer;
	typedef _Self::size_type size_type;

	const size_type __old_size = _Self::size_type(this->_M_finish - this->_M_start);
	const size_type __len = __old_size + (max)(__old_size, __fill_len);

	pointer __new_start = this->_M_end_of_storage.allocate(__len);
	pointer __new_finish = __new_start;
	_STLP_TRY
	{
		__new_finish = ((FileInfoCopyFn)Rva0021784ACopy)(
			this->_M_start, __position, __new_start, FILEINFO_TAG);
		if (__fill_len == 1)
		{
			((FileInfoCtorFn)dup_0021781D)(__new_finish, __x);
			++__new_finish;
		}
		else
		{
			__new_finish = ((FileInfoFillFn)Rva00217870Fill)(
				__new_finish, __fill_len, __x, FILEINFO_TAG);
		}
		if (!__atend)
		{
			__new_finish = ((FileInfoCopyFn)Rva0021784ACopy)(
				__position, this->_M_finish, __new_finish, FILEINFO_TAG);
		}
	}
	_STLP_UNWIND((_Destroy(__new_start, __new_finish),
		this->_M_end_of_storage.deallocate(__new_start, __len)));
	reinterpret_cast<Rva0021887C *>(this)->rva0021887C();
	this->_M_start = __new_start;
	this->_M_finish = __new_finish;
	this->_M_end_of_storage._M_data = __new_start + __len;
}

template void vector<FileInfoStruct>::_M_insert_overflow(
	vector<FileInfoStruct>::pointer,
	const FileInfoStruct &,
	const __false_type &,
	vector<FileInfoStruct>::size_type,
	bool);
}
