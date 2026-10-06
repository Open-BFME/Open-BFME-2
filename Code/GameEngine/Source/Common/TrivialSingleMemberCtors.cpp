// Trivial single-member constructors: nine-byte frameless __thiscall ctors
// with one shape:
//
//     mov eax,ecx / mov [eax],<CONST> / ret
//
// One pointer-sized field at +0 is initialized to a vtable. MSVC 7.1 emits
// `8B C1` plus `C7 00 IMM32` plus `C3` for nine bytes total. Identity is
// not recovered beyond the initializer: every name is derived from its
// address, with the holder verb describing the single-field shape.
// No // cl: line (defaults match the frameless nine-byte shape).
extern "C" const void *const vtbl_00BBC8D4[];  // ??_7_Messages@_STL@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBC8D4=??_7_Messages@_STL@@6B@")
extern "C" const void *const vtbl_00BC7F74[];
extern "C" const void *const vtbl_00C6573C[];

class Rva00019EB0Holder
{
public:
	Rva00019EB0Holder();
	void *m_vtable;
};
Rva00019EB0Holder::Rva00019EB0Holder()
{
	m_vtable = (void *)((unsigned int)vtbl_00BBC8D4);
}
class Rva000910D8Holder
{
public:
	Rva000910D8Holder();
	void *m_vtable;
};
Rva000910D8Holder::Rva000910D8Holder()
{
	m_vtable = (void *)((unsigned int)vtbl_00BC7F74);
}
class Rva005114BDHolder
{
public:
	Rva005114BDHolder();
	void *m_vtable;
};
Rva005114BDHolder::Rva005114BDHolder()
{
	m_vtable = (void *)((unsigned int)vtbl_00C6573C);
}
