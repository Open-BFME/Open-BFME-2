extern "C" void bfmeDtorCbDSE(void *what);
void __stdcall bfmeVecDtorDSE(void *base, unsigned int size, int count, void (*dtor)(void *));

class BfmeThingDSE
{
public:
	void bfmeGoDSE();
	char m_bfmeHead[8];
};

void BfmeThingDSE::bfmeGoDSE()
{
	bfmeVecDtorDSE((char *)this + 8, 0xc, 4, bfmeDtorCbDSE);
}

class BfmeThingDSF
{
public:
	void bfmeGoDSF();
	char m_bfmeHead[0x60];
};

void BfmeThingDSF::bfmeGoDSF()
{
	bfmeVecDtorDSE((char *)this + 0x60, 0xc, 4, bfmeDtorCbDSE);
}

// Retail 0x00270234 (44 bytes): thiscall, no arguments, ret. Walks the three
// null-terminated pointer lists at +0x14C, +0x150 and +0x154 in address order,
// calling virtual slot 8 (+0x20) on each non-null element until a null element.
// Owner class and list element type are address-derived; identity unproven.
class Rva00270234Item
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20();
};

class Rva00270234
{
public:
	void rva00270234();
private:
	char m_pad[0x14c];
	Rva00270234Item **m_lists[3];
};

void Rva00270234::rva00270234()
{
	for (int i = 0; i < 3; ++i) {
		Rva00270234Item **p = m_lists[i];
		if (p) {
			do {
				Rva00270234Item *item = *p;
				if (!item)
					break;
				item->slot20();
				++p;
			} while (p);
		}
	}
}

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:?bfmeVecDtorDSE@@YGXPAXIHP6AX0@Z@Z=??_M@YGXPAXIHP6EX0@Z@Z")
