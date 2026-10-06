// cl: /MD
//
// Address-derived recovery of the 57-byte checked pop at RVA 0x00706330. The
// body is a stack pop on {int count; int capacity; Element **array} (the
// AptBasePtrStack layout already established in Rva007062F0Siblings.cpp): it
// decrements the count, takes the element, and if live destroys it through the
// address-derived element destructor ??1Rva006FBDB0@@QAE@XZ (0x006FBDB0, which
// zeroes +4 and tail-jumps the EAStringC destructor at 0x006D3010) and returns
// its 12-byte store to the pool through the rowed freeBlock
// ?freeBlock@Rva006DB270@@QAEXPAXH@Z (0x006DB270) via the pool at 0x00E176E8,
// then clears the vacated slot. The caller at 0x007073BA is an
// AptDebugStack<DebugCallStackInfo_t> method, but that template name is not
// proven for this body, so the class and method stay address-derived.

class Rva006FBDB0
{
public:
	~Rva006FBDB0();

	char m_bfmePad[8];
};

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

class Rva00706330Stack
{
public:
	void rva00706330();

	int m_bfmeCount;
	int m_bfmeCapacity;
	Rva006FBDB0 **m_bfmeArray;
};

// ?rva00706330@Rva00706330Stack@@QAEXXZ
void Rva00706330Stack::rva00706330()
{
	--m_bfmeCount;
	Rva006FBDB0 *element = m_bfmeArray[m_bfmeCount];
	if (element) {
		element->~Rva006FBDB0();
		g_pChainBlockAllocator->freeBlock(element, 0xC);
	}
	m_bfmeArray[m_bfmeCount] = 0;
}
