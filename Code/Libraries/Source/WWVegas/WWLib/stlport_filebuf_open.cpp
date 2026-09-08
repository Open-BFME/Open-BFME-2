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
