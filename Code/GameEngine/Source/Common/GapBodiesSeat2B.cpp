// Small accessors from .text gaps no ledger row covered (each begins after
// its neighbour's padding or return and ends in its own ret), none reached by
// a direct caller in retail. Retail bytes establish every shape; the owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches.

// --- 0x000AD711 (12B): address of 16-bit element `index` of the array whose
// base pointer is at +0.
class Rva000AD711
{
public:
	unsigned short *getElement(int index);
private:
	unsigned short *m_items;
};

unsigned short *Rva000AD711::getElement(int index)
{
	return &m_items[index];
}

// --- 0x000B3F5B (12B): address of 64-byte record `index` of the array whose
// base pointer is at +0.
struct Rva000B3F5BRecord
{
	unsigned char m_data[0x40];
};

class Rva000B3F5B
{
public:
	Rva000B3F5BRecord *getRecord(int index);
private:
	Rva000B3F5BRecord *m_records;
};

Rva000B3F5BRecord *Rva000B3F5B::getRecord(int index)
{
	return &m_records[index];
}

// --- 0x00135F0C (13B): address of dword `index` of the array whose base
// pointer is at +4.
class Rva00135F0C
{
public:
	int *GetItem(int index);
private:
	int m_00;
	int *m_items;
};

int *Rva00135F0C::GetItem(int index)
{
	return &m_items[index];
}

// --- 0x000CF0FF (12B): element count of a [begin,end) range of 0x4C-byte
// records held at +0/+4.
struct Rva000CF0FFRecord
{
	unsigned char m_data[0x4C];
};

class Rva000CF0FF
{
public:
	int size() const;
private:
	Rva000CF0FFRecord *m_begin;
	Rva000CF0FFRecord *m_end;
};

int Rva000CF0FF::size() const
{
	return m_end - m_begin;
}

// --- 0x000B2B7C (11B): scales its argument by 0.001 (the constant at
// VA 0x00BC28F8), e.g. milliseconds to seconds.
float Rva000B2B7CScale(float value)
{
	return value * 0.001f;
}

// --- 0x000A47AE (8B): cdecl read of the dword at +0x58 of its argument.
struct Rva000A47AERecord
{
	unsigned char m_pad00[0x58];
	int m_58;
};

int Rva000A47AEGet(const Rva000A47AERecord *record)
{
	return record->m_58;
}

// --- 0x000D1D2B / 0x000D1EA2 (8B each): cdecl addresses of the link words
// at +8 and +4 of a tree-node-like record (the shape of STLport's
// _Rb_tree _S_left / _S_parent; the instantiation is not recovered).
struct Rva000D1D2BNode
{
	int m_color;
	Rva000D1D2BNode *m_parent;
	Rva000D1D2BNode *m_left;
	Rva000D1D2BNode *m_right;
};

Rva000D1D2BNode **_S_left(Rva000D1D2BNode *node)
{
	return &node->m_left;
}

Rva000D1D2BNode **_S_parent(Rva000D1D2BNode *node)
{
	return &node->m_parent;
}

// --- 0x000E0F0E (8B): sets the byte flag at +0x44555.
class Rva000E0F0E
{
public:
	void rva000E0F0E();
private:
	unsigned char m_pad00[0x44555];
	bool m_44555;
};

void Rva000E0F0E::rva000E0F0E()
{
	m_44555 = true;
}

// --- 0x0009DBF4 (17B): log10 of a float through the msvcr71 import
// (thunk 0x0062997C), returned as double.
#include <math.h>

double __cdecl Rva0009DBF4Log10(float value)
{
	return log10(value);
}

// --- 0x000A87E1 (18B): a constructor that only runs the rowed
// ??0Rva0073F4F3@@QAE@PAX@Z (0x0073F468) on itself with its argument.
class Rva0073F4F3
{
public:
	Rva0073F4F3(void *source);
};

class Rva000A87E1 : public Rva0073F4F3
{
public:
	Rva000A87E1(void *source);
};

Rva000A87E1::Rva000A87E1(void *source) : Rva0073F4F3(source)
{
}

// --- 0x000EF26A (8B): cdecl, its argument with bit 15 set.
int Rva000EF26ASetBit15(int value)
{
	return value | 0x8000;
}

// --- 0x000E0197 (12B): XOR of the two dwords of the record it is given
// (the receiver is not read).
struct Rva000E0197Pair
{
	unsigned int m_00;
	unsigned int m_04;
};

class Rva000E0197
{
public:
	unsigned int rva000E0197(const Rva000E0197Pair *pair);
};

unsigned int Rva000E0197::rva000E0197(const Rva000E0197Pair *pair)
{
	return pair->m_04 ^ pair->m_00;
}

// --- 0x000E4422 (12B): clears the dword at +0x2C and sets the flag at +0x9C.
class Rva000E4422
{
public:
	void rva000E4422();
private:
	unsigned char m_pad00[0x2C];
	int m_2C;
	unsigned char m_pad30[0x9C - 0x30];
	bool m_9C;
};

void Rva000E4422::rva000E4422()
{
	m_2C = 0;
	m_9C = true;
}

// --- 0x0010E4C6 (14B): runs the rowed ?rva0010E482@Rva0010E482@@QAEHH@Z
// (0x0010E482) with 0 on the object at +0x94 and returns its result.
class Rva0010E482
{
public:
	int rva0010E482(int index);
};

class Rva0010E4C6
{
public:
	int rva0010E4C6();
private:
	unsigned char m_pad00[0x94];
	Rva0010E482 *m_94;
};

int Rva0010E4C6::rva0010E4C6()
{
	return m_94->rva0010E482(0);
}

// --- 0x001338A0 (7B): the float at +8 minus the float at +0.
class Rva001338A0
{
public:
	float Width() const;
	float Height() const;
private:
	float m_00;
	float m_04;
	float m_08;
	float m_bottom;
};

float Rva001338A0::Width() const
{
	return m_08 - m_00;
}

// --- 0x001338B0 (6B): the sibling difference, the float at +0xC minus the
// float at +4 (with the one above, the width/height pair of a
// left/top/right/bottom rectangle; the class is not established).
float Rva001338A0::Height() const
{
	return m_bottom - m_04;
}

// --- 0x000FA927 (8B) / 0x000FA92F (6B): clear and read the shared dirty
// flag g_bfmeDirtyCU (0x00DFF48C) the screen-filter preRenders test, in the
// screen-filter run ahead of ScreenHilightFilter::init 0x000FA935.
extern bool g_bfmeDirtyCU;

void clearDirty()
{
	g_bfmeDirtyCU = false;
}

bool isDirty()
{
	return g_bfmeDirtyCU;
}

// --- 0x000F0FB8 (5B): a destructor whose only work is its leading Geometry
// member's (the rowed ??1Geometry@@QAE@XZ, 0x000EFC45), emitted as a tail
// jump, in the shadow-geometry run after ??0Geometry 0x000F0F98.
class Geometry
{
public:
	~Geometry();
};

class Rva000F0FB8
{
public:
	~Rva000F0FB8();
private:
	Geometry m_geometry;
};

Rva000F0FB8::~Rva000F0FB8()
{
}

// --- 0x000E0E64 (6B): reads the dx8wrapper flag bfmeOnlyEmissiveDraws
// (0x00DEC3D8); in the aabtreecull run, no direct caller.
extern bool bfmeOnlyEmissiveDraws;

bool Rva000E0E64OnlyEmissiveDraws()
{
	return bfmeOnlyEmissiveDraws;
}
