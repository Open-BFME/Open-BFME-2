// cl: /DNDEBUG /MD /EHsc /Ob2
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/BfmeOwnerDtorCC.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// BfmeOwnerCC::~BfmeOwnerCC 0x0007280A (92B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
//
// Open-BFME5: a destructor at retail 0x0073A4E0, 109 bytes.  Both vftable
// stores are compiler-generated, which is what puts the first one ahead of the
// unwind state rather than after it.

// The cleanup is the rowed W3DVideoBuffer::rva00072583.
class W3DVideoBuffer
{
public:
	void rva00072583();
};

class BfmeElemCC
{
public:
	~BfmeElemCC(void);

	char m_bfmePadECC[0x14];
};

class BfmeRegistryCC
{
public:
	void bfmeForgetCC(void *owner);
};

// Retail 0x012F1270 is EA's `Display *TheDisplay` (defined in
// game/GameEngine/Source/GameClient/Display.cpp).  The registry call is reached
// through the local view, so the cast happens at the use.
class Display;
extern Display *TheDisplay;

class BfmeBaseCC
{
public:
	virtual ~BfmeBaseCC(void)
	{
	}
};

class BfmeOwnerCC : public BfmeBaseCC
{
public:
	virtual ~BfmeOwnerCC(void);

	void bfmeCleanupCC(void);

	char m_bfmePadCC[0x28];
	BfmeElemCC m_bfmeElemsCC[1];
};

BfmeOwnerCC::~BfmeOwnerCC(void)
{
	((W3DVideoBuffer *)this)->rva00072583();

	if (TheDisplay != 0)
		((BfmeRegistryCC *)TheDisplay)->bfmeForgetCC(this);
}
