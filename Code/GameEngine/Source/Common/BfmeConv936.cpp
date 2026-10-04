// Open-BFME5 conversions (trimmed to the placed 936B body; the other three
// are declared-only here).

void __stdcall bfmeElem936B(void *p);
void __stdcall bfmeVecDtor936B(void *p, unsigned int size, int count, void (__stdcall *dtor)(void *));

class BfmeThing936B
{
public:
	void bfmeGo936B(void);
};

// ?bfmeGo936B@BfmeThing936B@@QAEXXZ
void BfmeThing936B::bfmeGo936B(void)
{
	bfmeVecDtor936B(this, 4, 0x80, bfmeElem936B);
}

class BfmeThing936F
{
public:
	void bfmeGo936F(void);
};

void bfmeGo936C(void);

// The former936G view was the stream Init constructor at16AA0. It now
// shares the STLport ios_base::Init view in stlport_loc_init.cpp, beside the
// matching Init lifetime protocol; no duplicate guessed owner remains here.

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:?bfmeVecDtor936B@@YGXPAXIHP6GX0@Z@Z=??_M@YGXPAXIHP6EX0@Z@Z")
