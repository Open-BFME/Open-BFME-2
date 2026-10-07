// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva001E28B8@@QAE@ABVAsciiString@@@Z @0x001E28B8 42B derived of Rva001E2747.
// Retail calls base 0x001E2747 with AsciiString arg then and [0x2C] 0 then
// mov [0x28] 0xBC6F20 then vtable 0xBDD978 at +0 then mov [0x28] 0xBDD974.
// Caller at 0x001E2C0F plus base vtable 0x7DD970 prove AsciiString passthrough.

extern "C" const void *const vtbl_00BDD978[];  // ??_7Rva001E2906@@6BRva001E2747@@@
#pragma comment(linker, "/alternatename:_vtbl_00BDD978=??_7Rva001E2906@@6BRva001E2747@@@")

extern "C" const void *const vtbl_00BDD974[];  // ??_7Rva001E2906@@6BRva0007DF07@@@
#pragma comment(linker, "/alternatename:_vtbl_00BDD974=??_7Rva001E2906@@6BRva0007DF07@@@")

extern "C" const void *const vtbl_00BC6F20[];  // folded, 7 classes; via ??_7Rva0007DF07@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6F20=??_7Rva0007DF07@@6B@")

#include <list>

#include "ascii_string.h"


class Rva001E2747
{
public:
	Rva001E2747(const AsciiString &name);
private:
	char m_pad[0x28];
};

struct Member28
{
	Member28() : m_vtable((void *)((unsigned int)vtbl_00BC6F20)), m_04(0) {}
	void *m_vtable;
	int m_04;
};

class Rva001E28B8 : public Rva001E2747
{
public:
	Rva001E28B8(const AsciiString &name);
private:
	Member28 m_28;
};

Rva001E28B8::Rva001E28B8(const AsciiString &name) : Rva001E2747(name)
{
	*(unsigned int *)this = (unsigned int)((unsigned int)vtbl_00BDD978);
	m_28.m_vtable = (void *)((unsigned int)vtbl_00BDD974);
}
