// Open-BFME5 conversions.

struct BfmeHandleUZA
{
	int m_bfmeValue;
};

class BfmeSubAUZA
{
public:
	BfmeHandleUZA bfmeGetAUZA(int a, int b) const;
};


class BfmeThingAUZA
{
public:
	BfmeHandleUZA bfmeGoAUZA(int a, int b) const;
	char m_bfmePad[0x94];
	BfmeSubAUZA *m_bfmeSub;
};

BfmeHandleUZA BfmeThingAUZA::bfmeGoAUZA(int a, int b) const
{
	volatile int m_bfmeDead = 0;
	return m_bfmeSub->bfmeGetAUZA(a, b);
}


// The retail call in this body reads 0x0015A180, an address the ledger already
// carries as ?Get_Single_Texture@MeshMatDescClass@@QBE?AV?$RefCountPtr@VTextureClass@@@@HH@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?bfmeGetAUZA@BfmeSubAUZA@@QBE?AUBfmeHandleUZA@@HH@Z=?Get_Single_Texture@MeshMatDescClass@@QBE?AV?$RefCountPtr@VTextureClass@@@@HH@Z")
