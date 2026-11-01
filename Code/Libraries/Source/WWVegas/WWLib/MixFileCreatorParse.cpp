// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?parseFontSizeMapping@FontLibrary@@SAXPAVINI@@PAX1PBX@Z @0x00218E96 300B
// FontLibrary::parseFontSizeMapping: WorldBuilder's twin (GameFont.cpp,
// asserts 463 and 470 on subst.ReplacementFontName) has the same token loop
// and callees. The record is still viewed as MixFileCreator::FileInfoStruct
// (same 16-byte shape; its push_back row keeps that name). Two leading
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

#include "MixFileCreatorFileInfo.h"
typedef MixFileCreator::FileInfoStruct FileInfoStruct;

// Use the rowed push_back specialization at 0x00218DD2.
namespace _STL { template <> void vector<FileInfoStruct>::push_back(const FileInfoStruct &); }

class INI
{
public:
	const char *getNextToken(const char *delimiters);
	int scanInt(const char *token);
	AsciiString getNextAsciiString();
	AsciiString getNextQuotedAsciiString();
	void initFromINI(void *instance, const struct FieldParse *fields);
};

struct Rva00218FC2Record
{
	Rva00218FC2Record();
	Rva00218FC2Record(const Rva00218FC2Record &);
	~Rva00218FC2Record();
	Rva00218FC2Record &operator=(const Rva00218FC2Record &);
	char bytes[16];
	bool Less(const Rva00218FC2Record &) const;
};

struct Rva00218FC2RecordCompare
{
	bool operator()(const Rva00218FC2Record &a, const Rva00218FC2Record &b) const { return a.Less(b); }
};

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

#include "../../../../GameEngine/Include/Common/INI/FieldParse.h"

// 0x00218C2B (the font-size table lookup) is rowed as
// int Rva00218C2B::rva00218C2B(const AsciiString &) in
// CreateAHeroDataRva004080DD.cpp; its result is the table pointer.
class Rva00218C2B
{
public:
	int rva00218C2B(const AsciiString &key);
};

class FontLibrary
{
public:
	static void parseFontSizeMapping(INI *ini, void *instance, void *store, const void *userData);
};

extern FontLibrary *TheFontLibrary;

namespace _STL
{
template <class I, class C> void sort(I first, I last, C comp);
}
void FontLibrary::parseFontSizeMapping(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	_STL::vector<FileInfoStruct> *out = (_STL::vector<FileInfoStruct> *)store;
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
		if (((const StringBase<char> &)(cur)).compareNoCase("+bold") == 0)
			info.Size = 1;
		else if (((const StringBase<char> &)(cur)).compareNoCase("-bold") == 0)
			info.Size = 2;
		else if (((const StringBase<char> &)(cur)).compareNoCase("normal") == 0)
			info.Size = 0;
		else
			info.Filename.setCopyInline(cur);
		cur.setCopyInline(ini->getNextAsciiString());
	}
	if (info.Filename.getLength() > 0)
		out->push_back(info);
}

void parseFontSubstitutionDefinition(INI *ini)
{
	(void)&ini;
	AsciiString name = ini->getNextQuotedAsciiString();
	_STL::vector<Rva00218FC2Record> *table = (_STL::vector<Rva00218FC2Record> *)((Rva00218C2B *)TheFontLibrary)->rva00218C2B(name);
	FieldParse fields[2] = {{"Size", FontLibrary::parseFontSizeMapping, 0, 0}, {0, 0, 0, 0}};
	ini->initFromINI(table, fields);
	Rva00218FC2RecordCompare compare = {};
	_STL::sort(table->begin(), table->end(), compare);
}
