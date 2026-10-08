// cl: /EHsc
//
// ??0Rva00317BBB@@QAE@XZ at 0x00317BA5, 22 bytes.
// Ctor beside rowed dtor ??1Rva00317BBB@@UAE@XZ at 0x00317BBB: baseConstruct
// 0x001B4E63 then zero +0x0C then vtable 0x00C0C62C then return this.
// Evidence: vtable store plus rowed baseConstruct plus dtor row plus caller
// at 0x0022E82D. Honest ctor name for Rva00317BBB.

extern "C" const void *const vtbl_00C0C62C[];
#pragma comment(linker, "/alternatename:_vtbl_00C0C62C=??_7Rva00317BBB@@6B@")

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class Rva00317BBB
{
	int m_pad00[3];
	int m_0C;
public:
	Rva00317BBB();
};

Rva00317BBB::Rva00317BBB()
{
	((BFME2NativeNetwork *)this)->baseConstruct();
	m_0C = 0;
	*(void **)this = (void *)((unsigned int)vtbl_00C0C62C);
}
