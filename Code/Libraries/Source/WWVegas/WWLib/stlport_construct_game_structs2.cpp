// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// Second batch of STLport _Construct<T> placement-copy helpers, same-shape
// siblings of the rowed _Construct<AsciiString> at 0x0002C485 (45 bytes; see
// stlport_construct_asciistring.cpp and stlport_construct_game_structs.cpp).
// Each body is the null-guarded placement-new copy over a single element: the
// copy delegates out-of-line to T's own rowed copy ctor, and __EH_prolog
// resolves via its matched row. Each T is declared minimally (declared-only
// copy ctor, matching the struct/class-ness of its rowed copy ctor); no member
// is ever touched, so the emitted code is identical apart from the callee.

#include <memory>

struct BfmeStringRecord004071F7
{
public:
	BfmeStringRecord004071F7(const BfmeStringRecord004071F7 &other);
};

struct BfmeStringRecord005F93E3
{
public:
	BfmeStringRecord005F93E3(const BfmeStringRecord005F93E3 &other);
};

struct BfmeRecordOwner900
{
public:
	BfmeRecordOwner900(const BfmeRecordOwner900 &other);
};

class MixFileCreator
{
public:
	struct FileInfoStruct
	{
	public:
		FileInfoStruct(const FileInfoStruct &other);
	};
};

template void _STL::_Construct<BfmeStringRecord004071F7, BfmeStringRecord004071F7>(BfmeStringRecord004071F7 *, const BfmeStringRecord004071F7 &);
template void _STL::_Construct<BfmeStringRecord005F93E3, BfmeStringRecord005F93E3>(BfmeStringRecord005F93E3 *, const BfmeStringRecord005F93E3 &);
template void _STL::_Construct<BfmeRecordOwner900, BfmeRecordOwner900>(BfmeRecordOwner900 *, const BfmeRecordOwner900 &);
template void _STL::_Construct<MixFileCreator::FileInfoStruct, MixFileCreator::FileInfoStruct>(MixFileCreator::FileInfoStruct *, const MixFileCreator::FileInfoStruct &);
