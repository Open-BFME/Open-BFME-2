// cl: /MD
// ??0Rva005734EB@@QAE@XZ @0x005734D7 20B
// Ctor: base Rva005CB22A holder constructed with NULL at +0, then our own
// vtable is stored; returns this. The rowed dtor ??1Rva005734EB@@UAE@XZ in
// Rva005CB23CDerived.cpp stores the same vtable 0x0086E1A4 and tail-calls
// the base dtor; no virtual is defined here so this TU emits no vtable.
// Evidence: push esi push 0 mov esi,ecx call ??0Rva005CB22A@@QAE@PAX@Z,
// mov [esi] vtable, mov eax esi.
struct Rva005CB22A
{
	Rva005CB22A(void *held);
	virtual ~Rva005CB22A();
};
struct Rva005734EB : Rva005CB22A
{
	Rva005734EB();
	virtual ~Rva005734EB();
};
Rva005734EB::Rva005734EB() : Rva005CB22A(0)
{
}
