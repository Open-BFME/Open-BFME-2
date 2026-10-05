// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ?rva002DC267@Rva002DC267@@QBE?AVUnicodeString@@XZ @0x002DC267 (118B):
// Unicode save-directory builder. Ascii user-data path from GlobalData
// rva002360DE at 0x002360DE widens through UnicodeString ctor at 0x006CB6D0
// then concats wide L"Save\\" at 0x00C03F88 via StringBase concat at
// 0x00005692 and returns into the hidden pointer via wide copy at 0x00037050.
// Callers pass a stack temp and read the string out (0x002DC681 disk-space
// check via GetDiskFreeSpaceExW and 0x002DC7C1 startsWithNoCase and 0x002DC74A
// getFilePath helper plus 8 more unblocked). Neighbour pins place this in
// GameState save code (realMapPath at 0x002DC833). Honest-address name:
// owner unproven so class Rva002DC267. Donor shape is GameState
// getSaveDirectory in BFME1 GameState.cpp and BFME2 GameState.cpp.

extern class GlobalData *TheWritableGlobalData;

extern class FileSystem *TheFileSystem;

typedef int Int;
typedef unsigned short WideChar;

#define NULL 0

#include "ascii_string.h"


#include "unicode_string.h"

class GlobalData
{
public:
	AsciiString rva002360DE() const;
};

#define TheGlobalData TheWritableGlobalData

class Rva002DC267
{
public:
	UnicodeString rva002DC267() const;
};

class Rva002DC7C1
{
public:
	bool rva002DC7C1(const UnicodeString &path) const;
};

class Rva002DC74A
{
public:
	UnicodeString rva002DC74A(const UnicodeString &leaf) const;
};

class BFME2FileSystemFacade
{
public:
	bool doesWideFileExist(const WideChar *path);
};

#define TheFileSystem (*(BFME2FileSystemFacade **)&TheFileSystem)

class ArchiveFileSystem
{
public:
	virtual ~ArchiveFileSystem();
	virtual void A1();
	virtual void A2();
	virtual void A3();
	virtual bool A4(const WideChar *path);
};

extern ArchiveFileSystem *TheArchiveFileSystem;

class Rva002DCCFB
{
public:
	bool rva002DCCFB(UnicodeString filename);
};

UnicodeString Rva002DC267::rva002DC267() const
{
	UnicodeString wtmp(TheGlobalData->rva002360DE());
	wtmp.concat(L"Save\\");
	return wtmp;
}

// Unicode isInSaveDirectory: save dir from 0x002DC267 then
// StringBase startsWithNoCase at 0x000362B0. Callers pass a stack temp.
bool Rva002DC7C1::rva002DC7C1(const UnicodeString &path) const
{
	return ((const StringBase<WideChar> *)&path)->startsWithNoCase((const StringBase<WideChar> &)((const Rva002DC267 *)this)->rva002DC267());
}

// Unicode getFilePathInSaveDirectory: if leaf holds a backslash return it,
// else save dir from 0x002DC267 plus leaf via StringBase concat at 0x00006A2A.
UnicodeString Rva002DC74A::rva002DC74A(const UnicodeString &leaf) const
{
	if (((const StringBase<WideChar> *)&leaf)->find((WideChar)L'\\'))
		return leaf;
	UnicodeString tmp(((const Rva002DC267 *)this)->rva002DC267());
	((StringBase<WideChar> *)&tmp)->concat(*(const StringBase<WideChar> *)&leaf);
	return tmp;
}

// Unicode doesSaveGameExist: full path from 0x002DC74A then wide existence
// via facade doesWideFileExist pin at 0x0060068A. Filename by value.
bool Rva002DCCFB::rva002DCCFB(UnicodeString filename)
{
	UnicodeString filepath(((const Rva002DC74A *)this)->rva002DC74A((const UnicodeString &)filename));
	bool result = TheFileSystem->doesWideFileExist(filepath.str());
	return result;
}

// ?Rva002DC802BaseName@@YG?AVAsciiString@@ABV1@@Z @0x002DC802 49B:
// Ascii basename: reverseFind '\\' at 0x00035930 then AsciiString from
// substring at 0x00037BA0 or copy at 0x000365F0 into hidden return buffer.
// Caller 0x00356E8E forwards map path at ebp+8 with temp at ebp-0x14 then
// translates via UnicodeString at 0x006CB6A0. Honest-address free function.
// Ret 8 proves __stdcall.
AsciiString __stdcall Rva002DC802BaseName(const AsciiString &in)
{
	const char *slash = ((const StringBase<char> &)in).reverseFind('\\');
	if (slash)
		return AsciiString(slash + 1);
	return in;
}

// ?doesWideFileExist@BFME2FileSystemFacade@@QAE_NPBG@Z @0x0060068A 11B
// Facade ignores this and forwards wide path via TheArchiveFileSystem
// (VA 0x00A06E5C, mangled ?TheArchiveFileSystem@@3PAVArchiveFileSystem@@A)
// slot 0x10 (A4); retail override at 0x00604873 does _waccess(path,0)==0.
// Evidence: sole E8 caller rva002DCCFB at 0x002DCD34 in this TU plus
// parseMod/cmdline callers, ret 4, tail jmp via vtable under /O1.
__declspec(noinline) bool BFME2FileSystemFacade::doesWideFileExist(const WideChar *path)
{
	return TheArchiveFileSystem->A4(path);
}
