// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv975.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: BfmeD975::bfmeGo975D 0x0033C396 (38B). Callee addresses are
// read off retail's call sites (reverse/symbols.csv). Only the placed bodies
// are carried; the donor's other definitions are omitted.
// Open-BFME5 conversions.

// The template lookup is the rowed Rva002D06CA::rva002D06CA.
class AsciiString;
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};

struct BfmeObj975A
{
	char m_bfmePad[0x344];
	char m_bfmeFlags;
};

class BfmeA975
{
public:
	virtual void bfmeV0975();
	virtual void bfmeV1975();
	virtual void bfmeV2975();
	virtual void bfmeV3975();
	virtual void bfmeV4975();
	virtual void bfmeV5975();
	virtual void bfmeV6975();
	virtual void bfmeV7975();
	virtual void bfmeV8975();
	virtual void bfmeV9975();
	virtual void bfmeV10975();
	virtual void bfmeV11975();
	virtual void bfmeV12975();
	virtual void bfmeStart975A(BfmeObj975A *o);
	virtual void bfmeStop975A(BfmeObj975A *o);

	void bfmeGo975A(BfmeObj975A *o);
};


class BfmeMgr975B
{
public:
	virtual void bfmeV0975();
	virtual void bfmeV1975();
	virtual void bfmeV2975();
	virtual void bfmeV3975();
	virtual void bfmeV4975();
	virtual void bfmeV5975();
	virtual void bfmeV6975();
	virtual void bfmeV7975();
	virtual void bfmeV8975();
	virtual void bfmeV9975();
	virtual void bfmeV10975();
	virtual void bfmeV11975();
	virtual void bfmeV12975();
	virtual void bfmeV13975();
	virtual void bfmeV14975();
	virtual void bfmeV15975();
	virtual void bfmeV16975();
	virtual void bfmeV17975();
	virtual void bfmeV18975();
	virtual void bfmeV19975();
	virtual void bfmeV20975();
	virtual void bfmeV21975();
	virtual void bfmeV22975();
	virtual void bfmeV23975();
	virtual void bfmeV24975();
	virtual void bfmeV25975();
	virtual int bfmeReady975B();
};

struct BfmeHold975B
{
	char m_bfmePad[0x1fc];
	BfmeMgr975B *m_bfmeMgr;
};

class BfmeB975
{
public:
	void bfmeGo975B(int a, int b);
	void bfmeSend975B(int a, int b);

	char m_bfmePad[8];
	BfmeHold975B *m_bfmeHold;
};


class BfmeFind975D
{
public:
	void *bfmeFind975D(int a);
};

// Retail global 0x012EF1D8 is EA's ThingFactory singleton, defined once in
// Common/Thing/ThingFactory.cpp; this TU keeps only its own view of it.
class ThingFactory;

extern ThingFactory *TheThingFactory;

class BfmeD975
{
public:
	char bfmeGo975D(int a);
	char bfmeUse975D(void *p);
};

char BfmeD975::bfmeGo975D(int a)
{
	void *p = ((Rva002D06CA *)TheThingFactory)->rva002D06CA((const AsciiString *)a);

	if (p)
		return bfmeUse975D(p);

	return 0;
}
