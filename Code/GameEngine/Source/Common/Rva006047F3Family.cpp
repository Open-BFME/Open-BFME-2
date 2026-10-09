// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/inputs/reference/shims/win32localfilesystem_wide /Ireference/open-bfme-1/inputs/reference/shims/asciistring_thin /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
#include <new>
#include <set>
#include "ascii_string.h"
#include "unicode_string.h"

struct BfmeStringNoCaseLess {
  bool operator()(const AsciiString&, const AsciiString&) const;
};
typedef std::set<AsciiString, BfmeStringNoCaseLess> FilenameList;

int __cdecl BFME2Utf8ToWide(const char* src, int srclen, unsigned short* dst, int dstlen);
int __cdecl BFME2WideToUtf8(const unsigned short* src, int srclen, char* dst, int dstlen);
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
  virtual void getFileListInDirectory(const char* a1, const char* a2, const char* a3, const char* a4, void* a5, void* a6);
  virtual void _v7();
  virtual void rva00604A8B(const AsciiString &current,const AsciiString &original,const AsciiString &pattern,void *output,void *recurse);
  virtual int Virt24(unsigned short* buf, void* a2);
  virtual int M948(const char* src, void* a2);
  virtual bool createDirectory(const unsigned short* path);
  virtual bool rva006049D8(const char *src);
  virtual void _v13();
  virtual void _v14();
};
struct Win32LocalFileSystem : LocalFileSystem {
  virtual bool rva006049D8(const char *src);
  virtual void rva00604A8B(const AsciiString &current,const AsciiString &original,const AsciiString &pattern,void *output,void *recurse);
  virtual File* openFile(const unsigned short* filename, int access, void** seekPointer);
  virtual int M7F3(const char* src, void* a2, int a3);
  virtual bool M831(const char* src);
  virtual void getFileListInDirectory(const char* a1, const char* a2, const char* a3, const char* a4, void* a5, void* a6);
  virtual int M948(const char* src, void* a2);
  virtual void getFileListInDirectory(unsigned short* prefix, unsigned short* current, unsigned short* original, unsigned short* pattern, void* output, void* recurse);
};
int Win32LocalFileSystem::M7F3(const char* src, void* a2, int a3) {
  unsigned short buf[260];
  BFME2Utf8ToWide(src, -1, buf, 260);
  return (int)openFile(buf, (int)a2, (void**)a3);
}
bool Win32LocalFileSystem::M831(const char* src) {
  if (!src) return false;
  unsigned short buf[260];
  BFME2Utf8ToWide(src, -1, buf, 260);
  return Virt10(buf);
}
int Win32LocalFileSystem::M948(const char* src, void* a2) {
  unsigned short buf[260];
  BFME2Utf8ToWide(src, -1, buf, 260);
  return Virt24(buf, a2);
}

// ?getFileListInDirectory@Win32LocalFileSystem@@UAEXPBD000PAX1@Z @0x00604895 179B.
// Four-string virtual, slot 6 of vtable 0x00C7A9A8 (neighbours M831): require
// a2-a4, optionally convert a1, convert a2-a4 via BFME2Utf8ToWide, then call
// the 0x3C virtual with the four wide buffers plus a5-a6.
void Win32LocalFileSystem::getFileListInDirectory(const char* a1, const char* a2, const char* a3, const char* a4, void* a5, void* a6)
{
	if (a2 == 0 || a3 == 0 || a4 == 0)
		return;
	unsigned short b0[260];
	unsigned short b1[260];
	unsigned short b2[260];
	unsigned short b3[260];
	unsigned short* p0 = 0;
	if (a1 != 0)
	{
		BFME2Utf8ToWide(a1, -1, b0, 260);
		p0 = b0;
	}
	BFME2Utf8ToWide(a2, -1, b1, 260);
	BFME2Utf8ToWide(a3, -1, b2, 260);
	BFME2Utf8ToWide(a4, -1, b3, 260);
	getFileListInDirectory(p0, b1, b2, b3, a5, a6);
}

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

struct EnumerationBuffers {
	char utf8Path[0x410];
	unsigned short subdirectoryPattern[260];
	unsigned short searchPath[260];
	unsigned short subdirectoryPath[260];
	unsigned short outputPath[260];
	WIN32_FIND_DATAW data;
};

extern "C" {
__declspec(dllimport) HANDLE __stdcall FindFirstFileW(const unsigned short *, WIN32_FIND_DATAW *);
__declspec(dllimport) BOOL __stdcall FindNextFileW(HANDLE, WIN32_FIND_DATAW *);
__declspec(dllimport) BOOL __stdcall FindClose(HANDLE);
__declspec(dllimport) unsigned short *__cdecl wcscpy(unsigned short *, const unsigned short *);
__declspec(dllimport) unsigned short *__cdecl wcscat(unsigned short *, const unsigned short *);
__declspec(dllimport) int __cdecl wcscmp(const unsigned short *, const unsigned short *);
}

