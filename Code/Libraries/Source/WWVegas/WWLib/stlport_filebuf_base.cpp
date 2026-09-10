// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 _Filebuf_base, the Win32 half of basic_filebuf. The handle,
// the mapping handle, the open mode and the two open flags sit at 0, 4, 8,
// 0x0C and 0x0D, which is what every one of these bodies indexes.
// All three flags retain the original _fstream.h unsigned-char storage;
// their values are normalized only at Boolean interfaces.

#include <stddef.h>
#include <string.h>

extern "C" __declspec(dllimport) int __stdcall WriteFile(
	void *handle, const void *buffer, unsigned long bytes,
	unsigned long *written, void *overlapped);
extern "C" __declspec(dllimport) int __stdcall ReadFile(
	void *handle, void *buffer, unsigned long bytes,
	unsigned long *read, void *overlapped);
extern "C" __declspec(dllimport) unsigned long __stdcall SetFilePointer(
	void *handle, long low, long *high, unsigned long method);

extern "C" __declspec(dllimport) int __stdcall UnmapViewOfFile(const void *base);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);
extern "C" __declspec(dllimport) unsigned long __stdcall GetFileSize(
		void *handle, unsigned long *high);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError(void);
extern "C" __declspec(dllimport) unsigned long __stdcall SetFilePointer(
		void *handle, long low, long *high, unsigned long method);

struct _System_info
{
	unsigned long _M_oem_id;
	unsigned long _M_page_size;
	void *_M_minimum_application_address;
	void *_M_maximum_application_address;
	unsigned long *_M_active_processor_mask;
	unsigned long _M_number_of_processors;
	unsigned long _M_processor_type;
	unsigned long _M_allocation_granularity;
	unsigned short _M_processor_level;
	unsigned short _M_processor_revision;
};

extern "C" __declspec(dllimport) void __stdcall GetSystemInfo(
		_System_info *info);

namespace _STL
{

// _algobase.h's min and max: both return a reference to the chosen operand.
template <class _Tp>
inline const _Tp &(min)(const _Tp &__a, const _Tp &__b) { return __b < __a ? __b : __a; }
template <class _Tp>
inline const _Tp &(max)(const _Tp &__a, const _Tp &__b) { return  __a < __b ? __b : __a; }

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
	_Filebuf_base();

	long _M_file_size();
	long _M_seek(long offset, int direction);
	void _M_unmap(void *base, long length);
	bool _M_close();
	ptrdiff_t _M_read(char *buf, ptrdiff_t n);
	bool _M_write(char *buf, ptrdiff_t n);

protected:
	void *_M_file_id;
	void *_M_view_id;
	int _M_openmode;
	unsigned char _M_is_open;
	unsigned char _M_should_close;
	unsigned char _M_regular_file;

	static unsigned long _M_page_size;
};

unsigned long _Filebuf_base::_M_page_size;

_Filebuf_base::_Filebuf_base()
	: _M_file_id(reinterpret_cast<void *>(-1)), _M_openmode(0),
	  _M_is_open(false), _M_should_close(false)
{
	if (_M_page_size == 0)
	{
		_System_info info;

		GetSystemInfo(&info);
		_M_page_size = info._M_page_size;
	}

	_M_view_id = 0;

	if (!(_M_page_size > 0))
		_M_page_size = 0x1000;
}

__declspec(dllimport) __forceinline long __cdecl _File_size(void *handle)
{
	_Large_integer size;

	size._M_parts._M_low = GetFileSize(handle,
			reinterpret_cast<unsigned long *>(&size._M_parts._M_high));

	if (size._M_parts._M_low == 0xFFFFFFFF && GetLastError() != 0)
		return 0;

	return size._M_parts._M_low;
}

