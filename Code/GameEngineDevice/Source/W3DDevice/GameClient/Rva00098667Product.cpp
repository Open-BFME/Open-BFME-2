// cl: /MD /EHsc /DNDEBUG
//
// ??0Rva00098667Product@@QAE@XZ @0x00098667 41B: game-client product
// constructor (size 0x68, vtable 0x00BC8358). Calls the base constructor
// 0x0030AFC4 (vtable 0x00BC8318 family, pinned), installs its own vtable,
// and zeroes the seven tail dwords at +0x4C..+0x64. Honest address-derived
// base name; product name is proven by the factory REL32 at 0x0004C694
// (new 0x68 plus this ctor). Boundary verified (push esi at 0x98667,
// pop esi + ret at end).

class Rva0030AFC4Base
{
public:
	Rva0030AFC4Base();
	virtual ~Rva0030AFC4Base();

private:
	char m_pad04[0x4C - 4];
};

class Rva98667Tail
{
public:
	Rva98667Tail()
	{
		m_00 = 0;
		m_04 = 0;
		m_08 = 0;
		m_0C = 0;
		m_10 = 0;
		m_14 = 0;
		m_18 = 0;
	}

private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
};

class Rva00098667Product : public Rva0030AFC4Base
{
public:
	Rva00098667Product();

private:
	Rva98667Tail m_4C;
};

// ??0Rva00098667Product@@QAE@XZ
Rva00098667Product::Rva00098667Product()
{
}
