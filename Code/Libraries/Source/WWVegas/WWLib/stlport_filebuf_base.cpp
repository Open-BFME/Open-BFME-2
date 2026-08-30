// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 _Filebuf_base, the Win32 half of basic_filebuf. The handle,
// the mapping handle, the open mode and the two open flags sit at 0, 4, 8,
// 0x0C and 0x0D, which is what every one of these bodies indexes.

extern "C" __declspec(dllimport) int __stdcall UnmapViewOfFile(const void *base);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);
extern "C" __declspec(dllimport) unsigned long __stdcall GetFileSize(
		void *handle, unsigned long *high);
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError(void);

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

struct _Large_integer
{
	unsigned long _M_low;
	unsigned long _M_high;
};

class _Filebuf_base
{
public:
	_Filebuf_base();

	long _M_file_size();
	void _M_unmap(void *base, long length);
	bool _M_close();

protected:
	void *_M_file_id;
	void *_M_view_id;
	int _M_openmode;
	bool _M_is_open;
	bool _M_should_close;

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

long _Filebuf_base::_M_file_size()
{
	_Large_integer size;

	size._M_low = GetFileSize(_M_file_id, &size._M_high);

	if (size._M_low == 0xFFFFFFFF && GetLastError() != 0)
		return 0;

	return size._M_low;
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

}
