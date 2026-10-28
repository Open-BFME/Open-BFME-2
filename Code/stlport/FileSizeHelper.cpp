// cl: /MD
// platformsdk
// STLport 4.5.3 Win32 file-size helper used by _Filebuf_base. Donor-verbatim
// logic from BFME1 Code/stlport/FileSizeHelper.cpp (b1 0x00849E80): reads the
// 64-bit size via GetFileSize, returns 0 when LowPart is -1 and GetLastError
// is nonzero, otherwise the truncated QuadPart. Kept as its own TU (not
// folded into stlport_filebuf_base.cpp's forceinline _File_size) because
// retail keeps it out of line at 0x0001D240.

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

long Rva00849E80FileSize(void *fd)
{
	LARGE_INTEGER size;
	size.LowPart = GetFileSize(fd, (unsigned long *)&size.HighPart);
	if (size.LowPart == (unsigned long)-1 && GetLastError() != 0)
		return 0;
	return (long)size.QuadPart;
}
