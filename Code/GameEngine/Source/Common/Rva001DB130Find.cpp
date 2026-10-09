// cl: /Ob0
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva001DB130Find.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?find@Rva001DB130@@QAEPAURva001DB130Node@@H@Z 0x004DE549 (26B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

struct Rva001DB130Node
{
	char pad[0x0C];
	int m_0C;
	Rva001DB130Node *m_10;
};

class Rva001DB130
{
	Rva001DB130Node *m_00;
	Rva001DB130Node *m_04;

public:
	Rva001DB130Node *find(int v);
};

Rva001DB130Node *Rva001DB130::find(int v)
{
	Rva001DB130Node *p = m_04;
	m_00 = p;
	if (!p)
		return 0;
	do
	{
		if (p->m_0C == v)
			return p;
		p = p->m_10;
	} while (p);
	return 0;
}

// Clean BF1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d
// Common/Rva001DB120Advance.cpp guides this cursor advance, not its identity.
// Native 4DE53C..4DE549 follows the previous RET and has two own RET0 exits:
// receiver word0 null => return; otherwise replace it with node word+0x10.
// Reuse the existing accessed node prefix; the cursor owner's original class
// is unknown and is kept separate from the existing find owner's declaration.
// The donor's zero-instruction compiler barrier preserves the early null RET;
// it is a compiler-shape guide, not an asserted retail memory fence.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct Rva004DE53C
{
    Rva001DB130Node *cursor;
    void advance();
};
void Rva004DE53C::advance()
{
    Rva001DB130Node *current = cursor;
    if (!current) {
        _ReadWriteBarrier();
        return;
    }
    cursor = current->m_10;
}
