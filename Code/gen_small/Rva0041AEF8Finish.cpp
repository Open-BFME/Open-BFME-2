// ?Rva0041AEF8Read@@YAXVAsciiString@@PAVFile@@@Z
// partial score=0.97 date=2026-10-03
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?Rva0041AEF8Read@@YAXVAsciiString@@PAVFile@@@Z, retail 0x0041AEF8, 226 bytes.
// Evidence: unlock lane, callers at 0x0041B46F/0x0041B4B0 in 0x0041AFDA, callee openFile 0x00600C34,
// _bfmeFormatText 0x0060C36E, new[] 0x0002FDE0, delete[] 0x0002FD80, releaseBuffer 0x00036410,
// EmptyString g_Rva0107301CEmptyString, TheFileSystem, EmbeddedMap literal, guard throw info.
#include "ascii_string.h"

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
extern const char g_Rva0107301CEmptyString[];
extern int g_guardTargetTypeThrowInfo;

struct BfmeFormattedText
{
	char *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *result, int tag, const char *format, ...);
void __stdcall _CxxThrowException(void *a, void *b);
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *p);

// Static with a TU-local caller, for the private register convention the rowed
// sibling ?Rva0041AD08Read@@YAXVAsciiString@@PAVFile@@@Z (0x0041AD08, matched)
// uses: with a single non-static definition in the unit VC7 keeps the by-value
// AsciiString's pointer live in ecx across entry and reloads ctx from the frame
// late, pushing esi. Retail holds ctx in esi from the first use and pushes only
// ebx and edi. Giving the body internal linkage plus one TU-local caller is the
// shape lever that produced the sibling's match (lever 462).
static void __cdecl Rva0041AEF8Read(AsciiString path, File *ctx)
{
	char *t = *(char **)(void *)&path;
	const char *name = t ? t + 8 : g_Rva0107301CEmptyString;
	File *f = TheFileSystem->openFile(name, 0x4a, 0);
	if (!f)
	{
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, &g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	ctx->f_check("EmbeddedMap");
	int size;
	ctx->f_getsize(&size);
	char *buf = new char[size];
	if (!buf)
	{
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, &g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	ctx->f_read2(buf, size);
	int got = f->f_read(buf, size);
	if (got != size)
	{
		delete[] buf;
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, &g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	f->f2();
	ctx->f_close2();
	delete[] buf;
}

// ?Rva0041AEF8Caller@@YAXVAsciiString@@PAVFile@@@Z present-unmatched
void __cdecl Rva0041AEF8Caller(AsciiString p, File *c)
{
	Rva0041AEF8Read(p, c);
}
