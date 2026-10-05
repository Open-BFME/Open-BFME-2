// ??1Rva0033DDA1@@UAE@XZ
// partial score=0.99 date=2026-10-05
// cl: /O1 /EHs /MD
extern "C" void free(void *block);

class Rva0033B84ETok
{
public:
	Rva0033B84ETok(const char *s);
	~Rva0033B84ETok();
	Rva0033B84ETok() : m_data(0) {}

private:
	void *m_data;
};

struct PtrHolder
{
	void *m_p;
	~PtrHolder() { if (m_p != 0) free(m_p); }
};

struct Rva0033DDA1E14
{
	char m[0x14];
	~Rva0033DDA1E14();
};

struct Rva0033DDA1E8
{
	char m[8];
	~Rva0033DDA1E8();
};

struct Rva0033DDA1E4
{
	char m[4];
	~Rva0033DDA1E4();
};

class Rva0026E1A6
{
public:
	~Rva0026E1A6();
	char m_pad[11];
};

class Rva0033BDC0
{
public:
	~Rva0033BDC0();
};

class Rva0033D00ATree
{
public:
	~Rva0033D00ATree();
};

class Rva0025742CTree
{
public:
	~Rva0025742CTree();
};

class Rva0033BD88
{
public:
	~Rva0033BD88();
};

class Rva0033D4ABVec
{
public:
	~Rva0033D4ABVec();
};

class Rva0033BD50
{
public:
	~Rva0033BD50();
};

class RvaVecAscii
{
public:
	~RvaVecAscii();
};

class Rva0033CA81Vec
{
public:
	~Rva0033CA81Vec();
};

class Rva0033CD02Vec
{
public:
	~Rva0033CD02Vec();
};

class Rva0033C3F3
{
public:
	~Rva0033C3F3();
};

class GeometryInfo
{
public:
	virtual ~GeometryInfo();
};

class Rva0033B352Record
{
public:
	~Rva0033B352Record();
	char m_wide_narrow[8];
};

class Rva001E3624
{
public:
	virtual ~Rva001E3624();

private:
	char m_pad04[0x14 - 4];
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
	char m_padFD[0x124 - 0xfd];
	Rva0033DDA1E8 m_e124[0x38]; // +0x124
	Rva0033CD02Vec m_v2e4; // +0x2e4
	char m_pad2E5[0x2f0 - 0x2e5];
	Rva0033CD02Vec m_v2f0; // +0x2f0
	char m_pad2F1[0x2fc - 0x2f1];
	Rva0033CD02Vec m_v2fc; // +0x2fc
	char m_pad2FD[0x308 - 0x2fd];
	Rva0033CD02Vec m_v308; // +0x308
	char m_pad309[0x324 - 0x309];
	Rva0033CA81Vec m_v324; // +0x324
	char m_pad325[0x330 - 0x325];
	RvaVecAscii m_a330; // +0x330
	char m_pad331[0x33c - 0x331];
	RvaVecAscii m_a33c; // +0x33c
	char m_pad33D[0x348 - 0x33d];
	RvaVecAscii m_a348; // +0x348
	char m_pad349[0x358 - 0x349];
	PtrHolder m_h358; // +0x358
	char m_pad35C[0x364 - 0x35c];
	Rva0033BD50 m_d364; // +0x364
	char m_pad365[0x370 - 0x365];
	Rva0033D4ABVec m_v370; // +0x370
	char m_pad371[0x37c - 0x371];
	Rva0033BD88 m_d37c; // +0x37c
	char m_pad37D[0x388 - 0x37d];
	Rva0025742CTree m_t388; // +0x388
	char m_pad389[0x394 - 0x389];
	Rva0033D00ATree m_t394; // +0x394
	char m_pad395[0x3a0 - 0x395];
	Rva0033BDC0 m_d3a0; // +0x3a0
	char m_pad3A1[0x3ac - 0x3a1];
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
