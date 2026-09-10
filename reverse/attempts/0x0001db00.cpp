// ?_M_write@_Filebuf_base@_STL@@QAE_NPADH@Z
// partial score=0.99 date=2026-09-10
// cl: /O2 /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Dedicated TU for STLport _Filebuf_base::_M_write. Seek is defined here so
// the append path inlines the same way as the shared filebuf-base unit.

#include <stddef.h>

extern "C" __declspec(dllimport) int __stdcall WriteFile(
	void *handle, const void *buffer, unsigned long bytes,
	unsigned long *written, void *overlapped);
extern "C" __declspec(dllimport) unsigned long __stdcall SetFilePointer(
	void *handle, long low, long *high, unsigned long method);
extern "C" __declspec(dllimport) unsigned long __stdcall GetFileSize(
	void *handle, unsigned long *high);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError(void);
extern "C" __declspec(dllimport) void *__cdecl memchr(
	const void *buf, int value, size_t count);
extern "C" void *__cdecl memcpy(void *dst, const void *src, size_t count);

template <class T>
inline const T &(min)(const T &a, const T &b)
{
	return a < b ? a : b;
}

template <class T>
inline const T &(max)(const T &a, const T &b)
{
	return a > b ? a : b;
}

namespace _STL
{

union _Large_integer
{
	struct
	{
		unsigned long _M_low;
		long _M_high;
	} _M_parts;

	__int64 _M_quad;
};

class _Filebuf_base
{
public:
	bool _M_write(char *buf, ptrdiff_t n);
	long _M_seek(long offset, int direction);

protected:
	void *_M_file_id;
	void *_M_view_id;
	int _M_openmode;
	unsigned char _M_is_open;
	unsigned char _M_should_close;
	unsigned char _M_regular_file;

	static unsigned long _M_page_size;
};

__declspec(dllimport) __forceinline long __cdecl _File_size(void *handle)
{
	_Large_integer size;

	size._M_parts._M_low = GetFileSize(handle,
			reinterpret_cast<unsigned long *>(&size._M_parts._M_high));

	if (size._M_parts._M_low == 0xFFFFFFFF && GetLastError() != 0)
		return 0;

	return size._M_parts._M_low;
}

long _Filebuf_base::_M_seek(long offset, int direction)
{
	unsigned long method;

	switch (direction)
	{
	case 0x01:
		if (offset < 0)
			return -1;

		method = 0;
		break;

	case 0x02:
		method = 1;
		break;

	case 0x04:
		if (-offset > _File_size(_M_file_id))
			return -1;

		method = 2;
		break;

	default:
		return -1;
	}

	_Large_integer position;

	position._M_quad = offset;
	position._M_parts._M_low = SetFilePointer(_M_file_id,
			position._M_parts._M_low, &position._M_parts._M_high, method);

	if (position._M_parts._M_low == 0xFFFFFFFF && GetLastError() != 0)
		return -1;

	return position._M_parts._M_low;
}

bool _Filebuf_base::_M_write(char *buf, ptrdiff_t n)
{
	for (;;) {
		ptrdiff_t written;

		if (_M_openmode & 0x01)
			_M_seek(0, 0x04);

		if (_M_openmode & 0x04) {
			unsigned long NumberOfBytesWritten;
			WriteFile(_M_file_id, buf, (unsigned long)n, &NumberOfBytesWritten, 0);
			written = (ptrdiff_t)NumberOfBytesWritten;
		} else {
			char textbuf[4097];
			char *nextblock = buf;
			char *ptrtextbuf = textbuf;
			char *endtextbuf = textbuf + 4096;
			char *endblock = buf + n;
			ptrdiff_t nextblocksize = (min)((ptrdiff_t)4096, n);
			char *nextlf;

			while (nextblocksize > 0 &&
				(nextlf = (char *)memchr(nextblock, '\n', nextblocksize)) != 0) {
				ptrdiff_t linelength = nextlf - nextblock;
				memcpy(ptrtextbuf, nextblock, linelength);
				ptrtextbuf += linelength;
				nextblock += linelength + 1;
				*ptrtextbuf++ = '\r';
				*ptrtextbuf++ = '\n';
				nextblocksize = (min)(
					(max)((ptrdiff_t)(endtextbuf - ptrtextbuf), (ptrdiff_t)0),
					(ptrdiff_t)(endblock - nextblock));
			}

			if (nextblocksize > 0) {
				memcpy(ptrtextbuf, nextblock, nextblocksize);
				ptrtextbuf += nextblocksize;
				nextblock += nextblocksize;
			}

			char *writetextbuf = textbuf;
			for (unsigned long NumberOfBytesToWrite =
					(unsigned long)(ptrtextbuf - textbuf);
				NumberOfBytesToWrite != 0;) {
				unsigned long NumberOfBytesWritten;
				WriteFile(_M_file_id, writetextbuf, NumberOfBytesToWrite,
					&NumberOfBytesWritten, 0);
				if (NumberOfBytesWritten == NumberOfBytesToWrite)
					break;
				if (NumberOfBytesWritten == 0)
					return false;
				writetextbuf += NumberOfBytesWritten;
				NumberOfBytesToWrite -= NumberOfBytesWritten;
			}

			written = nextblock - buf;
		}

		if (n == written)
			return true;
		else if (written > 0 && written < n) {
			n -= written;
			buf += written;
		} else
			return false;
	}
}

}
