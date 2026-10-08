// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?Rva0041AD08Read@@YAXVAsciiString@@PAVFile@@@Z, retail 0x0041AD08, 248 bytes.
// Evidence: unlock lane, callers at 0x0041B35F/0x0041B3CA in 0x0041AFDA, callee openFile 0x00600C34,
// _bfmeFormatText 0x0060C36E, new[] 0x0002FDE0, delete[] 0x0002FD80, releaseBuffer 0x00036410,
// EmptyString g_Rva0107301CEmptyString, TheFileSystem, PristineMap literal, guard throw info.
// Static with TU-local caller for private register convention (ctx in edi from entry, shape lever 462).
#include "ascii_string.h"

class OpenedFile
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f_close();
	virtual int f_read(void *buf, int size);
	virtual void f4();
	virtual int f_seek(int offset, int origin);
};

class File
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual int f_read(void *buf, int size);
	virtual void f_check(const char *key);
	virtual void f_close2();
	virtual void f7();
	virtual void f8();
	virtual void f_read2(void *buf, int size);
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void f26();
	virtual void f27();
	virtual void f28();
	virtual void f29();
	virtual void f_getsize(int *size);
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int unk);
};

extern FileSystem *TheFileSystem;
extern int g_guardTargetTypeThrowInfo;

struct BfmeFormattedText
{
	char *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *result, int tag, const char *format, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *p);

static void __cdecl Rva0041AD08Read(AsciiString path, File *ctx)
{
	char *t = *(char **)(void *)&path;
	const char *name = t ? t + 8 : "";
	OpenedFile *f = (OpenedFile *)TheFileSystem->openFile(name, 0x41, 0);
	if (!f)
	{
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	int size = f->f_seek(0, 2);
	f->f_seek(0, 0);
	char *buf = new char[size];
	if (!buf)
	{
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	int got = f->f_read(buf, size);
	if (got != size)
	{
		delete[] buf;
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	f->f_close();
	ctx->f_check("PristineMap");
	ctx->f_getsize(&size);
	ctx->f_read2(buf, size);
	ctx->f_close2();
	delete[] buf;
}

// ?Rva0041AD08Caller@@YAXVAsciiString@@PAVFile@@@Z present-unmatched
void __cdecl Rva0041AD08Caller(AsciiString p, File *c)
{
	Rva0041AD08Read(p, c);
}

// ?Rva0041AE00Read@@YAXVAsciiString@@PAVFile@@@Z, retail 0x0041AE00, 248 bytes:
// the same read for the "InUseMap" entry (callers 0x0041B3DA, 0x0041B435).
static void __cdecl Rva0041AE00Read(AsciiString path, File *ctx)
{
	char *t = *(char **)(void *)&path;
	const char *name = t ? t + 8 : "";
	OpenedFile *f = (OpenedFile *)TheFileSystem->openFile(name, 0x41, 0);
	if (!f)
	{
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	int size = f->f_seek(0, 2);
	f->f_seek(0, 0);
	char *buf = new char[size];
	if (!buf)
	{
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	int got = f->f_read(buf, size);
	if (got != size)
	{
		delete[] buf;
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	f->f_close();
	ctx->f_check("InUseMap");
	ctx->f_getsize(&size);
	ctx->f_read2(buf, size);
	ctx->f_close2();
	delete[] buf;
}

// ?Rva0041AE00Caller@@YAXVAsciiString@@PAVFile@@@Z present-unmatched
void __cdecl Rva0041AE00Caller(AsciiString p, File *c)
{
	Rva0041AE00Read(p, c);
}
