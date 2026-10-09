// ?copyCurrentRecordingToFile@RecorderClass@@QAE_NPAVUnicodeString@@0@Z
// partial score=0.968895800933126 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// BANK ONLY: the canonical UnicodeString view is expanded here with proposed
// inline concat assignment declarations. No canonical header was edited;
// adopt this API through the shared-header gate before moving this into Code. Candidate643B versus retail643B;
// local frame and temporary slots still differ; all instruction positions agree. Formal qualifiers
// remain an ABI view; WB independently establishes the method name.
// BFME1 9cbfb551 RecorderCopyReplayRva00099A40 supplies body sequence.
// Native37D6E8..37D96B643B; out-of-line success epilogue37D930 belongs
// to this body via branch37D901. WB F5BC90 named copyCurrentRecordingToFile.


// BFME2's shared UnicodeString: include this instead of declaring a TU-local
// `class UnicodeString` (2026-10-01: 217 TUs carried private copies in 145
// versions). Put /Ireference/shims/bfme2_ascii FIRST among a TU's /I flags so
// this header and the string_base.h beside it win over Open-BFME-1's.
//
// Zero Hour's UnicodeString made a StringBase<unsigned short> subclass, as the
// Open-BFME-1 WWLib header has it and as most private copies wrote it. Retail
// inlines the members everywhere: game.dat holds no call to the out-of-line
// copies of the copy and text constructors, the (unsigned short), (const
// unsigned short *, int) and (const unsigned short *, int, int) constructors,
// operator= or the other operator+= overloads; those are __forceinline here.
// operator+=(unsigned short) is a plain inline: retail calls its copy from 8
// sites and expands it in place elsewhere (LanguageFilter::unHaxor). The exports keep one copy of each alive, which
// WWLib/unicode_string.cpp emits as select-any COMDATs for the ledger rows.
// string_base.h's inline ~StringBase makes ~UnicodeString the bare
// `jmp releaseBuffer` retail has at 0x005B804E. The other members follow game.dat's exports (reverse/exports.csv):
// format(const unsigned short *, ...), format(const UnicodeString *, ...),
// translate(const AsciiString &), translate(const char *),
// UnicodeString(const AsciiString &). TheEmptyString is non-const, the spelling
// the tree converged on (c4cb0cd6ba).
#include "string_base.h"

class AsciiString;
struct BFME2WideConcatPair;struct BFME2WideConcatTriple;

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	__forceinline UnicodeString(const UnicodeString &that) : StringBase<unsigned short>(that) {}
	__forceinline UnicodeString(unsigned short c) : StringBase<unsigned short>(c) {}
	__forceinline UnicodeString(const unsigned short *s) : StringBase<unsigned short>(s) {}
	__forceinline UnicodeString(const unsigned short *s, int len) : StringBase<unsigned short>(s, len) {}
	__forceinline UnicodeString(const unsigned short *s, int start, int len) : StringBase<unsigned short>(s, start, len) {}
	UnicodeString(const UnicodeString &that, int start, int len) : StringBase<unsigned short>(that, start, len) {}
	UnicodeString(const AsciiString &that);
	~UnicodeString() {}

	__forceinline UnicodeString &operator=(const UnicodeString &that)
	{
		set(that);
		return *this;
	}
	__forceinline UnicodeString &operator=(unsigned short c)
	{
		unsigned short text = c;
		set(&text, 1);
		return *this;
	}
	__forceinline UnicodeString &operator=(const unsigned short *s)
	{
		set(s);
		return *this;
	}
	__forceinline UnicodeString &operator+=(const UnicodeString &that)
	{
		concat(that);
		return *this;
	}
	UnicodeString &operator+=(unsigned short c)
	{
		unsigned short text = c;
		concat(&text, 1);
		return *this;
	}
	__forceinline UnicodeString &operator+=(const unsigned short *s)
	{
		concat(s);
		return *this;
	}

	void __cdecl format(const unsigned short *fmt, ...);
	void __cdecl format(const UnicodeString *fmt, ...);
	void translate(const AsciiString &that);
	void translate(const char *that);

	__forceinline UnicodeString &operator=(const BFME2WideConcatPair &that);
	__forceinline UnicodeString &operator=(const BFME2WideConcatTriple &that);
	__forceinline UnicodeString &assignTriple(const UnicodeString &,const UnicodeString &,const UnicodeString &);
	static UnicodeString TheEmptyString;
};

