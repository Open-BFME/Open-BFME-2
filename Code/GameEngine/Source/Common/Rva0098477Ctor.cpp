// cl: /MD
//
// ??0Rva0098477@@QAE@XZ, retail 0x00318AA5, 22 bytes.
// Rva0098477 ctor beside the rowed dtor 0x00098477: baseConstruct 0x001B4E63
// then vtable 0x00BC8298 then zero +0x0C then return this. Dtor rowed in
// SubsystemDerivedDtors.cpp proves the class and vtable (string +0x0C).
// Callee baseConstruct is rowed. Barrier keeps the vptr store before the
// zero like retail; same recipe as Rva0026201CCtor.cpp.

extern "C" const void *const vtbl_00BC8298[];  // ??_7Rva0098477@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC8298=??_7Rva0098477@@6B@")

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class Rva0098477
{
	int m_pad00[3];
	int m_0C;
public:
	Rva0098477();
};

Rva0098477::Rva0098477()
{
	((BFME2NativeNetwork *)this)->baseConstruct();
	*(void **)this = (void *)((unsigned int)vtbl_00BC8298);
	_ReadWriteBarrier();
	m_0C = 0;
}
