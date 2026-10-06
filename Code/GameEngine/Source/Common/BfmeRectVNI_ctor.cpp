// cl: /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/BfmeRectVNI_ctor.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// BfmeRectVNI::BfmeRectVNI 0x003FD64D (67B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME5: VNE-family ctor with inlined 0x2c rb-header at +0xC.
// Retail 0x003BC360, 162 bytes. Base virtual dtor pulls the EH frame.

void *bfmeAllocNode(unsigned int bytes);

class BfmeBaseVNI
{
public:
	BfmeBaseVNI(unsigned w, char f);
	virtual ~BfmeBaseVNI();
	virtual void handle();

	unsigned m_bfme04;
	char m_bfme08;
};


struct BfmeVNINode
{
	char color;
	int *parent;
	BfmeVNINode *left;
	BfmeVNINode *right;
};

struct BfmeVNITree
{
	BfmeVNINode *header;
	int count;
	BfmeVNITree();
};


class BfmeRectVNI : public BfmeBaseVNI
{
public:
	BfmeRectVNI(unsigned w, char f);

	BfmeVNITree m_tree;
	int m_at14;
	int m_at18;
};

// ??0BfmeRectVNI@@QAE@ID@Z
BfmeRectVNI::BfmeRectVNI(unsigned w, char f)
	: BfmeBaseVNI(w, f)
	, m_at18(0)
{
}
