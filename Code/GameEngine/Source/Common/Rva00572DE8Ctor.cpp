// cl: /MD
// ??0Rva00572DE8@@QAE@XZ @0x00572DD4 20B
// Ctor: base Rva005CB22A holder constructed with (void *)2 at +0, then our
// own vtable 0x0086E094 is stored; returns this. Sibling of
// ??0Rva00572C6E@@QAE@XZ (0x00572C5A, passes 0) and ??0Rva005737AF@@QAE@XZ
// (0x0057379B, passes (void *)1); the rowed dtor ??1Rva00572DE8@@UAE@XZ in
// Rva005CB23CDerived.cpp stores the same vtable. No virtual is defined here
// so this TU emits no vtable.
// Evidence: push esi push 2 mov esi,ecx call ??0Rva005CB22A@@QAE@PAX@Z,
// mov [esi] vtable, mov eax esi; caller 0x0041E650 in 0x0041E561/329.
class Rva005CB22A
{
public:
	Rva005CB22A(void *held);
	virtual ~Rva005CB22A();

	void *m_held;
};

class Rva00572DE8 : public Rva005CB22A
{
public:
	Rva00572DE8();
	virtual ~Rva00572DE8();
};

Rva00572DE8::Rva00572DE8()
	: Rva005CB22A((void *)2)
{
}
