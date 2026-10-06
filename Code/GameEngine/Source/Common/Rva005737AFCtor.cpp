// cl: /MD
// ??0AITargetHeuristicBaseDefense@@QAE@XZ @0x0057379B 20B
// Ctor: base Rva005CB22A holder constructed with (void *)1 at +0, then our
// own vtable is stored; returns this. Sibling of ??0Rva005734EB@@QAE@XZ
// (0x005734D7) which passes NULL; the rowed dtor ??1AITargetHeuristicBaseDefense@@UAE@XZ in
// Rva005CB23CDerived.cpp stores the same vtable 0x0086E1BC. No virtual is
// defined here so this TU emits no vtable.
// Evidence: push esi push 1 mov esi,ecx call ??0Rva005CB22A@@QAE@PAX@Z,
// mov [esi] vtable, mov eax esi.
struct Rva005CB22A
{
	Rva005CB22A(void *held);
	virtual ~Rva005CB22A();
};
struct AITargetHeuristicBaseDefense : Rva005CB22A
{
	AITargetHeuristicBaseDefense();
	virtual ~AITargetHeuristicBaseDefense();
};
AITargetHeuristicBaseDefense::AITargetHeuristicBaseDefense() : Rva005CB22A((void *)1)
{
}
