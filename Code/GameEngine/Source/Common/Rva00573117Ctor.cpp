// cl: /MD
// ??0Rva00573117@@QAE@XZ @0x005730FF 24B
// Ctor: base Rva005CB22A holder constructed with (void *)3 at +0, int at +8
// zeroed, then own vtable stored; returns this. Sibling family of
// ??0Rva005734EB@@QAE@XZ (0x005734D7, NULL) and ??0Rva005737AF@@QAE@XZ
// (0x0057379B, (void *)1). Rowed dtor ??1Rva00573117@@UAE@XZ in
// Rva005CB23CDerived.cpp stores vtable 0x0086E0B8.
// Evidence: push esi push 3 mov esi,ecx call ??0Rva005CB22A@@QAE@PAX@Z,
// and [esi+8],0 mov [esi] vtable mov eax esi.
struct Rva005CB22A
{
	Rva005CB22A(void *held);
	virtual ~Rva005CB22A();
	void *m_held;
};
struct Rva00573117 : Rva005CB22A
{
	Rva00573117();
	virtual ~Rva00573117();
	int m_field08;
};
Rva00573117::Rva00573117() : Rva005CB22A((void *)3), m_field08(0)
{
}
