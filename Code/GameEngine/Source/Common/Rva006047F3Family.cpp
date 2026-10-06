// cl: /O1 /MD
int __cdecl BFME2Utf8ToWide(const char* src, int srclen, unsigned short* dst, int dstlen);
struct Rva00604xx {
  virtual void _v0();
  virtual void _v1();
  virtual int Virt8(unsigned short* buf, void* a2, void* a3);
  virtual void _v3();
  virtual bool Virt10(unsigned short* buf);
  virtual void _v5();
  virtual void _v6();
  virtual void _v7();
  virtual void _v8();
  virtual int Virt24(unsigned short* buf, void* a2);
  int M7F3(const char* src, void* a2, int a3);
  bool M831(const char* src);
  int M948(const char* src, void* a2);
};
int Rva00604xx::M7F3(const char* src, void* a2, int a3) {
  unsigned short buf[260];
  BFME2Utf8ToWide(src, -1, buf, 260);
  return Virt8(buf, a2, (void*)a3);
}
bool Rva00604xx::M831(const char* src) {
  if (!src) return false;
  unsigned short buf[260];
  BFME2Utf8ToWide(src, -1, buf, 260);
  return Virt10(buf);
}
int Rva00604xx::M948(const char* src, void* a2) {
  unsigned short buf[260];
  BFME2Utf8ToWide(src, -1, buf, 260);
  return Virt24(buf, a2);
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
