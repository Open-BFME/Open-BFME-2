// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$copy_backward@PAUFileInfoStruct@MixFileCreator@@PAU12@@_STL@@YAPAUFileInfoStruct@MixFileCreator@@PAU12@00@Z @0x00217B93 27B
// STL 3-arg copy_backward wrapper forwarding to rowed __copy_backward_ptrs at 0x002177B0
// with false_type temp at ebp-1. Evidence: ebp frame plus push ecx plus lea eax ebp-1
// plus 3 ptr args plus call 0x002177B0 plus add esp 0x10; caller at 0x00217F30.
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

namespace _STL
{
	struct __false_type {};
	template <class _BidIt1, class _BidIt2>
	_BidIt2 __copy_backward_ptrs(_BidIt1 first, _BidIt1 last, _BidIt2 result, const __false_type &);
	template <class _BidIt1, class _BidIt2>
	_BidIt2 copy_backward(_BidIt1 first, _BidIt1 last, _BidIt2 result)
	{
		__false_type t;
		return __copy_backward_ptrs(first, last, result, t);
	}
}

template MixFileCreator::FileInfoStruct *_STL::copy_backward<MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *>(MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *);
