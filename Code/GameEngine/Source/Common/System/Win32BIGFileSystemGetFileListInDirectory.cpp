// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// ?getFileListInDirectory@Win32BIGFileSystem@@UBEXABVAsciiString@@00AAV?$set@VAsciiString@@UBfmeStringNoCaseLess@@V?$allocator@VAsciiString@@@_STL@@@_STL@@_N@Z
// Retail 0x00603FF8..0x0060421C (548 bytes); slot 9 of the Win32BIGFileSystem
// vtable 0x00C7A94C (entry at 0x0087A970), WB
// Win32BIGFileSystem::getFileListInDirectory (Win32BIGFileSystem.cpp).
//
// BFME 2 lists files from its own directory index at +0x04 (directory name
// -> set of file names, both C strings) instead of Zero Hour's per-archive
// walk: a non-empty currentDirectory is a debug crash ("currentDirectory -
// not implemented"); the original directory and the search mask are copied
// and normalised (rowed 0x00605324); a directory matches exactly, or with
// subdirectory search as a prefix ending at a backslash; each of its files
// matching the mask (rowed wildcard 0x006053D7) is added to the list as
// "directoryile" (rowed makeAsciiString 0x002343DF and the narrow
// concatenation nodes 0x00109CFD / 0x00234CA6 of RegistryAsciiPath.cpp).
// Evidence: vtable slot, WB name, the debug literal, rowed callees, the
// imported strncmp and the rowed no-case AsciiString set insert 0x0002CA26
// (FilenameList). Debug expansion as in Rva0033BA46Finish.cpp.
#include <set>
// STLport4.5.3 iterator comparison is its node-pointer comparison.
// Spell that native comparison here so no competing operator copy is emitted.
#include <map>
#include <string.h>
#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &a, const AsciiString &b) const;
};
typedef _STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > FilenameList;
namespace _STL
{
template <> pair<FilenameList::iterator, bool> FilenameList::insert(const AsciiString &);
}

struct BfmeCStringLess
{
	bool operator()(const char *a, const char *b) const;
};
typedef _STL::set<const char *, BfmeCStringLess> BigFileNameSet;
typedef _STL::map<const char *, BigFileNameSet, BfmeCStringLess> BigDirectoryMap;

void Rva00605324(char *path);				// 0x00605324, path normaliser
bool Rva006053D7(const char *str, const char *pattern);	// 0x006053D7, wildcard match
AsciiString makeAsciiString(const char *text);		// 0x002343DF

// BFME 2's narrow concatenation nodes (RegistryAsciiPath.cpp).
struct AsciiStringRef
{
	const AsciiString *m_string;
};
struct AsciiStringRefWithChar : AsciiStringRef
{
	char m_char;
};
struct Rva000B3F84Pair
{
	const char *m_ptr;
	int m_len;
};
struct AsciiStringCharPlusText : AsciiStringRefWithChar
{
	operator AsciiString();					// 0x00234CA6
	Rva000B3F84Pair m_right;
};
inline AsciiStringRefWithChar operator+(const AsciiString &s, char c)
{
	AsciiStringRefWithChar r;
	r.m_string = &s;
	r.m_char = c;
	return r;
}
AsciiStringCharPlusText operator+(const AsciiStringRefWithChar &left, const char *text);	// 0x00109CFD

void _bfme_debugRecordCallsite(int kind);

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};
extern Debug *theDebug;

class Win32BIGFileSystem
{
public:
	virtual ~Win32BIGFileSystem();
	virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
	virtual void getFileListInDirectory(const AsciiString &currentDirectory, const AsciiString &originalDirectory,
		const AsciiString &searchName, FilenameList &filenameList, Bool searchSubdirectories) const;	// slot 9

private:
	BigDirectoryMap m_directories;	// +0x04
};

void Win32BIGFileSystem::getFileListInDirectory(const AsciiString &currentDirectory, const AsciiString &originalDirectory,
	const AsciiString &searchName, FilenameList &filenameList, Bool searchSubdirectories) const
{
	if (currentDirectory.getLength() > 0)
	{
		_bfme_debugRecordCallsite(1);
		theDebug->SkipNext();
		(theDebug->CrashBegin(0, 0, 0) << "currentDirectory - not implemented").CrashDone(1);
	}

	char directory[260];
	strcpy(directory, originalDirectory.str());
	Rva00605324(directory);
	char mask[260];
	strcpy(mask, searchName.str());
	Rva00605324(mask);

	Int directoryLength = -1;
	if (searchSubdirectories)
		directoryLength = strlen(directory);

	for (BigDirectoryMap::const_iterator it = m_directories.begin(); it._M_node != m_directories.end()._M_node; ++it)
	{
		Bool match;
		if (directoryLength >= 0)
		{
			match = strncmp(directory, (*it).first, directoryLength) == 0;
			if (match && strlen((*it).first) != directoryLength)
				match &= ((*it).first[directoryLength] == '\\');
		}
		else
		{
			match = strcmp(directory, (*it).first) == 0;
		}
		if (!match)
			continue;

		for (BigFileNameSet::const_iterator fit = (*it).second.begin(); fit._M_node != (*it).second.end()._M_node; ++fit)
		{
			if (Rva006053D7(*fit, mask))
			{
				AsciiString path = makeAsciiString((*it).first) + '\\' + *fit;
				filenameList.insert(path);
			}
		}
	}
}
