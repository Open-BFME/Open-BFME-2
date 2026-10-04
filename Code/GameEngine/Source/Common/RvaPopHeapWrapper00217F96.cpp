// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?Rva00217F96Aux@@YAXPAURva004748F0Element@@0URva004748F0Compare@@@Z @0x00217F96 23B
// Unlock thin __cdecl wrapper forwarding to rowed Rva00474A90PopHeapAux at
// 0x00217C01 with a null third arg. Evidence: push push-0 push push plus call
// plus add esp 0x10; caller at 0x002183F0.
struct Rva004748F0Element;
struct Rva004748F0Compare
{
	int m_state;
};

void __cdecl Rva00474A90PopHeapAux(Rva004748F0Element *first, Rva004748F0Element *last,
	Rva004748F0Element *result, Rva004748F0Compare comp);

void __cdecl Rva00217F96Aux(Rva004748F0Element *first, Rva004748F0Element *last,
	Rva004748F0Compare comp)
{
	Rva00474A90PopHeapAux(first, last, 0, comp);
}
