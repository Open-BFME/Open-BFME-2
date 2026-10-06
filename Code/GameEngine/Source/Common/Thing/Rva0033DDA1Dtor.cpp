// cl: /EHs /MD
// ??1Rva0033DDA1@@UAE@XZ @0x0033DDA1 713B.
// Virtual scalar destructor of the large ThingTemplate-side record holder:
// vptr store, 20 member-dtor calls in reverse order, three ehvec array
// teardowns, inline free-holder tails, then the rowed base dtor 0x001E3624.
// All member dtors are declared-only TU-local spellings so each call site
// resolves to its rowed body or symbols.csv pin; only the PtrHolder tails
// inline (free 0x00030830). Member order and sizes mirror the banked 0.99
// layout (+0x364 is the Rva0033BD50 holder, not a CD02Vec).
extern "C" void free(void *block);

struct PtrHolder
{
	void *m_p;
	~PtrHolder()
	{
		if (m_p != 0)
			free(m_p);
	}
};

class Rva0033B84ETok
{
public:
	~Rva0033B84ETok();

private:
	void *m_data;
};

class Rva0033B352Record
{
public:
	~Rva0033B352Record();

private:
	char m_wide_narrow[8];
};

class Rva0033DDA1E4
{
public:
	~Rva0033DDA1E4();

private:
	char m[4];
};

class Rva0033DDA1E8
{
public:
	~Rva0033DDA1E8();

private:
	char m[8];
};

class Rva0033DDA1E14
{
public:
	~Rva0033DDA1E14();

private:
	char m[0x14];
};

class GeometryInfo
{
public:
	virtual ~GeometryInfo();
}; // 4B: vptr only; the +0xa4..0xfc span is dtor-silent POD

struct Rva0033C3F3
{
	void *m_a;
	void *m_b;
	~Rva0033C3F3();
};

class Rva0033CD02Vec
{
public:
	~Rva0033CD02Vec();

private:
	void *m_v[3];
};

class Rva0033CA81Vec
{
public:
	~Rva0033CA81Vec();

private:
	void *m_v[3];
};

class RvaVecAscii
{
public:
	~RvaVecAscii();

private:
	void *m_v[3];
};

struct Rva0033BD50
{
	void *m_begin;
	void *m_end;
	~Rva0033BD50();
};

class Rva0033D4ABVec
{
public:
	~Rva0033D4ABVec();

private:
	void *m_v[3];
};

struct Rva0033BD88
{
	void *m_begin;
	void *m_end;
	~Rva0033BD88();
};

class Rva0025742CTree
{
public:
	~Rva0025742CTree();

private:
	void *m_t[3];
};

class Rva0033D00ATree
{
public:
	~Rva0033D00ATree();

private:
	void *m_t[3];
};

struct Rva0033BDC0
{
	void *m_begin;
	void *m_end;
	~Rva0033BDC0();
};

class Rva0026E1A6
{
public:
	~Rva0026E1A6();

private:
	char m_pad[12];
};

class Rva001E3624
{
public:
	virtual ~Rva001E3624();

private:
	char m_pad[0x14 - 4];
};

class Rva0033DDA1 : public Rva001E3624
{
public:
	virtual ~Rva0033DDA1();

private:
	Rva0033B84ETok m_s14; // +0x14
	char m_pad18[8];
	Rva0033B84ETok m_s20; // +0x20
	char m_pad24[8];
	Rva0033B352Record m_r2c; // +0x2c
	Rva0033B352Record m_r34; // +0x34
	Rva0033B352Record m_r3c; // +0x3c
	Rva0033B352Record m_r44; // +0x44
	Rva0033B352Record m_r4c; // +0x4c
	Rva0033B352Record m_r54; // +0x54
	Rva0033B84ETok m_s5c; // +0x5c
	Rva0033B84ETok m_s60; // +0x60
	Rva0033B84ETok m_s64; // +0x64
	Rva0033B84ETok m_s68; // +0x68
	Rva0033B84ETok m_s6c; // +0x6c
	Rva0033B84ETok m_s70; // +0x70
	Rva0033B84ETok m_s74; // +0x74
	Rva0033B84ETok m_s78; // +0x78
	Rva0033DDA1E4 m_e7c[5]; // +0x7c
	Rva0033B84ETok m_s90; // +0x90
	Rva0033B84ETok m_s94; // +0x94
	Rva0033B84ETok m_s98; // +0x98
	Rva0033B84ETok m_s9c; // +0x9c
	GeometryInfo m_gA0; // +0xa0
	char m_padA4[0xfc - 0xa4];
	Rva0033C3F3 m_cFC; // +0xfc
	char m_pad104[0x124 - 0x104];
	struct Rva0033DDA1E124
	{
		Rva0033DDA1E8 e[0x38];
	} m_e124; // +0x124
	Rva0033CD02Vec m_v2e4; // +0x2e4
	Rva0033CD02Vec m_v2f0; // +0x2f0
	Rva0033CD02Vec m_v2fc; // +0x2fc
	Rva0033CD02Vec m_v308; // +0x308
	char m_pad314[0x324 - 0x314];
	Rva0033CA81Vec m_v324; // +0x324
	RvaVecAscii m_a330; // +0x330
	RvaVecAscii m_a33c; // +0x33c
	RvaVecAscii m_a348; // +0x348
	char m_pad354[0x358 - 0x354];
	PtrHolder m_h358; // +0x358
	char m_pad35C[0x364 - 0x35c];
	Rva0033BD50 m_d364; // +0x364
	char m_pad36C[0x370 - 0x36c];
	Rva0033D4ABVec m_v370; // +0x370
	Rva0033BD88 m_d37c; // +0x37c
	char m_pad384[0x388 - 0x384];
	Rva0025742CTree m_t388; // +0x388
	Rva0033D00ATree m_t394; // +0x394
	Rva0033BDC0 m_d3a0; // +0x3a0
	char m_pad3A8[0x3ac - 0x3a8];
	Rva0026E1A6 m_m3ac; // +0x3ac
	PtrHolder m_h3b8; // +0x3b8
	char m_pad3BC[0x3c4 - 0x3bc];
	Rva0033DDA1E14 m_e3c4[2]; // +0x3c4
	PtrHolder m_h3ec; // +0x3ec
	char m_pad3F0[0x3f8 - 0x3f0];
	PtrHolder m_h3f8; // +0x3f8
};

Rva0033DDA1::~Rva0033DDA1()
{
}
