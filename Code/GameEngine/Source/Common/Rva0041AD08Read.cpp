// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?embedPristineMap@@YAXVAsciiString@@PAVXfer@@@Z (WorldBuilder name), retail 0x0041AD08, 248 bytes.
// Evidence: unlock lane, callers at 0x0041B35F/0x0041B3CA in 0x0041AFDA, callee openFile 0x00600C34,
// _bfmeFormatText 0x0060C36E, new[] 0x0002FDE0, delete[] 0x0002FD80, releaseBuffer 0x00036410,
// EmptyString g_Rva0107301CEmptyString, TheFileSystem, PristineMap literal, guard throw info.
// Static with TU-local caller for private register convention (ctx in edi from entry, shape lever 462).
#include "ascii_string.h"

class File
{
public:
	virtual void f0();
	virtual void f1();
	virtual void close();
	virtual int read(void *buf, int size);
	virtual int write(const void *buf, int size);
	virtual int seek(int offset, int origin);
};

// The second parameter is the save game's Xfer, as in Zero Hour's and BFME 1's
// GameStateMap.cpp (static void embedPristineMap(AsciiString, Xfer *)); WB's
// twin asserts xfer.IsStoring(). Slots as the rowed BFME 2 Xfer views place
// them: beginBlock +0x14, endBlock +0x18, xferUser +0x24, xferUnsignedInt +0x78.
class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual int beginBlock(const char *name);
	virtual void endBlock();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *data, unsigned int size);
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void xferUnsignedInt(unsigned int *value);
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

static void __cdecl embedPristineMap(AsciiString path, Xfer *xfer)
{
	char *t = *(char **)(void *)&path;
	const char *name = t ? t + 8 : "";
	File *f = TheFileSystem->openFile(name, 0x41, 0);
	if (!f)
	{
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	unsigned int size = f->seek(0, 2);
	f->seek(0, 0);
	char *buf = new char[size];
	if (!buf)
	{
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	int got = f->read(buf, size);
	if (got != size)
	{
		delete[] buf;
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	f->close();
	xfer->beginBlock("PristineMap");
	xfer->xferUnsignedInt(&size);
	xfer->xferUser(buf, size);
	xfer->endBlock();
	delete[] buf;
}

// Native41AC98..41AD08 and WB132EDB0 replace a four-character map
// suffix with .wak, clearing the output if the remaining prefix is not positive.
// Retail DoXfer41AFDA passes its input reference in ECX and output on stack.
static void Rva0041AC98(const AsciiString &path,AsciiString &out) {
 int length=path.getLength()-4;
 if(length>0) { AsciiString prefix(path,0,length);prefix+=".wak";out=prefix; }
 else out="";
}

// ?Rva0041AD08Caller@@YAXVAsciiString@@PAVFile@@@Z present-unmatched (register key kept; the anchor takes the Xfer view)
void __cdecl Rva0041AD08Caller(AsciiString p, Xfer *c)
{
	// Existing source-only private-ABI driver; this is not a retail claim.
	AsciiString auxiliary;
	Rva0041AC98(p, auxiliary);
	embedPristineMap(p, c);
}

// ?embedInUseMap@@YAXVAsciiString@@PAVXfer@@@Z (WorldBuilder name), retail 0x0041AE00, 248 bytes:
// the same read for the "InUseMap" entry (callers 0x0041B3DA, 0x0041B435).
static void __cdecl embedInUseMap(AsciiString path, Xfer *xfer)
{
	char *t = *(char **)(void *)&path;
	const char *name = t ? t + 8 : "";
	File *f = TheFileSystem->openFile(name, 0x41, 0);
	if (!f)
	{
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	unsigned int size = f->seek(0, 2);
	f->seek(0, 0);
	char *buf = new char[size];
	if (!buf)
	{
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	int got = f->read(buf, size);
	if (got != size)
	{
		delete[] buf;
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 5, (const char *)0);
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	f->close();
	xfer->beginBlock("InUseMap");
	xfer->xferUnsignedInt(&size);
	xfer->xferUser(buf, size);
	xfer->endBlock();
	delete[] buf;
}

// ?Rva0041AE00Caller@@YAXVAsciiString@@PAVFile@@@Z present-unmatched (register key kept; the anchor takes the Xfer view)
void __cdecl Rva0041AE00Caller(AsciiString p, Xfer *c)
{
	embedInUseMap(p, c);
}

// Native41AEF8..41AFDA / WB132E990 (GameStateMap.cpp:179..204)
// establish extractAndSaveMap. The BFME1 donor at874e38488 has the same
// transfer/write purpose; BFME2 uses FileSystem rather than CRT file IO.
// Xfer remains in ESI at its two calls from DoXfer; File::write is slot+10.
static void __cdecl extractAndSaveMap(AsciiString path, Xfer *xfer)
{
 char *t=*(char **)(void *)&path;
 const char *name=t?t+8:"";
 File *f=TheFileSystem->openFile(name,0x4a,0);
 if(!f){BfmeFormattedText tmp;bfmeFormatText(&tmp,5,(const char*)0);
 _CxxThrowException(&tmp,(const _s__ThrowInfo*)&g_guardTargetTypeThrowInfo);__assume(0);}
 xfer->beginBlock("EmbeddedMap");
 unsigned int size;
 xfer->xferUnsignedInt(&size);
 char *buf=new char[size];
 if(!buf){BfmeFormattedText tmp;bfmeFormatText(&tmp,5,(const char*)0);
 _CxxThrowException(&tmp,(const _s__ThrowInfo*)&g_guardTargetTypeThrowInfo);__assume(0);}
 xfer->xferUser(buf,size);
 int got=f->write(buf,size);
 if(got!=size){delete[]buf;BfmeFormattedText tmp;bfmeFormatText(&tmp,5,(const char*)0);
 _CxxThrowException(&tmp,(const _s__ThrowInfo*)&g_guardTargetTypeThrowInfo);__assume(0);}
 f->close();xfer->endBlock();delete[]buf;
}
// ?Rva0041AEF8Caller@@YAXVAsciiString@@PAVXfer@@@Z present-unmatched
void Rva0041AEF8Caller(AsciiString path,Xfer*xfer){extractAndSaveMap(path,xfer);}
