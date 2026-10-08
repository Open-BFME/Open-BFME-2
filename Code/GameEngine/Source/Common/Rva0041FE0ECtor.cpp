// cl: /MD
//
// ??0Rva0041FE0E@@QAE@XZ, retail 0x0041FDF8, 22 bytes.
// Rva0041FE0E ctor: baseConstruct 0x001B4E63 then zero +0x0C then vtable
// 0x00C3B988 then return this. Dtor 0x0041FE0E rowed in
// GameEngineDeletingBaseDerived.cpp proves the class and vtable. Callee
// baseConstruct is rowed. Caller 0x0042017F overwrites vtable to 0x00C3BA28.
// Same recipe as Rva0026201CCtor.cpp (zeros then vtable).

extern "C" const void *const vtbl_00C3B988[];  // ??_7Rva0041FE0E@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C3B988=??_7Rva0041FE0E@@6B@")

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class Rva0041FE0E
{
	int m_pad00[3];
	int m_0C;
public:
	Rva0041FE0E();
};

Rva0041FE0E::Rva0041FE0E()
{
	((BFME2NativeNetwork *)this)->baseConstruct();
	m_0C = 0;
	*(void **)this = (void *)((unsigned int)vtbl_00C3B988);
}