// BFME1 donor: Win32LocalFileSystem::getFileListInDirectory in
// reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/
// GameEngineDevice/Source/Win32Device/Common/Win32LocalFileSystem.cpp at
// revision 6583b3c1ff21db4a561285717028fdafc780b7db. The donor enumerates
// matching files, suppresses dot entries, deduplicates in FilenameList, and
// recurses through subdirectories. BF2's 0x00604895 wrapper converts the four
// string arguments to wide buffers and dispatches slot 0x3c; this body is the
// slot implementation at 0x00604E34. The wide Win32 calls and BFME2WideToUtf8
// adapt the donor algorithm to the BF2 ABI. The set type and conversion helper
// are grounded by the existing BF2 helper rows at 0x0002C751, 0x0002CA26, and
// 0x002FB30; the identity also follows the neighbouring Win32LocalFileSystem
// methods and that wrapper-to-slot relationship, not from byte equality alone.
void Win32LocalFileSystem::getFileListInDirectory(unsigned short* prefix, unsigned short* current, unsigned short* original, unsigned short* pattern, void* output, void* recurse)
{
	EnumerationBuffers buffers;

	if (!current && !original && !pattern)
		return;

	wcscpy(buffers.searchPath, original);
	wcscat(buffers.searchPath, current);
	wcscat(buffers.searchPath, pattern);

	HANDLE handle = FindFirstFileW(buffers.searchPath, &buffers.data);
	bool done = (handle == INVALID_HANDLE_VALUE);
	while (!done) {
		if (!(buffers.data.dwFileAttributes & 0x10) &&
			wcscmp(buffers.data.cFileName, L".") &&
			wcscmp(buffers.data.cFileName, L"..")) {
			if (prefix)
				wcscpy(buffers.outputPath, prefix);
			else
				wcscpy(buffers.outputPath, original);
			wcscat(buffers.outputPath, current);
			wcscat(buffers.outputPath, buffers.data.cFileName);
			BFME2WideToUtf8(buffers.outputPath, -1, buffers.utf8Path, 0x410);
			AsciiString filename(buffers.utf8Path);
			FilenameList *filenameList = (FilenameList *)output;
			if (filenameList->find(filename) == filenameList->end())
				filenameList->insert(filename);
		}
		done = (FindNextFileW(handle, &buffers.data) == 0);
	}
	FindClose(handle);

	if (((unsigned char *)&recurse)[0]) {
		wcscpy(buffers.subdirectoryPattern, original);
		wcscat(buffers.subdirectoryPattern, current);
		wcscat(buffers.subdirectoryPattern, L"*.");
		handle = FindFirstFileW(buffers.subdirectoryPattern, &buffers.data);
		if (handle != INVALID_HANDLE_VALUE) {
			do {
				if ((buffers.data.dwFileAttributes & 0x10) &&
					wcscmp(buffers.data.cFileName, L".") &&
					wcscmp(buffers.data.cFileName, L"..")) {
					wcscpy(buffers.subdirectoryPath, current);
					wcscat(buffers.subdirectoryPath, buffers.data.cFileName);
					wcscat(buffers.subdirectoryPath, L"\\");
					getFileListInDirectory(prefix, buffers.subdirectoryPath, original, pattern, output, recurse);
				}
			} while (FindNextFileW(handle, &buffers.data));
		}
		FindClose(handle);
	}
}

struct Rva00604983Info
{
	unsigned int m_sizeHigh;
	unsigned int m_sizeLow;
	unsigned int m_timeHigh;
	unsigned int m_timeLow;
};

// ?Rva00604983Get@@YG_NPAGPAX@Z @0x00604983 85B.
// File-info fetch through table slot 0x0087A9CC (neighbours M948 Virt24 and
// rva00604A1E): FindFirstFileW on the wide path, copy write-time and size
// into the out info, FindClose, return true; false when the handle is invalid.
bool __stdcall Rva00604983Get(unsigned short *path, void *outParam)
{
	WIN32_FIND_DATAW data;
	HANDLE h = FindFirstFileW(path, &data);
	if (h == INVALID_HANDLE_VALUE)
		return false;
	Rva00604983Info *out = (Rva00604983Info *)outParam;
	out->m_timeHigh = data.ftLastWriteTime.dwHighDateTime;
	out->m_timeLow = data.ftLastWriteTime.dwLowDateTime;
	out->m_sizeHigh = data.nFileSizeHigh;
	out->m_sizeLow = data.nFileSizeLow;
	FindClose(h);
	return true;
}

