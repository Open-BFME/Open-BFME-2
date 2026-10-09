// ?Rva0037D55EGet@@YA?AVUnicodeString@@XZ
// partial score=0.906091370558376 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// BANK TRIAL ONLY: expanded UnicodeString adds an inline triple constructor.
// Canonical headers remain unchanged. Native37D55E..37D6E8 is394B,WB F5B870.
// Existing pointer-returning providers retain their address-derived ABI names.
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

	__forceinline UnicodeString(const BFME2WideConcatTriple &that);
	static UnicodeString TheEmptyString;
};


struct Pair8 {Pair8(){} Pair8(int x,int y):a(x),b(y){} int a,b;};struct Triple12 {Triple12(){} int a,b,c;};
inline Triple12 Rva0037BA97Init(const Pair8 *src,int c){Triple12 tmp;tmp.a=src->a;tmp.b=src->b;tmp.c=c;return tmp;}
struct BFME2WideConcatTriple {const UnicodeString *a,*b,*c;operator StringBase<unsigned short>();};
__forceinline UnicodeString::UnicodeString(const BFME2WideConcatTriple &that)
 : StringBase<unsigned short>(const_cast<BFME2WideConcatTriple &>(that)) {}
__forceinline Pair8 makePair(const UnicodeString &x,const UnicodeString &y){Pair8 pair((int)&x,(int)&y);return pair;}
__forceinline const Pair8 *pairPtr(const Pair8 &p){return &p;}
__forceinline int widePtr(const UnicodeString &s){return (int)&s;}
UnicodeString Rva0037B9D4Get();UnicodeString Rva0037BA48Get();
class FileSystem;extern FileSystem *TheFileSystem;
class BFME2FileSystemFacade {public:bool doesWideFileExist(const unsigned short *);};
class GameTextInterface {public:
 virtual void v00();virtual void v04();virtual void v08();virtual void v0c();
 virtual void v10();virtual void v14();virtual void v18();virtual void v1c();
 virtual void v20();virtual void v24();virtual void v28();virtual void v2c();
 virtual void v30();virtual void v34();virtual void v38();
 virtual UnicodeString fetch(const char *,bool * =0);
};
extern GameTextInterface *TheGameText;
UnicodeString Rva0037D55EGet(){
 UnicodeString formatText((const unsigned short *)L"%d");
 if(TheGameText)formatText=TheGameText->fetch("GUI:DefaultReplayFileName");
 for(int i=1;i<99999999;++i){
  UnicodeString filename;filename.format(&formatText,i);
  UnicodeString filepath((const BFME2WideConcatTriple &)Rva0037BA97Init(pairPtr(makePair(Rva0037B9D4Get(),filename)),widePtr(Rva0037BA48Get())));
  if(!((BFME2FileSystemFacade *)TheFileSystem)->doesWideFileExist(filepath.str()))return filename;
 }
 return UnicodeString((const unsigned short *)L"0");
}
