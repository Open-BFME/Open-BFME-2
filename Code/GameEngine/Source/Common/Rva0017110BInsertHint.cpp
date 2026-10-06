// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?rva0017110B@Rva00170BFF@@QAE?AURva00170EFEIter@@U2@ABVRva00170999@@@Z
// Candidate 0x0017110B, 29B. Forwards hint-insert (position, value) to the
// rowed worker 0x00170EFE on the same Rva00170BFF tree; caller 0x00171128
// passes this through in ecx with hidden return pointer. Boundary from int3
// padding; byte verification decides.
#include <map>

class Rva00170999;

struct Rva00170EFENode
{
	unsigned int _color;
	Rva00170EFENode *_parent;
	Rva00170EFENode *_left;
	Rva00170EFENode *_right;
	char _val10[0x14];
};

struct Rva00170EFEIter
{
	Rva00170EFENode *node;
	Rva00170EFEIter(Rva00170EFENode *p) : node(p) {}
	Rva00170EFEIter(const Rva00170EFEIter &o) : node(o.node) {}
};

struct Rva00170DB7Out
{
	Rva00170EFENode *node;
	bool inserted;
};

class Rva00170BFF
{
	Rva00170EFENode *m_00Head;
	unsigned int m_04Flag;
public:
	Rva00170EFEIter rva00170EFE(Rva00170EFEIter position,
		const Rva00170999 &value);
	Rva00170EFEIter rva0017110B(Rva00170EFEIter position,
		const Rva00170999 &value);
};

Rva00170EFEIter Rva00170BFF::rva0017110B(Rva00170EFEIter position,
	const Rva00170999 &value)
{
	return rva00170EFE(position, value);
}
