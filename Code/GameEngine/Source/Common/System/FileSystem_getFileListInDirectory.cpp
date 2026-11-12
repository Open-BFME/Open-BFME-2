// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport
//
// FileSystem::getFileListInDirectory, retail 0x00600FC9 (676 bytes).
// Zero Hour FileSystem.cpp lists the local then the archive file system with
// AsciiString("") as the current directory. BFME2 (native 600FC9..60126D,
// WorldBuilder twin 0x016440E0, same statement order) first lists the
// preferred "%s\%s" root and "lang\%s\%s" language trees through the narrow
// listing slot when local files are preferred, then filters the result list
// through TheFilePathGate, erasing rejected names with files.erase(it++).
#include <set>
#include <stdio.h>
#include "ascii_string.h"

#include "../../../Include/Common/BfmeStringNoCaseLess.h"
typedef _STL::set<AsciiString, BfmeStringNoCaseLess> FilenameList;

// _Rb_tree::erase(iterator) is provided out of line (retail 0x00056BC3, the ICF
// fold with the less<AsciiString> erase; fold-pinned with its provider in
// MapCacheLoadUserMapsBFME2.cpp); this unit inlines ~AsciiString and would
// emit a non-retail copy.
namespace _STL {
template <> void _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, BfmeStringNoCaseLess,
	allocator<AsciiString> >::erase(iterator);
}

// Data-ledger names (provisional): 0x00E06E5C is TheArchiveFileSystem and
// 0x00E06E54 TheLocalFileSystem. The first is called through slots 6 and 8
// of the Win32LocalFileSystem vftable layout 0x00C7A9A8.
class ArchiveFileSystem
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual void slot5();
	virtual void getFileListInDirectory(const char *currentDirectory, const char *originalDirectory,
		const char *localDirectory, const char *searchName, FilenameList &filenameList, bool searchSubdirectories);	// slot 6
	virtual void slot7();
	// Rowed as Win32LocalFileSystem::rva00604A8B (slot 8, RET 0x14).
	virtual void rva00604A8B(const AsciiString &currentDirectory, const AsciiString &originalDirectory,
		const AsciiString &searchName, FilenameList &filenameList, bool searchSubdirectories);	// slot 8
};

class LocalFileSystem
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8();
	virtual void getFileListInDirectory(const AsciiString &currentDirectory, const AsciiString &originalDirectory,
		const AsciiString &searchName, FilenameList &filenameList, bool searchSubdirectories);	// slot 9
};

#include "../../../Include/GameClient/FilePathGate.h"

extern ArchiveFileSystem *TheArchiveFileSystem;
extern LocalFileSystem *TheLocalFileSystem;
extern bool BFME2PreferLocalFiles;
extern char TheLangDir[];
extern char g_00DD509C[];
extern FilePathGate *TheFilePathGate;

#include "../../../Include/Common/FileSystem.h"

// BFME2's AsciiString::str() is StringBase<char>::str(): an empty string reads
// StringBase's shared TheNullChr.
static inline const char *nameOf(const AsciiString &asciiString)
{
	return reinterpret_cast<const StringBase<char> *>(&asciiString)->str();
}

void FileSystem::getFileListInDirectory(const AsciiString &directory, const AsciiString &searchName,
	FilenameList &filenameList, bool searchSubdirectories) const
{
	char path[260];

	if (BFME2PreferLocalFiles)
	{
		if (TheLangDir[0])
		{
			sprintf(path, "%s\\%s", TheLangDir, nameOf(directory));
			const char *search = nameOf(searchName);
			const char *dir = nameOf(directory);
			TheArchiveFileSystem->getFileListInDirectory(dir, "", path, search, filenameList, searchSubdirectories);
		}
		if (g_00DD509C[0])
		{
			sprintf(path, "lang\\%s\\%s", g_00DD509C, nameOf(directory));
			const char *search = nameOf(searchName);
			const char *dir = nameOf(directory);
			TheArchiveFileSystem->getFileListInDirectory(dir, "", path, search, filenameList, searchSubdirectories);
		}
	}

	TheArchiveFileSystem->rva00604A8B(AsciiString(""), AsciiString(nameOf(directory)),
		AsciiString(nameOf(searchName)), filenameList, searchSubdirectories);
	TheLocalFileSystem->getFileListInDirectory(AsciiString(""), AsciiString(nameOf(directory)),
		AsciiString(nameOf(searchName)), filenameList, searchSubdirectories);

	if (TheFilePathGate)
	{
		FilenameList::iterator it = filenameList.begin();
		while (it != filenameList.end())
		{
			if (!TheFilePathGate->allow(nameOf(*it)))
				filenameList.erase(it++);
			else
				++it;
		}
	}
}
