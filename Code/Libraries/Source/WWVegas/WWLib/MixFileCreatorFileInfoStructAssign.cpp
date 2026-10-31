// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??4FileInfoStruct@MixFileCreator@@QAEAAU01@ABU01@@Z, retail 0x002174DF,
// 41 bytes.
//
// MixFileCreator's file-info record: three plain header words (CRC, data
// offset, data size) plus the entry name. The name member assigns through
// the AsciiString copy-assign fold at 0x366F0 (existing pin); the header
// words copy as plain dwords. Layout follows the Zero Hour reference
// (WWLib/mixfile.h: MixFileCreator::FileInfoStruct), whose implicit
// copy-assignment is this body's 94.6% donor (see reverse/zh_sweep/packets/
// 002174df.md). A sibling 41B body at 0x217624 is the same shape with the
// name copy-constructed instead of assigned (the copy constructor).

#include "ascii_string.h"


#include "MixFileCreatorFileInfo.h"
// ??0FileInfoStruct@MixFileCreator@@QAE@ABU01@@Z
MixFileCreator::FileInfoStruct::FileInfoStruct(const FileInfoStruct &src) :
	CRC(src.CRC),
	Offset(src.Offset),
	Size(src.Size),
	Filename(src.Filename)
{
}

// ??4FileInfoStruct@MixFileCreator@@QAEAAU01@ABU01@@Z
inline MixFileCreator::FileInfoStruct &MixFileCreator::FileInfoStruct::operator=(const FileInfoStruct &src)
{
	CRC = src.CRC;
	Offset = src.Offset;
	Size = src.Size;
	Filename = src.Filename;
	return *this;
}

void __cdecl Rva002176A6Swap(MixFileCreator::FileInfoStruct *lhs, MixFileCreator::FileInfoStruct *rhs)
{
	MixFileCreator::FileInfoStruct tmp(*lhs);
	*lhs = *rhs;
	*rhs = tmp;
}

MixFileCreator::FileInfoStruct *__cdecl Rva00217AB0Partition(
	MixFileCreator::FileInfoStruct *first,
	MixFileCreator::FileInfoStruct *last,
	MixFileCreator::FileInfoStruct pivot)
{
	for (;;)
	{
		while ((int)first->CRC < (int)pivot.CRC)
			++first;
		--last;
		while ((int)pivot.CRC < (int)last->CRC)
			--last;
		if (!(first < last))
			return first;
		Rva002176A6Swap(first, last);
		++first;
	}
}

void __cdecl Rva002176F1Insert(MixFileCreator::FileInfoStruct *last, MixFileCreator::FileInfoStruct value)
{
	MixFileCreator::FileInfoStruct *next = last;
	--next;
	while ((int)value.CRC < (int)next->CRC)
	{
		*last = *next;
		last = next;
		--next;
	}
	*last = value;
}
