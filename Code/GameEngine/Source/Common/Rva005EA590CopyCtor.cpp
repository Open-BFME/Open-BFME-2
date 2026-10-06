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
	virtual void s0();
	virtual ~Rva005EA6C0Part0() {}
	int m_field04;
};

class Rva005EA6C0Part1
{
public:
	virtual void s0();
	virtual ~Rva005EA6C0Part1() {}
};

class Rva005EA6C0 : public Rva005EA6C0Part0, public Rva005EA6C0Part1
{
public:
	Rva005EA6C0( const Rva005EA6C0 & );
};

struct Rva005EA590Block
{
	int m_value[ 32 ];
};

class Rva005E95C0
{
public:
	Rva005E95C0( const Rva005E95C0 & );
	virtual ~Rva005E95C0();
	Rva005EA590Block m_block;
	int m_field84;
};

struct Rva005EA590Triple
{
	int m_value[ 3 ];
};

class Rva005EA590 : public Rva005EA6C0, public Rva005E95C0
{
public:
	Rva005EA590( const Rva005EA590 & );
	Rva005EA590Triple m_fields94;
	Rva005EA590Triple m_fieldsA0;
	int m_fieldAC;
};

Rva005EA590::Rva005EA590( const Rva005EA590 &o )
	: Rva005EA6C0( o ), Rva005E95C0( o )
{
	m_fields94 = o.m_fields94;
	m_fieldsA0 = o.m_fieldsA0;
	m_fieldAC = o.m_fieldAC;
}
