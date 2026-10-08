// cl: /DNDEBUG /MD /EHsc
//
// One body carried from Open-BFME-1's game/Libraries/Source/Apt/string/
// EAString.cpp (BFME 1 RVA 0x0089EFE0), whose bytes reappear in game.dat at
// 0x006D5580 once relocation slots are set aside. Only this body is carried.

// Address-derived emission view. Original class and member identities unknown.
// Native wrapper: entry ECX, one stack byte, RET4; forwards callee EAX.
class Rva0089EFE0
{
public:
    int method(char value);
    // Native body at BFME 1 RVA 0x0089E2B0 (game.dat 0x006D47F0): ECX
    // receiver, two C strings, RET8, and an integral count in EAX.
    int rva0089E2B0(const char *first, const char *second);
};

int Rva0089EFE0::method(char value)
{
    char text[2] = "*";
    text[0] = value;
    return rva0089E2B0(text, "");
}

// EAStringC is established by the existing ChangeBuffer and SetSize providers.
// The assertion at retail 0x006D53F0 identifies this source and line 590.
// The formatting member name is unknown; keep its address-derived identity.
// Retail proves the shared representation pointer at +0, capacity at +4,
// character storage at +8 and cached hash at +6. The BFME 1 donor at
// ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f was reviewed for this family;
// this formatting body is reconstructed from BFME 2, not carried from it.
#include <stdarg.h>
extern "C" int __cdecl memcmp(const void *,const void *,unsigned int);
#pragma intrinsic(memcmp)
extern "C" unsigned int __cdecl strlen(const char *);
extern "C" int __cdecl _vsnprintf(char *,unsigned int,const char *,va_list);
extern "C" void __cdecl __debugbreak(void);
#pragma intrinsic(strlen,__debugbreak)
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class EAStringC {
    class StringDataC { public: unsigned short refCount,size,maxSize,hash; };
    StringDataC *data;
public:
    enum CBPushZero { CB_NO_PUSH_ZERO, CB_PUSH_ZERO };
private:
    void ChangeBuffer(unsigned int,unsigned int,unsigned int,CBPushZero,unsigned int);
public:
    void SetSize(int);
    static void FreeData(StringDataC *);
    EAStringC(const EAStringC &);
    EAStringC &operator=(const EAStringC &);
    ~EAStringC() { FreeData(data); }
    EAStringC Left(int) const;
    bool rva006D5DA0(const char *);
    __declspec(noinline) void rva006D53F0(const char *,va_list);
    void __cdecl rva006D62C0(const char *,...);

};
void EAStringC::rva006D53F0(const char *format,va_list args)
{
    if (!format) {
        g_bfmeAptAssertAtE17734("pStrFormat != NULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp",590);
        if(g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    unsigned int count = strlen(format)*4;
    char *buffer;
    int result;
    for (;;) {
        ChangeBuffer(count,0,0,CB_NO_PUSH_ZERO,0);
        buffer = reinterpret_cast<char *>(data)+8;
        result = _vsnprintf(buffer,data->maxSize,format,args);
        if (result>=0) break;
        count*=2;
    }
    buffer[result]=0;
    SetSize(result);
    data->hash=0;
}

// The retail assertion identifies this source at line 561. Native varargs
// use a cdecl member entry with the receiver as the first stack argument.
void __cdecl EAStringC::rva006D62C0(const char *format,...)
{
    if (!format) {
        g_bfmeAptAssertAtE17734("pStrFormat != NULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp",561);
        if(g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    va_list args;
    va_start(args,format);
    rva006D53F0(format,args);
    va_end(args);
}

// Retail source assertion at line 1615 fixes the suffix-removal member here.
// BFME 1 rva0089F730 at ba7ddda7 provides the same suffix/Left semantics.
// Target calls prove value-result Left, copy assignment and refcount release.
// Intrinsic strlen and the value temporary reproduce the native scope state.
bool EAStringC::rva006D5DA0(const char *pStrText)
{
	if (pStrText == 0)
	{
		g_bfmeAptAssertAtE17734("pStrText != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp",
			0x64F);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}

	StringDataC *rep = data;
	unsigned int size = rep->size;

	unsigned int len = strlen(pStrText);

	if (size < len)
		return false;

	const char *folded = (const char *)rep - len;
	if (memcmp(folded + size + (int)sizeof(StringDataC), pStrText, len) == 0)
		goto matched;
	return false;

matched:
    *this = Left(rep->size - len);
    return true;
}
