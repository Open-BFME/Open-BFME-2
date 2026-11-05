// cl: /DNDEBUG /MD /D_CRTIMP= /EHsc
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
};

// EAStringC is established by the existing ChangeBuffer and SetSize providers.
// The assertion at retail 0x006D53F0 identifies this source and line 590.
// The formatting member name is unknown; keep its address-derived identity.
// Retail proves the shared representation pointer at +0, capacity at +4,
// character storage at +8 and cached hash at +6. The BFME 1 donor at
// ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f was reviewed for this family;
// this formatting body is reconstructed from BFME 2, not carried from it.
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#pragma intrinsic(memcmp)
extern "C" void __cdecl __debugbreak(void);
#pragma intrinsic(strlen,__debugbreak)
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
#include "../EAStringC.h"

// Retail inlines the destructor in this unit.
inline EAStringC::~EAStringC() { FreeData(data); }

// The call at retail 0x006D559A reaches the recovered EAStringC member
// 0x006D47F0 with the unchanged ECX receiver, two C strings and RET8.
// Keep the wrapper's address-derived identity; only its callee is established.
int Rva0089EFE0::method(char value)
{
    char text[2] = "*";
    text[0] = value;
    return reinterpret_cast<EAStringC *>(this)->rva006D47F0(text, "");
}

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
        result = _vsnprintf(buffer,data->m_uMaxSize,format,args);
        if (result>=0) break;
        count*=2;
    }
    buffer[result]=0;
    SetSize(result);
    data->m_uHash=0;
}

// Native 0x006D5300 (225B), Ghidra-unlisted: the appending twin of the
// formatter above. Same pStrFormat assert (line 498, retail texts) and the
// same four-bytes-per-format-character first guess, but the buffer grows past
// the current size and _vsnprintf writes after the existing text; the size
// is set to old size plus the formatted length. Cdecl variadic member entry,
// receiver first on the stack, as rva006D62C0. Address-derived name.
void __cdecl EAStringC::rva006D5300(const char *format,...)
{
    if (!format) {
        g_bfmeAptAssertAtE17734("pStrFormat != NULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp",498);
        if(g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    unsigned int count = strlen(format)*4;
    unsigned int oldSize = data->m_uSize;
    va_list args;
    va_start(args,format);
    char *buffer;
    int result;
    for (;;) {
        ChangeBuffer(oldSize+count,0,0,CB_NO_PUSH_ZERO,0);
        buffer = reinterpret_cast<char *>(data)+8;
        result = _vsnprintf(buffer+oldSize,data->m_uMaxSize-oldSize,format,args);
        if (result>=0) break;
        count*=2;
    }
    buffer[oldSize+result]=0;
    SetSize(oldSize+result);
    data->m_uHash=0;
    va_end(args);
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
	unsigned int size = rep->m_uSize;

	unsigned int len = strlen(pStrText);

	if (size < len)
		return false;

	const char *folded = (const char *)rep - len;
	if (memcmp(folded + size + (int)sizeof(StringDataC), pStrText, len) == 0)
		goto matched;
	return false;

matched:
    *this = Left(rep->m_uSize - len);
    return true;
}

// Retail 0x006D5CD0 (204B), Ghidra-unlisted: the prefix twin of the suffix
// remover above. Asserts pStrText (line 0x62A, retail texts); when the text
// starts the buffer, the string becomes the rowed Mid(len) remainder through
// copy assignment and the value temporary is released. Address-derived name.
bool EAStringC::rva006D5CD0(const char *pStrText)
{
	if (pStrText == 0)
	{
		g_bfmeAptAssertAtE17734("pStrText != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp",
			0x62A);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}

	unsigned int len = strlen(pStrText);
	if (data->m_uSize >= len)
	{
		if (memcmp((char *)data + sizeof(StringDataC), pStrText, len) == 0)
		{
			*this = Mid(len);
			return true;
		}
	}
	return false;
}
