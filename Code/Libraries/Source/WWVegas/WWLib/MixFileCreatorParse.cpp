// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva00218E96Parse@@YAXPAVINI@@HPAU?$vector@UFileInfoStruct@MixFileCreator@@V?$allocator@UFileInfoStruct@MixFileCreator@@@_STL@@@_STL@@@_STL@@@Z @0x00218E96 300B
// INI-driven fill of a MixFileCreator::FileInfoStruct vector. Two leading
// integers (CRC, Offset) come from getNextToken/scanInt; following string
// tokens are style markers ("+bold" -> 1, "-bold" -> 2, "normal" -> 0) or the
// entry filename. The record is pushed only when the filename is non-empty.
// Callees all rowed: INI getNextToken/scanInt/getNextAsciiString, StringBase
// compareNoCase/set/releaseBuffer, vector push_back 0x00218DD2 (chain).
// Layout from MixFileCreatorFileInfoStructAssign (CRC Offset Size Filename).
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

class MixFileCreator
{
public:
	struct FileInfoStruct
	{
		unsigned long CRC;
		unsigned long Offset;
		unsigned long Size;
		AsciiString Filename;
	};
};

typedef MixFileCreator::FileInfoStruct FileInfoStruct;

class INI
{
public:
	const char *getNextToken(const char *delimiters);
	int scanInt(const char *token);
	AsciiString getNextAsciiString();
};

void Rva00218E96Parse(INI *ini, int unused, _STL::vector<FileInfoStruct> *out)
{
	int crc = ini->scanInt(ini->getNextToken(0));
	int offset = ini->scanInt(ini->getNextToken(0));
	FileInfoStruct info;
	info.CRC = (unsigned long)crc;
	info.Offset = (unsigned long)offset;
	info.Size = 0;
	AsciiString cur = ini->getNextAsciiString();
	for (;;)
	{
		if (cur.getLength() == 0)
			break;
		if (cur.compareNoCase("+bold") == 0)
			info.Size = 1;
		else if (cur.compareNoCase("-bold") == 0)
			info.Size = 2;
		else if (cur.compareNoCase("normal") == 0)
			info.Size = 0;
		else
			info.Filename.set(cur);
		cur.set(ini->getNextAsciiString());
	}
	if (info.Filename.getLength() > 0)
		out->push_back(info);
}
