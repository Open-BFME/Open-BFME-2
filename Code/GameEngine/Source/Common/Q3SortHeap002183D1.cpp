// cl: /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common -DNDEBUG -MD -EHsc
//
// ?Rva002183D1SortHeap@@YAXPAURva004748F0Element@@0URva004748F0Compare@@@Z @0x002183D1 58B
// Sort-heap tail of the MixFileCreator FileInfo partial-sort driver 0x002188E4.
// Loops pop-heap Aux 0x00217F96 while more than one 16-byte record remains.
// Evidence: caller 0x002188E4 pushes first/last/comp; callee rowed Aux;
// stride 0x10 matches FileInfoStruct/Q3SortElem16 16B records.
struct Rva004748F0Element
{
	char data[16];
};

struct Rva004748F0Compare
{
	int m_state;
};

void __cdecl Rva00217F96Aux(Rva004748F0Element *first, Rva004748F0Element *last, Rva004748F0Compare comp);

void __cdecl Rva002183D1SortHeap(Rva004748F0Element *first, Rva004748F0Element *last, Rva004748F0Compare comp)
{
	if ((((char *)last - (char *)first) & -16) <= 16)
		return;
	for (;;)
	{
		Rva00217F96Aux(first, last, comp);
		--last;
		if ((((char *)last - (char *)first) & -16) <= 16)
			break;
	}
}
