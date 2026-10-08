// cl: /MD
//
// ??0Rva0026201C@@QAE@XZ, retail 0x00262002, 26 bytes.
// Rva0026201C ctor beside the rowed dtor: baseConstruct 0x001B4E63 then zero
// +0x0C/+0x10 then vtable 0x007F9010 then return this. Dtor rowed in
// GameEngineDeletingBaseDerived.cpp proves the class and vtable. Callee
// baseConstruct is rowed. Honest address-derived class name.

extern "C" const void *const vtbl_00BF9010[];  // ??_7Rva0026201C@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BF9010=??_7Rva0026201C@@6B@")

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class Rva0026201C
{
	int m_pad00[3];
	int m_0C;
	int m_10;
public:
	Rva0026201C();
};

Rva0026201C::Rva0026201C()
{
	((BFME2NativeNetwork *)this)->baseConstruct();
	m_0C = 0;
	m_10 = 0;
	*(void **)this = (void *)((unsigned int)vtbl_00BF9010);
}
