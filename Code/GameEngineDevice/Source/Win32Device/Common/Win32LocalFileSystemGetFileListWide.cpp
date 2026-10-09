// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
//
// Win32LocalFileSystem::getFileListInDirectory, retail 0x006050B9 (619
// bytes): slot 7 (+0x1C) of the Win32LocalFileSystem vftable 0x00C7A9A8,
// next to the narrow forwarder (slot 6, 0x00604895) and the wide buffer
// form (slot 15, 0x00604E34).  It is Zero Hour's
// Win32LocalFileSystem::getFileListInDirectory on UnicodeString paths: build
// originalDirectory+currentDirectory+searchName, FindFirstFileW over it,
// add every non-directory entry other than "." and ".." to the
// case-insensitive UnicodeString set unless already present (rowed
// _M_find 0x00604D0E / insert 0x00604E11), then, when asked, walk the
// "*." subdirectories and recurse through slot 7 with currentDirectory plus
// the directory name and '\\'.  WorldBuilder twin 0x01651B70 (order lead).
#include <set>
#include "unicode_string.h"

typedef unsigned long DWORD;
typedef int BOOL;
typedef void *HANDLE;
typedef struct _FILETIME { DWORD dwLowDateTime; DWORD dwHighDateTime; } FILETIME;
typedef struct _WIN32_FIND_DATAW
{
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	DWORD dwReserved0;
	DWORD dwReserved1;
	unsigned short cFileName[260];
	unsigned short cAlternateFileName[14];
} WIN32_FIND_DATAW;
#define INVALID_HANDLE_VALUE ((HANDLE)-1)
#define FILE_ATTRIBUTE_DIRECTORY 0x10

extern "C" {
__declspec(dllimport) HANDLE __stdcall FindFirstFileW(const unsigned short *, WIN32_FIND_DATAW *);
__declspec(dllimport) BOOL __stdcall FindNextFileW(HANDLE, WIN32_FIND_DATAW *);
__declspec(dllimport) BOOL __stdcall FindClose(HANDLE);
__declspec(dllimport) int __cdecl wcscmp(const unsigned short *, const unsigned short *);
}

namespace rts {
	template <class T> struct less_than_nocase {
		bool operator()(const T &a, const T &b) const { return a.compareNoCase(b) < 0; }
	};
}
typedef std::set<UnicodeString, rts::less_than_nocase<UnicodeString> > FilenameList;

// set::insert (0x00604E11) is rowed in stlport_unicode_string_set.cpp;
// declare its specialization so this unit calls it without emitting a
// second copy of the insert chain. (_M_find 0x00604D0E is a member template;
// declaring its specialization crashes MSVC 7.1, so its COMDAT stays.)
namespace _STL
{
template <> pair<FilenameList::iterator, bool> FilenameList::insert(const UnicodeString &__x);
}

class Win32LocalFileSystem
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void getFileListInDirectory(const UnicodeString &currentDirectory, const UnicodeString &originalDirectory,
		const UnicodeString &searchName, FilenameList &filenameList, bool searchSubdirectories) const;	// slot 7
};

void Win32LocalFileSystem::getFileListInDirectory(const UnicodeString &currentDirectory, const UnicodeString &originalDirectory,
	const UnicodeString &searchName, FilenameList &filenameList, bool searchSubdirectories) const
{
	HANDLE fileHandle = 0;
	WIN32_FIND_DATAW findData;

	UnicodeString asciisearch;
	asciisearch = originalDirectory;
	asciisearch.concat(currentDirectory);
	asciisearch.concat(searchName);

	bool done = false;

	fileHandle = FindFirstFileW(asciisearch.str(), &findData);
	done = (fileHandle == INVALID_HANDLE_VALUE);

	while (!done)
	{
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			(wcscmp(findData.cFileName, L".") && wcscmp(findData.cFileName, L"..")))
		{
			UnicodeString newFilename;
			newFilename = originalDirectory;
			newFilename.concat(currentDirectory);
			newFilename.concat(findData.cFileName);
			if (filenameList.find(newFilename) == filenameList.end())
				filenameList.insert(newFilename);
		}

		done = (FindNextFileW(fileHandle, &findData) == 0);
	}
	FindClose(fileHandle);

	if (searchSubdirectories)
	{
		UnicodeString subdirsearch;
		subdirsearch = originalDirectory;
		subdirsearch.concat(currentDirectory);
		subdirsearch.concat(L"*.");
		fileHandle = FindFirstFileW(subdirsearch.str(), &findData);
		done = fileHandle == INVALID_HANDLE_VALUE;

		while (!done)
		{
			if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				(wcscmp(findData.cFileName, L".") && wcscmp(findData.cFileName, L"..")))
			{
				UnicodeString tempsearchstr;
				tempsearchstr.concat(currentDirectory);
				tempsearchstr.concat(findData.cFileName);
				unsigned short slash = L'\\';
				tempsearchstr.concat(&slash, 1);

				getFileListInDirectory(tempsearchstr, originalDirectory, searchName, filenameList, searchSubdirectories);
			}

			done = (FindNextFileW(fileHandle, &findData) == 0);
		}

		FindClose(fileHandle);
	}
}
