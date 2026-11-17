// cl: /EHs-c-
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Rva005EA590CopyCtor.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// Rva005EA590::Rva005EA590 0x003ADD31 (108B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// The base widths and copy order match the adjacent constructors in the same
// retail family.
class Rva005EA6C0Part0
{
public:
	virtual ~Rva005EA6C0Part0() {}
	int m_field04;
};

class Rva005EA6C0Part1
{
public:
	virtual void s0() = 0;
	~Rva005EA6C0Part1() {}
};

class Rva0055BCD2 : public Rva005EA6C0Part0, public Rva005EA6C0Part1
{
public:
	Rva0055BCD2( const Rva0055BCD2 & );
	virtual ~Rva0055BCD2();
};

struct ColorRateKey
{
    float red, green, blue;
    unsigned int frame;
};

struct Rva005EA590Block
{
    ColorRateKey keys[8];
};

class Rva005E95C0
{
public:
	Rva005E95C0( const Rva005E95C0 & );
	virtual void slot00() = 0;
	virtual void slot04() {}
	virtual const char *GetSnapshotName() const = 0;
	virtual void slot0C() = 0;
	Rva005EA590Block m_block;
	int m_field84;
};

struct Rva005EA590Triple
{
	float red, green, blue;
};

class Rva005EA590 : public Rva0055BCD2, public Rva005E95C0
{
public:
	Rva005EA590( const Rva005EA590 & );
	virtual const char *GetSnapshotName() const;
	void calculateRates();
	Rva005EA590Triple m_fields94;
	Rva005EA590Triple m_fieldsA0;
	int m_fieldAC;
};

Rva005EA590::Rva005EA590( const Rva005EA590 &o )
	: Rva0055BCD2( o ), Rva005E95C0( o )
{
	m_fields94 = o.m_fields94;
	m_fieldsA0 = o.m_fieldsA0;
	m_fieldAC = o.m_fieldAC;
}

// Native slot 2 of the Snapshot table 0081D194.
const char *Rva005EA590::GetSnapshotName() const
{
	return "DefaultParticleModule<CAT_COLOR>";
}

void Rva005EA590::calculateRates()
{
    int i = m_fieldAC;
    unsigned int dt = m_block.keys[i].frame;
    if (dt == 0) {
        m_fieldsA0.red = 0.0f;
        m_fieldsA0.green = 0.0f;
        m_fieldsA0.blue = 0.0f;
        return;
    }
    dt -= m_block.keys[i-1].frame;
    float inv = 1.0f / (float)dt;
    m_fieldsA0.red = (m_block.keys[i].red - m_fields94.red) * inv;
    m_fieldsA0.green = (m_block.keys[i].green - m_fields94.green) * inv;
    m_fieldsA0.blue = (m_block.keys[i].blue - m_fields94.blue) * inv;
}
