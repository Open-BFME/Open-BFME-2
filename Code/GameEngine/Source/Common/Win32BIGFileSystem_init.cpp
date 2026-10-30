// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// ?init@Win32BIGFileSystem@@UAEX_N@Z @0x00603944 188B: vslot 1 of vtable 0x0087A94C (class of ??0Win32BIGFileSystem@@QAE@XZ). Loads lang big files. Evidence: vtable slot 1; strings "%s*.big" "lang\" "lang\%sAudio.big" "EnglishAudio.big" "*.big" "apt\"; global TheArchiveFileSystem; buffers g_00DD509C g_Rva0107301CEmptyString.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdio.h>
#include <set>
#include <map>

class File;
class AsciiString;
struct BfmeStringNoCaseLess;
namespace _STL {
template <class T> class allocator;
template <class K, class C, class A> class set;
}

class ArchiveFileSystem
{
public:
	virtual ~ArchiveFileSystem();
	virtual void A1();
	virtual void A2();
	virtual File *openFile(const char *filename, int access, int unk);
	virtual void A4();
	virtual bool doesFileExist(const char *filename) const;
	virtual void getFiles(int x0, const char *a1, const char *empty, const char *a2, _STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > &out, int x5);
};

extern ArchiveFileSystem *TheArchiveFileSystem;
extern char g_00DD509C[];

struct BfmeCStringLess
{
	bool operator()(const char *a, const char *b) const;
};
typedef _STL::set<const char *, BfmeCStringLess> BigFileNameSet;
typedef _STL::map<const char *, BigFileNameSet, BfmeCStringLess> BigDirectoryMap;

class Win32BIGFileSystem
{
public:
	Win32BIGFileSystem();
	virtual ~Win32BIGFileSystem();
	virtual void init(bool flag);
	virtual void V2();
	virtual void V3();
	virtual void V4();
	virtual bool helper(const char *s, int extra);
	virtual void V6();
	virtual void V7();
	virtual bool rva006042B6(const char *path, const char *filter, int extra);
	virtual void getFileListInDirectory(const AsciiString &currentDirectory, const AsciiString &originalDirectory,
		const AsciiString &searchName, _STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > &filenameList, bool searchSubdirectories) const;	// slot 9

private:
	BigDirectoryMap m_directories;	// +0x04
};

void Win32BIGFileSystem::init(bool flag)
{
	char buf[0x104];

	if (TheArchiveFileSystem == 0)
		return;
	if (!flag)
		return;

	int (__cdecl *sprintfImp)(char *, const char *, ...);
	sprintfImp = sprintf;

	sprintfImp(buf, "%s*.big", g_00DD509C);
	rva006042B6("lang\\", buf, 1);

	sprintfImp(buf, "lang\\%sAudio.big", g_00DD509C);
	if (!TheArchiveFileSystem->doesFileExist(buf)) {
		rva006042B6("lang\\", "EnglishAudio.big", 0);
	}

	const char *pat = "*.big";
	rva006042B6("", pat, 0);
	rva006042B6("apt\\", pat, 0);
}
