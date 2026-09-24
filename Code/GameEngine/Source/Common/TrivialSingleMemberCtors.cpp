// Trivial single-member constructors: nine-byte frameless __thiscall ctors
// with one shape:
//
//     mov eax,ecx / mov [eax],<CONST> / ret
//
// One pointer-sized field at +0 is initialized to a constant (a vtable for
// the first two, a string literal for the third). MSVC 7.1 emits
// `8B C1` plus `C7 00 IMM32` plus `C3` for nine bytes total. Identity is
// not recovered beyond the initializer: every name is derived from its
// address, with the holder verb describing the single-field shape.
// No // cl: line (defaults match the frameless nine-byte shape).
class Rva00019EB0Holder
{
public:
	Rva00019EB0Holder();
	void *m_vtable;
};
Rva00019EB0Holder::Rva00019EB0Holder()
{
	m_vtable = (void *)0x00BBC8D4;
}
