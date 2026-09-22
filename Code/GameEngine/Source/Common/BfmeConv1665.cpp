// Open-BFME5 conversion.
//
// The sibling copy constructor ??0BfmeOwnVVE@@QAE@ABV0@@Z, carried over from
// the same BFME1 donor TU, does not mask-search to any address in this
// image (0 hits): BFME2 either never instantiates it or compiles it to
// different bytes, so it is not claimable from this donor and is left out.

void __cdecl operator delete[](void *block);

class BfmeElemVVE
{
public:
	~BfmeElemVVE();

	void *m_bfme00;
};

class BfmeBaseVVE
{
public:
	BfmeBaseVVE() : m_bfmeRefs( 1 ) {}
	~BfmeBaseVVE() { }
	virtual void bfmeSlot0VVE();
	int m_bfmeRefs;
};

class BfmeOwnVVE : public BfmeBaseVVE
{
public:
	~BfmeOwnVVE();
	BfmeElemVVE *m_bfme08;
	BfmeElemVVE *m_bfme0C;
	int m_bfme10;
	int m_bfme14;
};

BfmeOwnVVE::~BfmeOwnVVE()
{
	delete [] m_bfme08;
}
