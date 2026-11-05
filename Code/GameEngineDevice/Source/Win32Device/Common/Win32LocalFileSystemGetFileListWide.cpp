// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// platformsdk
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
#include <windows.h>
#include <string.h>

namespace rts {
	template <class T> struct less_than_nocase {
		bool operator()(const T &a, const T &b) const { return a.compareNoCase(b) < 0; }
	};
	// Use the byte-verified comparator at 0x00037B40; /O1's local copy differs.
	template <> bool less_than_nocase<UnicodeString>::operator()(
		const UnicodeString &a, const UnicodeString &b) const;
}
// /O1 emits a non-retail standalone comparator. Preserve _M_find's calls
// and use the byte-verified external provider at 0x00037B40 instead of
// defining another compiler-shaped copy in this unit.
namespace rts {
	template <>
	bool less_than_nocase<UnicodeString>::operator()(const UnicodeString &a, const UnicodeString &b) const;
}
typedef std::set<UnicodeString, rts::less_than_nocase<UnicodeString> > UnicodeFilenameList;

// set::insert (0x00604E11) is rowed in stlport_unicode_string_set.cpp;
// declare its specialization so this unit calls it without emitting a
// second copy of the insert chain. (_M_find 0x00604D0E is a member template;
// declaring its specialization crashes MSVC 7.1, so its COMDAT stays.)
namespace _STL
{
template <> pair<UnicodeFilenameList::iterator, bool> UnicodeFilenameList::insert(const UnicodeString &__x);
}

class AsciiString;

// Slots 0-14 of vtable 0x00C7A9A8 (installed by the ctor at 0x00604A5F) come
// from the LocalFileSystem interface; slots 3, 5, 6 and 10 are the narrow-string
// virtuals that convert and forward to their wide neighbours. The wide
// getFileListInDirectory is Win32LocalFileSystem's own slot 15 (0x3C): it is a
// new virtual of the derived class, which is why it does not sit next to the
// narrow overload as two overloads introduced by one class would.
class File;

struct LocalFileSystem {
  virtual void _v0();
  virtual void _v1();
  virtual File* openFile(const unsigned short* filename, int access, void** seekPointer);
  virtual int M7F3(const char* src, void* a2, int a3);
  virtual bool Virt10(unsigned short* buf);
  virtual bool M831(const char* src);
  // MSVC lays overloaded virtuals out in reverse declaration order: this
  // UnicodeString form is slot 7, the narrow form slot 6.
  virtual void getFileListInDirectory(const UnicodeString &currentDirectory, const UnicodeString &originalDirectory,
    const UnicodeString &searchName, UnicodeFilenameList &filenameList, bool searchSubdirectories) const;
  virtual void getFileListInDirectory(const char* a1, const char* a2, const char* a3, const char* a4, void* a5, void* a6);
  virtual void rva00604A8B(const AsciiString &current,const AsciiString &original,const AsciiString &pattern,void *output,void *recurse);
  virtual int Virt24(unsigned short* buf, void* a2);
  virtual int M948(const char* src, void* a2);
  virtual bool createDirectory(const unsigned short* path);
  virtual bool rva006049D8(const char *src);
  virtual void _v13();
  virtual void _v14();
};

struct Win32LocalFileSystem : LocalFileSystem {
  virtual bool Virt10(unsigned short *buf);
  virtual bool rva006049D8(const char *src);
  virtual void rva00604A8B(const AsciiString &current,const AsciiString &original,const AsciiString &pattern,void *output,void *recurse);
  virtual File* openFile(const unsigned short* filename, int access, void** seekPointer);
  virtual int M7F3(const char* src, void* a2, int a3);
  virtual bool M831(const char* src);
  virtual void getFileListInDirectory(const char* a1, const char* a2, const char* a3, const char* a4, void* a5, void* a6);
  virtual int M948(const char* src, void* a2);
  virtual void getFileListInDirectory(const UnicodeString &currentDirectory, const UnicodeString &originalDirectory,
    const UnicodeString &searchName, UnicodeFilenameList &filenameList, bool searchSubdirectories) const;
  virtual void getFileListInDirectory(unsigned short* prefix, unsigned short* current, unsigned short* original, unsigned short* pattern, void* output, void* recurse);
};

void Win32LocalFileSystem::getFileListInDirectory(const UnicodeString &currentDirectory, const UnicodeString &originalDirectory,
	const UnicodeString &searchName, UnicodeFilenameList &filenameList, bool searchSubdirectories) const
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
