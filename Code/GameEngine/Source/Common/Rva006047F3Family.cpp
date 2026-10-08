// cl: /O1 /MD
int __cdecl BFME2Utf8ToWide(const char* src, int srclen, unsigned short* dst, int dstlen);
struct Win32LocalFileSystem {
  virtual void _v0();
  virtual void _v1();
  virtual int Virt8(unsigned short* buf, void* a2, void* a3);
  // Slots 3, 5, 6 and 10 of vtable 0x00C7A9A8 (installed by the ctor at
  // 0x00604A5F): each narrow-string virtual converts and forwards to its wide
  // neighbour, so they are virtuals of this class, not plain members.
  virtual int M7F3(const char* src, void* a2, int a3);
  virtual bool Virt10(unsigned short* buf);
  virtual bool M831(const char* src);
  virtual void getFileListInDirectory(const char* a1, const char* a2, const char* a3, const char* a4, void* a5, void* a6);
  virtual void _v7();
  virtual void _v8();
  virtual int Virt24(unsigned short* buf, void* a2);
  virtual int M948(const char* src, void* a2);
  virtual void _v11();
  virtual void _v12();
  virtual void _v13();
  virtual void _v14();
  virtual void Virt60(unsigned short* b0, unsigned short* b1, unsigned short* b2, unsigned short* b3, void* a5, void* a6);
};
int Win32LocalFileSystem::M7F3(const char* src, void* a2, int a3) {
  unsigned short buf[260];
  BFME2Utf8ToWide(src, -1, buf, 260);
  return Virt8(buf, a2, (void*)a3);
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
	Virt60(p0, b1, b2, b3, a5, a6);
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
extern "C" {
__declspec(dllimport) HANDLE __stdcall FindFirstFileW(const unsigned short *, WIN32_FIND_DATAW *);
__declspec(dllimport) BOOL __stdcall FindClose(HANDLE);
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
