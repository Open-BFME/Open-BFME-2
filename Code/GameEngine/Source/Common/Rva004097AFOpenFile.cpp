// cl: /O1 /Ireference/shims/bfme2_ascii /EHs /MD
// _Rva004097AFWorker, retail 0x004097AF (227B): the shared worker of the two
// tagged wrappers in Rva004097AFWrappers.cpp (callee(a, b, 0x4A, b) and
// callee(a, b, 0x41, 0)). It opens a file by name in one of two places:
//  - not system: the Unicode save-directory path TheGameState builds
//    (0x002DC74A, rowed as Rva002DC74A) opened through the wide
//    FileSystem::rva00600676;
//  - system: "Data\SystemHeroes\" + name (VA 0x00BE62B4), optionally first
//    opened for edit in Perforce by 0x004096E6 (NULL when that fails), then
//    FileSystem::openFile.
// The access argument is passed through; TheFileSystem is VA 0x00E06A48.
// The wrappers keep calling the C-linkage name pinned for this address, so the
// body keeps it; parameter roles are target facts, the original name is not.
#include "ascii_string.h"
#include "unicode_string.h"

typedef unsigned short WideChar;

class File;

class FileSystem
{
public:
	File *rva00600676(const WideChar *name, int access, int bufferSize);
	File *openFile(const char *name, int access, int bufferSize);
};
extern FileSystem *TheFileSystem;

class Rva002DC74A
{
public:
	UnicodeString rva002DC74A(const UnicodeString &src) const;
};

class GameState;
extern GameState *TheGameState;

bool Rva004096E6(const AsciiString &fileName);

// Retail inlines a str() that reads the buffer pointer directly (text at +8
// of the StringBase buffer header) and falls back on its own L"" literal
// (VA 0x00BBB5C4) rather than the shared header's TheNullChr; the shared
// header keeps that pointer private, so the accessor reads the one-pointer
// object layout.
static inline const WideChar *wideText(const UnicodeString &s)
{
	const char *buffer = *(const char *const *)&s;
	return buffer ? (const WideChar *)(buffer + 8) : (const WideChar *)L"";
}

extern "C" File *__cdecl Rva004097AFWorker(const AsciiString &name, bool systemFile, int access,
	bool checkOut)
{
	File *file = 0;

	if (!systemFile)
	{
		UnicodeString path = ((const Rva002DC74A *)TheGameState)->rva002DC74A(UnicodeString(name));
		file = TheFileSystem->rva00600676(wideText(path), access, 0);
	}
	else
	{
		AsciiString path("Data\\SystemHeroes\\");
		path += name;
		if (!checkOut || Rva004096E6(path))
			file = TheFileSystem->openFile(path.str(), access, 0);
	}

	return file;
}
