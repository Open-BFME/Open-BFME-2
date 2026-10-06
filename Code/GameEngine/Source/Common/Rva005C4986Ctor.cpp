// cl: /MD
// ??0Rva005C4986@@QAE@II@Z @0x005C4986 50B
// Honest address-derived ctor: base ??0Rva0059B7CB@@QAE@II@Z with same this
// plus two ints then member ??0Rva005C48D0@@QAE@XZ at +0xC then clear dword
// at +0x20 then vptr 0x00C74764 at +0xC and vptr 0x00C7477C at +0. Chain lane
// after 0x005C48D0. Caller at 0x005C4A61. Prev 0x005C494D clearer and next
// 0x005C4ACD GameWindow getter. Explicit ctor calls give retail lea-edi and
// mov-ecx-edi order with no placement-new null checks.
extern "C" const void *const vtbl_00C7477C[];  // ??_7Rva005C48E5@@6BPrimaryBase@@@
#pragma comment(linker, "/alternatename:_vtbl_00C7477C=??_7Rva005C48E5@@6BPrimaryBase@@@")

extern "C" const void *const vtbl_00C74764[];  // ??_7Rva005C48E5@@6BSecondaryBase@@@
#pragma comment(linker, "/alternatename:_vtbl_00C74764=??_7Rva005C48E5@@6BSecondaryBase@@@")

class Rva0059B7CB
{
public:
	Rva0059B7CB(unsigned int a, unsigned int b);
};

class Rva005C48D0
{
public:
	Rva005C48D0();
};

class Rva005C4986
{
public:
	Rva005C4986(unsigned int a, unsigned int b);
private:
	char m_pad[0x20];
	int m_20; // +0x20
};

Rva005C4986::Rva005C4986(unsigned int a, unsigned int b)
{
	((Rva0059B7CB *)this)->Rva0059B7CB::Rva0059B7CB(a, b);
	Rva005C48D0 *second = (Rva005C48D0 *)((char *)this + 0xC);
	second->Rva005C48D0::Rva005C48D0();
	m_20 = 0;
	*(void **)second = (void *)((unsigned int)vtbl_00C74764);
	*(void **)this = (void *)((unsigned int)vtbl_00C7477C);
}