struct _iobuf;typedef _iobuf FILE;
extern "C" __declspec(dllimport) FILE *__cdecl _wfopen(const unsigned short *,const unsigned short *);
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *,unsigned int,unsigned int,FILE *);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *,unsigned int,unsigned int,FILE *);
extern "C" __declspec(dllimport) int __cdecl fseek(FILE *,long,int);
extern "C" __declspec(dllimport) long __cdecl ftell(FILE *);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *);
extern "C" __declspec(dllimport) int __cdecl fwprintf(FILE *,const unsigned short *,...);
extern "C" __declspec(dllimport) unsigned short __cdecl fputwc(unsigned short,FILE *);
UnicodeString Rva0037B9D4Get();UnicodeString Rva0037BA48Get();UnicodeString Rva0037D55EGet();
struct Pair8 {int a,b;};struct Triple12{Triple12(){} int a,b,c;};
inline Triple12 Rva0037BA97Init(const Pair8 *src,int c){Triple12 tmp;tmp.a=src->a;tmp.b=src->b;tmp.c=c;return tmp;}
struct BFME2WideConcatPair{const UnicodeString *a,*b;operator StringBase<unsigned short>();};
struct BFME2WideConcatTriple{const UnicodeString *a,*b,*c;operator StringBase<unsigned short>();};
__forceinline UnicodeString &UnicodeString::operator=(const BFME2WideConcatPair &that){set(const_cast<BFME2WideConcatPair &>(that));return *this;}
__forceinline UnicodeString &UnicodeString::operator=(const BFME2WideConcatTriple &that){set(const_cast<BFME2WideConcatTriple &>(that));return *this;}
__forceinline BFME2WideConcatPair makePair(const UnicodeString &x,const UnicodeString &y){BFME2WideConcatPair p={&x,&y};return p;}
__forceinline UnicodeString &UnicodeString::assignTriple(const UnicodeString &x,const UnicodeString &y,const UnicodeString &z){
 Pair8 pair={(int)&x,(int)&y};
 set((BFME2WideConcatTriple &)Rva0037BA97Init(&pair,(int)&z));return *this;
}
class Rva0037BBED {public:UnicodeString rva0037BCA8();};
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;



class RecorderClass {public:
 bool copyCurrentRecordingToFile(UnicodeString *a,UnicodeString *b);
 void logGameEnd() throw();
private:char prefix00[0x10];FILE *m_file;
};
Bool RecorderClass::copyCurrentRecordingToFile(UnicodeString *a, UnicodeString *b)
{
	if (m_file == 0)
		return false;
	UnsignedInt fileSize = ftell(m_file);
	if (fileSize < 0x25)
		return false;

 UnicodeString path;
 if(!a->isEmpty()){
  path=makePair(Rva0037B9D4Get(),*a);
 }else path.assignTriple(Rva0037B9D4Get(),Rva0037D55EGet(),Rva0037BA48Get());
	FILE *out = _wfopen(path.str(), (const unsigned short *)L"wb");
	if (out == 0)
		return false;
	Int seekRes = fseek(m_file, 0, 0);
	char buf[0x10000];
	UnsignedInt got = fread(buf, 1, 0x25, m_file);
	UnsignedInt put = fwrite(buf, 1, 0x25, out);
	if (seekRes != 0 || got < 0x25 || put < 0x25)
		return false;
	// Skips the source title so the new one in b replaces it.
	UnicodeString title = ((Rva0037BBED *)this)->rva0037BCA8();
	fwprintf(out, L"%ws", (const unsigned short *)b->str());
	fputwc(0, out);
	while (true) {
		UnsignedInt n = fread(buf, 1, 0x10000, m_file);
		UnsignedInt w = fwrite(buf, 1, n, out);
        if (n == 0x10000 && w == n) continue;
        if (n != w) return false;
        break;
    }
		FILE *saved = m_file;
		m_file = out;
		logGameEnd();
		m_file = saved;
		fclose(out);
		fseek(m_file, fileSize, 0);
		return true;
}

