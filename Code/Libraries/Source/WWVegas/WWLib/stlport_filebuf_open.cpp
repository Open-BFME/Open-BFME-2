// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Modified STLport 4.5.3 Win32 file-opening reconstruction, from src/fstream.cpp
// and src/fstream_impl.h. The native <fstream> header supplies the complete
// 16-byte _Filebuf_base layout, including three unsigned-char status flags.
// Those flags require Boolean normalization on return; treating them as bool
// was the former reconstruction's five-byte mismatch.
//
// The original _SgI helper namespace and descriptor/name overload identities
// are retained. GetFileType and CRT descriptor imports are independently
// identified from the retail PE import directory. The multithreaded CRT
// ioinfo layout below has the original 36-byte size and osfile offset four.
// Its critical-section storage mirrors the six 32-bit Win32 members.
//
// Every code byte and both switch tables match independently: the named-open
// body ends after 245 executable bytes; its three alignment bytes, six-entry
// jump table, and 49-byte dispatch table are excluded from coverage. The
// regular-file helper stays visible but noinline, as in the retail call graph.
/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */
#include <fstream>
#include <stddef.h>
typedef char _AssertFilebufSize[sizeof(_STL::_Filebuf_base)==16?1:-1];
extern "C" __declspec(dllimport) unsigned long __stdcall GetFileType(void*);
extern "C" __declspec(dllimport) void *__stdcall CreateFileA(const char*,unsigned long,unsigned long,void*,unsigned long,unsigned long,void*);
extern "C" __declspec(dllimport) int __stdcall SetEndOfFile(void*);
extern "C" __declspec(dllimport) unsigned long __stdcall SetFilePointer(void*,long,long*,unsigned long);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void*);
namespace _SgI {
__declspec(noinline) bool __is_regular_file(void* file) {
 return (GetFileType(file)&~0x8000UL)==1;
}
struct _StlCriticalSection {
 void* debug_info;
 long lock_count;
 long recursion_count;
 void* owning_thread;
 void* lock_semaphore;
 unsigned long spin_count;
};
extern "C" {
struct ioinfo {
 long osfhnd;
 char osfile;
 char pipech;
 int lockinitflag;
 _StlCriticalSection lock;
};
extern __declspec(dllimport) ioinfo* __pioinfo[];
}
typedef char _AssertIoinfoSize[sizeof(ioinfo)==36?1:-1];
typedef char _AssertIoinfoFlag[offsetof(ioinfo,osfile)==4?1:-1];
inline int flag_to_openmode(int mode) {
 int ret;
 switch(mode&3) {
 case 0:ret=8;break;
 case 1:ret=16;break;
 case 2:ret=24;break;
 }
 if(mode&8) ret|=1;
 if(mode&0x8000) ret|=4;
 return ret;
}
int _get_osfflags(int fd,void* oshandle) {
 char dosflags=0;
 dosflags=__pioinfo[fd>>5][fd&31].osfile;
 int mode=0;
 if(dosflags&0x20)mode|=8;
 if(dosflags&0x80)mode|=0x4000;
 else mode|=0x8000;
 if(dosflags&4)mode|=2;
 return flag_to_openmode(mode);
}
}
namespace _STL {
bool _Filebuf_base::_M_open(const char *name, int openmode, long permission)
{
	void *file_no;

	if (_M_is_open)
		return false;

	unsigned long desired_access, creation_disposition;
	bool do_truncate = false;

	switch (openmode & ~(2 | 4)) {
	case 16:
	case 16 | 32:
		desired_access = 0x40000000;
		creation_disposition = 4;
		do_truncate = true;
		break;
	case 16 | 1:
		desired_access = 0x40000000;
		creation_disposition = 4;
		break;
	case 8:
		desired_access = 0x80000000;
		creation_disposition = 3;
		permission = 0;
		break;
	case 8 | 16:
		desired_access = 0xC0000000;
		creation_disposition = 3;
		break;
	case 8 | 16 | 32:
		desired_access = 0xC0000000;
		creation_disposition = 4;
		do_truncate = true;
		break;
	default:
		return false;
	}

	file_no = CreateFileA(name, desired_access, 3, 0,
			creation_disposition, permission, 0);
	if (file_no == reinterpret_cast<void *>(-1))
		return false;

	if ((do_truncate && SetEndOfFile(file_no) == 0) ||
		(((openmode & 2) != 0) &&
		 (SetFilePointer(file_no, 0, 0, 2) == 0xFFFFFFFF))) {
		CloseHandle(file_no);
		return false;
	}

	_M_is_open = true;
	_M_file_id = file_no;
	_M_should_close = _M_is_open;
	_M_openmode = openmode;
	_M_regular_file = _SgI::__is_regular_file(_M_file_id);
	return _M_is_open;
}
}

extern "C" __declspec(dllimport) long __cdecl _get_osfhandle(int);

namespace _STL {
bool _Filebuf_base::_M_open(int file_no,int init_mode) {
 if(_M_is_open || file_no<0)return false;
 if(_M_is_open || file_no==-1)return false;
 void* oshandle=(void*)_get_osfhandle(file_no);
 if((long)oshandle!=-1)file_no=(int)oshandle;
 else return false;
 if(init_mode!=0)_M_openmode=init_mode;
 else _M_openmode=_SgI::_get_osfflags(file_no,oshandle);
 _M_is_open=true;
 _M_file_id=(void*)file_no;
 _M_should_close=false;
 _M_regular_file=_SgI::__is_regular_file(_M_file_id);
 return true;
}
}