long _Filebuf_base::_M_file_size()
{
	return _File_size(_M_file_id);
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

void _Filebuf_base::_M_unmap(void *base, long)
{
	if (base != 0)
		UnmapViewOfFile(base);

	if (_M_view_id != 0)
		CloseHandle(_M_view_id);

	_M_view_id = 0;
}

bool _Filebuf_base::_M_close()
{
	if (!_M_is_open)
		return false;

	bool ok;

	if (!_M_should_close)
		ok = true;
	else if (_M_file_id != reinterpret_cast<void *>(-1))
		ok = CloseHandle(_M_file_id) != 0;
	else
		ok = false;

	_M_should_close = false;
	_M_is_open = false;
	_M_openmode = 0;

	return ok;
}

ptrdiff_t _Filebuf_base::_M_read(char *buf, ptrdiff_t n)
{
	unsigned long number_of_bytes_read;
	ReadFile(_M_file_id, (void *)buf, (unsigned long)n,
			&number_of_bytes_read, 0);

	if (!(_M_openmode & 4) && number_of_bytes_read) {
		char *to = buf;
		char *last = buf + number_of_bytes_read - 1;
		char *from;
		for (from = buf; from <= last && *from != 26; ++from) {
			if (*from != 13) {
				*to++ = *from;
			} else if (from < last) {
				if (*(from + 1) != 10)
					*to++ = 13;
			} else {
				char peek = ' ';
				unsigned long bytes_peeked;
				ReadFile(_M_file_id, (void *)&peek, 1, &bytes_peeked, 0);
				if (bytes_peeked) {
					if (peek != 10) {
						*to++ = 13;
						SetFilePointer(_M_file_id, -1, 0, 1);
					} else {
						SetFilePointer(_M_file_id, -2, 0, 1);
					}
				}
			}
		}
		if (from <= last)
			SetFilePointer(_M_file_id, (long)((last + 1) - from), 0, 1);
		number_of_bytes_read = (unsigned long)(to - buf);
	}
	return (ptrdiff_t)number_of_bytes_read;
}

// Open mode bits as this file reads them: 1 is ios_base::app and 4 is
// ios_base::binary; _M_seek's 4 is ios_base::end.  Text mode expands each LF
// to CR LF through a 4097-byte staging buffer and loops on short writes.
bool _Filebuf_base::_M_write(char *buf, ptrdiff_t n)
{
	for (;;) {
		ptrdiff_t written;

		if (_M_openmode & 1)
			_M_seek(0, 4);

		if (_M_openmode & 4) {
			unsigned long NumberOfBytesWritten;
			WriteFile(_M_file_id, buf, (unsigned long)n, &NumberOfBytesWritten, 0);
			written = (ptrdiff_t)NumberOfBytesWritten;
		}
		else {
			char textbuf[4097];
			char *nextblock = buf;
			char *ptrtextbuf = textbuf;
			char *endtextbuf = textbuf + 4096;
			char *endblock = buf + n;
			ptrdiff_t nextblocksize = (min)(n, (ptrdiff_t)4096);
			char *nextlf;

			while (nextblocksize > 0 &&
			       (nextlf = (char *)::memchr(nextblock, '\n', nextblocksize)) != 0) {
				ptrdiff_t linelength = nextlf - nextblock;
				memcpy(ptrtextbuf, nextblock, linelength);
				ptrtextbuf += linelength;
				nextblock += linelength + 1;
				*ptrtextbuf++ = '\r';
				*ptrtextbuf++ = '\n';
				nextblocksize = (min)((ptrdiff_t)(endblock - nextblock),
				                      (max)((ptrdiff_t)0,
				                            (ptrdiff_t)(endtextbuf - ptrtextbuf)));
			}

			if (nextblocksize > 0) {
				memcpy(ptrtextbuf, nextblock, nextblocksize);
				ptrtextbuf += nextblocksize;
				nextblock += nextblocksize;
			}

			char *writetextbuf = textbuf;
			for (unsigned long NumberOfBytesToWrite = (unsigned long)(ptrtextbuf - textbuf);
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
		}
		else
			return false;
	}
}

}
