// ?Rva0037D96B@@YA_NABVUnicodeString@@00@Z
// partial score=0.8641456582633054 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// BANK TRIAL ONLY: canonical Unicode proposal expanded, shared headers untouched.
// Native37D96B..37DC36,715B. BF1 9cbfb551 RecorderCopyReplayFile semantic guide.
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
struct Pair8 {int a,b;};struct Triple12{int a,b,c;};
Triple12 Rva0037BA97Init(const Pair8 *,int);
struct BFME2WideConcatPair{const UnicodeString *a,*b;operator StringBase<unsigned short>();};
struct BFME2WideConcatTriple{const UnicodeString *a,*b,*c;operator StringBase<unsigned short>();};
__forceinline UnicodeString &UnicodeString::operator=(const BFME2WideConcatPair &that){set(const_cast<BFME2WideConcatPair &>(that));return *this;}
__forceinline UnicodeString &UnicodeString::operator=(const BFME2WideConcatTriple &that){set(const_cast<BFME2WideConcatTriple &>(that));return *this;}
__forceinline BFME2WideConcatPair makePair(const UnicodeString &x,const UnicodeString &y){BFME2WideConcatPair p={&x,&y};return p;}
__forceinline UnicodeString &UnicodeString::assignTriple(const UnicodeString &x,const UnicodeString &y,const UnicodeString &z){
 Pair8 pair={(int)&x,(int)&y};
 const BFME2WideConcatTriple &triple=(const BFME2WideConcatTriple &)Rva0037BA97Init(&pair,(int)&z);
 set(const_cast<BFME2WideConcatTriple &>(triple));return *this;
}

UnicodeString readUnicodeString(FILE *);
bool Rva0037D96B(const UnicodeString &src,const UnicodeString &dst,const UnicodeString &title)
{
 UnicodeString srcPath;
 if(src.find('\\'))srcPath=src;
 else {srcPath=Rva0037B9D4Get();srcPath+=src;}
 UnicodeString dstPath;
 if(!dst.isEmpty())dstPath=makePair(Rva0037B9D4Get(),dst);
 else dstPath.assignTriple(Rva0037B9D4Get(),Rva0037D55EGet(),Rva0037BA48Get());
 FILE *in=_wfopen(srcPath.str(),(const unsigned short *)L"rb");
 if(!in)return false;
 FILE *out=_wfopen(dstPath.str(),(const unsigned short *)L"wb");
 if(!out)return false;
 int seekRes=fseek(in,0,0);
 char buffer[0x10000];
 unsigned int got=fread(buffer,1,0x25,in);
 unsigned int put=fwrite(buffer,1,0x25,out);
 if(seekRes!=0||got<0x25||put<0x25)return false;
 UnicodeString oldTitle=readUnicodeString(in);
 fwprintf(out,L"%ws",title.str());fputwc(0,out);
 unsigned int n,w;
 do {n=fread(buffer,1,0x10000,in);w=fwrite(buffer,1,n,out);}while(n==0x10000&&w==n);
 if(n!=w)return false;
 fclose(in);fclose(out);return true;
}
