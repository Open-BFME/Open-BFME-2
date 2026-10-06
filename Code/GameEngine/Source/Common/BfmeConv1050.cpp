// Open-BFME5 conversions.

void bfmeReset1050(int n);

class BfmeA1050
{
public:
	void bfmeGo1050A(void);

	char m_bfmePad[8];
	int m_bfme08;
	char m_bfmePad2[0x55];
	char m_bfmeFlag;
	char m_bfmePad3[0xc6];
	int m_bfme128;
};

// ?bfmeGo1050A@BfmeA1050@@QAEXXZ present-unmatched
void BfmeA1050::bfmeGo1050A(void)
{
	m_bfmeFlag = 0;
	bfmeReset1050(0);
	m_bfme08 = 0;
	m_bfme128 = 0;
}

extern "C" void *bfmeVft1050B[];

class BfmeB1050
{
public:
	BfmeB1050 *bfmeGo1050B(void);
	void bfmeBase1050(void);

	void *m_bfmeVfptr;
	char m_bfmePad[0x54];
	int m_bfme58;
	int m_bfme5c;
	float m_bfme60;
	char m_bfme64;
};

// ?bfmeGo1050B@BfmeB1050@@QAEPAV1@XZ present-unmatched
BfmeB1050 *BfmeB1050::bfmeGo1050B(void)
{
	bfmeBase1050();

	int z = 0;

	m_bfme58 = z;
	m_bfme5c = z;
	m_bfme64 = (char)z;
	m_bfme60 = 20.0f;
	m_bfmeVfptr = bfmeVft1050B;
	return this;
}

class BfmeP1050
{
public:
	void bfmeFwd1050(int a, int b, int c, int d, int e);
};

class BfmeC1050
{
public:
	void bfmeGo1050C(int a, int b, int c, int d, int e);
	void bfmeGo009F26D0(int a, int b, int c, int d);

	char m_bfmePad[0x10]; // BFME2 target at 0x625390 loads this pointer at +0x10.
	BfmeP1050 *m_bfmeP;
};

void BfmeC1050::bfmeGo1050C(int a, int b, int c, int d, int e)
{
	m_bfmeP->bfmeFwd1050(a, c, b, d, e);
}

struct Coord3D;
class Object;
class Rva000421C8;	// the partition filter base (ctor 0x000421C8)

// The partition manager's closest-object implementation behind +0x10
// (0x00628040, the bfmeFwd1050 callee): position, radius, 0, distance
// type, filter chain.
class Rva00628040Impl
{
public:
	Object *rva00628040(const Coord3D *pos, float radius, int zero, int distType,
		Rva000421C8 *filters);
};

// ThePartitionManager (0x00DFE748): 26 matched callers reference this
// method by name. BFME1 retail 0x009F26A0 is the same four-argument
// wrapper with an explicit 0 in the third slot.
class PartitionManager
{
	char m_pad[0x10];
	Rva00628040Impl *m_impl;

public:
	Object *getClosestObject(const Coord3D *pos, float radius, int distType,
		Rva000421C8 *filters);
};

Object *PartitionManager::getClosestObject(const Coord3D *pos, float radius, int distType,
	Rva000421C8 *filters)
{
	return m_impl->rva00628040(pos, radius, 0, distType, filters);
}

void BfmeC1050::bfmeGo009F26D0(int a, int b, int c, int d)
{
	m_bfmeP->bfmeFwd1050(a, c, b, d, 0);
}

extern "C" void *bfmeVft1050F[];

class BfmeF1050
{
public:
	BfmeF1050 *bfmeGo1050F(int a, int b, int c);
	void bfmeBaseF1050(int a, int b, int c);

	void *m_bfmeVfptr;
};

BfmeF1050 *BfmeF1050::bfmeGo1050F(int a, int b, int c)
{
	bfmeBaseF1050(a, b, c);
	m_bfmeVfptr = bfmeVft1050F;
	return this;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:_bfmeVft1050F=??_7GridEnvironmentMapperClass@@6B@")
