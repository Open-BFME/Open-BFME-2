// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// stlport
// ?__linear_insert@@YAXPAUQ3SortElem16@@0U1@UQ3SortCompare@@@Z @0x00217F0E 111B CHAIN attempt under pinned Q3 name but FileInfo bodies via ICF
// Evidence: caller Q3 insertion_sort at 0x002183BD with 0x1c cleanup; callees rowed FileInfo copy_backward 0x00217B93 assign 0x002174DF copy ctor 0x00217624 Insert 0x002176F1; cmp-first-dword plus copy_backward shift plus temp plus Insert matches S4 and Q3 donors.
#include "ascii_string.h"

class MixFileCreator
{
public:
	struct FileInfoStruct
	{
		FileInfoStruct(const FileInfoStruct &src);
		FileInfoStruct &operator=(const FileInfoStruct &src);
		unsigned long CRC;
		unsigned long Offset;
		unsigned long Size;
		AsciiString Filename;
	};
};

struct Q3SortElem16
{
	int m_a;
	int m_b;
	int m_c;
	AsciiString m_d;
};

struct Q3SortCompare
{
	void *m_state;
	bool operator()(const Q3SortElem16 &left, const Q3SortElem16 &right) const
	{
		return left.m_a < right.m_a;
	}
};

class BfmeRoomQR
{
public:
	BfmeRoomQR(const BfmeRoomQR &other);
	~BfmeRoomQR() throw() {}
	int m_bfmeHandleQR;
};

struct BfmeElemQR
{
	int m_bfmeAQR;
	int m_bfmeBQR;
	int m_bfmeCQR;
	BfmeRoomQR m_bfmeRoomQR;
};

void __cdecl bfmeDoQR(BfmeElemQR *slot, BfmeElemQR value, void *extra);

namespace _STL
{
	template <class _BidIt1, class _BidIt2>
	_BidIt2 copy_backward(_BidIt1 first, _BidIt1 last, _BidIt2 result);
}

void __cdecl __linear_insert(Q3SortElem16 *first, Q3SortElem16 *last, Q3SortElem16 val, Q3SortCompare comp)
{
	if (comp(val, *first)) {
		_STL::copy_backward((MixFileCreator::FileInfoStruct *)first, (MixFileCreator::FileInfoStruct *)last, (MixFileCreator::FileInfoStruct *)(last + 1));
		*(MixFileCreator::FileInfoStruct *)first = *(MixFileCreator::FileInfoStruct *)&val;
	} else {
		bfmeDoQR((BfmeElemQR *)last, *(BfmeElemQR *)&val, comp.m_state);
	}
}
