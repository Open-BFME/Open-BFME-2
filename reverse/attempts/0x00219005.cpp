// ?rva00219005@@YGXPAVINI@@@Z
// partial score=0.7 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00219005@@YGXPAVINI@@@Z @0x00219005 144B.
// Stdcall: reads a quoted name from the INI, looks up its record vector through
// the singleton registry (unrowed thiscall 0x00218C2B, pinned), sorts the
// vector with the matched Rva00218FC2 instance, and parses the block with a
// one-entry field table ("Size" -> Rva00218E96Parse) terminated by a zero entry.
// Evidence: target only; the names are address-derived and the registry
// global is address-named because the ledger has no name at 0x00DFE33C.
#include "ascii_string.h"
#include <vector>

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

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	AsciiString getNextQuotedAsciiString();
	void initFromINI(void *instance, const FieldParse *fields);
};

class Rva00219005Registry
{
public:
	_STL::vector<Rva00218FC2Record> *rva00218C2B(const AsciiString &name);
};

extern Rva00219005Registry *g_00DFE33C;

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

void Rva00218E96Parse(INI *ini, int unused, _STL::vector<MixFileCreator::FileInfoStruct> *out);

namespace _STL
{
template <class I, class C> void sort(I first, I last, C comp);
}

void __stdcall rva00219005(INI *ini)
{
	AsciiString name = ini->getNextQuotedAsciiString();
	_STL::vector<Rva00218FC2Record> *table = g_00DFE33C->rva00218C2B(name);
	Rva00218FC2RecordCompare compare;
	FieldParse fields[2] = {{"Size", (INIFieldParseProc)Rva00218E96Parse, 0, 0}, {0, 0, 0, 0}};
	ini->initFromINI(table, fields);
	_STL::sort(table->begin(), table->end(), compare);
}