// BFME1 donor: Win32LocalFileSystem::openFile in
// reference/open-bfme-1/game/GameEngineDevice/Source/Win32Device/Common/
// Win32LocalFileSystemOpenFileWide.cpp at donor revision
// 6583b3c1ff21db4a561285717028fdafc780b7db. The donor checks the path, creates
// parent directories for WRITE, opens a LocalFile, deletes it on failure, and
// seeks on success. Target evidence identifies this body as Win32LocalFileSystem
// vtable slot 2: the ctor at 0x00604A5F installs vtable 0x0087A9A8; slot 2 is
// 0x00604AD3 and adjacent slots contain the matched filesystem wrappers. Its
// direct callees and virtual slots establish the LocalFile allocation/open,
// close/delete, seek, and slot-11 CreateDirectoryW path. BFME2 target-specific
// changes are the UTF-16 path and StringBase<unsigned short> temporaries, plus
// the three-argument access/seek ABI; the established UnicodeString header
// supplies the target StringBase layout and TheNullChr used by str().
// Slot zero is represented by its retail scalar-deleting-dtor ABI, not a
// destructor expression: 0x00605C75 receives flag 0 and returns the pointer
// that 0x00604AD3 passes to operator delete.
class File
{
public:
  enum { WRITE = 2, CURRENT = 1 };
  virtual void* _v0DeletingDtor(unsigned int flags);
  virtual bool open(const char* filename, int access);
  virtual void close();
  virtual int read(void* buffer, int bytes);
  virtual int write(const void* buffer, int bytes);
  virtual int seek(int bytes, int mode);
  virtual void nextLine(char* buffer, int size);
  virtual bool scanInt(int& value);
  virtual bool scanReal(float& value);
  virtual bool scanString(AsciiString& value);
  virtual bool print(const char* format, ...);
  virtual int size();
  virtual int position();
  virtual char* readEntireAndClose();
  virtual File* convertToRAMFile();
  virtual void lock();
  virtual void unlock();

  void deleteOnClose() { m_deleteOnClose = true; }

protected:
  void* m_nameData;
  int m_access;
  bool m_open;
  bool m_deleteOnClose;
  unsigned short m_bfmePadding;
  int m_mutex;
};

class Rva00605C91 : public File
{
public:
  Rva00605C91();
  virtual bool open(const char* filename, int access);
  virtual void close();
  virtual int read(void* buffer, int bytes);
  virtual int write(const void* buffer, int bytes);
  virtual int seek(int bytes, int mode);
  virtual void nextLine(char* buffer, int size);
  virtual bool scanInt(int& value);
  virtual bool scanReal(float& value);
  virtual bool scanString(AsciiString& value);
  virtual char* readEntireAndClose();
  virtual File* convertToRAMFile();
  virtual bool openWide(const unsigned short* filename, int access);

protected:
  int m_handle;
};

class Rva00605C6A : public Rva00605C91
{
public:
  Rva00605C6A();
};

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const unsigned short* text);

// Target boundary 0x00604AD3..0x00604C5F (388 bytes).
File* Win32LocalFileSystem::openFile(const unsigned short* filename, int access, void** seekPointer)
{
  void* seekTo = 0;
  if (seekPointer)
    seekTo = *seekPointer;
  if (wcslen(filename) <= 0)
    return 0;

  Rva00605C6A* file = new Rva00605C6A;
  if (access & File::WRITE) {
    UnicodeString string;
    string = filename;
    UnicodeString token;
    UnicodeString dirName;
    string.nextToken(&token, L"\\/");
    dirName = token;
    while ((token.find(L'.') == 0) || (string.find(L'.') != 0)) {
      createDirectory(dirName.str());
      string.nextToken(&token, L"\\/");
      unsigned short slash = L'\\';
      dirName.concat(&slash, 1);
      dirName.concat(token);
    }
  }

  if (!file->openWide(filename, access)) {
    file->close();
    ::operator delete(file->_v0DeletingDtor(0));
    file = 0;
  } else {
    file->deleteOnClose();
    if (seekTo != 0)
      file->seek((int)seekTo, File::CURRENT);
  }
  return file;
}

bool Win32LocalFileSystem::rva006049D8(const char *src)
{
 unsigned short buffer[260];
 if(!src || !*src) return false;
 BFME2Utf8ToWide(src,-1,buffer,260);
 return createDirectory(buffer);
}
void Win32LocalFileSystem::rva00604A8B(const AsciiString &current,const AsciiString &original,const AsciiString &pattern,void *output,void *recurse)
{
 const char *p=pattern.str();
 const char *o=original.str();
 const char *c=current.str();
 getFileListInDirectory(0,c,o,p,output,recurse);
}

// Native Win32LocalFileSystem vtable C7A9A8 slots8/12 own these bodies.
// The existing narrow and wide overloads establish forwarding signatures;
// the three-string wrapper retains opaque output and recurse argument types.
// WB16510E0 confirms the three AsciiString reads in reverse order.
