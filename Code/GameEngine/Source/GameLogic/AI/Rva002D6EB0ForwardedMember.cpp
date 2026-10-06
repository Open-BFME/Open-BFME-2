// cl: /DNDEBUG /MD /EHsc /Ob2
//
// Ported from Open-BFME-1 GameEngine/Source/GameLogic/AI/Rva002D6EB0ForwardedMember.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?update@Rva002D6EB0@@QAEXXZ 0x004B4204 (25B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

class BfmeSubBPB
{
public:
	void bfmeDoBPB(void *first, void *second, void *third);
};

class Rva002D6EB0Parent
{
private:
	char m_pad00[8];

public:
	BfmeSubBPB *m_nested;
};

class Rva002D6EB0
{
public:
	void update();

private:
	char m_pad00[0x0C];
	Rva002D6EB0Parent *m_parent;
	void *m_forwarded;
};

void Rva002D6EB0::update()
{
	Rva002D6EB0Parent *parent = m_parent;
	if (parent->m_nested != 0)
		parent->m_nested->bfmeDoBPB(m_forwarded, 0, 0);
}
