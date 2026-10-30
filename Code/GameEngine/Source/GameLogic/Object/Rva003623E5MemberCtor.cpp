// cl: /MD /EHsc /DNDEBUG
// stlport
//
// ??0Rva003623E5Member@@QAE@XZ at 0x003623E5 (82 bytes).
// The ctor resets its 4-byte handle to -1, builds a 0x94-byte default record
// with the rowed 0x360F55 ctor, registers/deduplicates it through 0x361790,
// stores the returned pool index, then destroys the local through 0x360FDB.
// The 0x361790 helper's identity is unknown; its pointer argument and integer
// return are established by this call site and the callee's table scan.

class BfmeFixedStorage0004543D
{
public:
    BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();

private:
    unsigned char m_data[0x1C];
};

#include <vector>
#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef unsigned int UnsignedInt;
typedef _STL::vector<AsciiString> AsciiStringVector;

struct BfmeAttributeBits
{
	UnsignedInt m_values[7];	// BitFlags<218>
};

class Rva00360F55
{
public:
	Rva00360F55();
	~Rva00360F55();
	bool rva00360E64(const Rva00360F55 &other);

	AsciiStringVector m_names;			// +0x00
	AsciiStringVector m_values;			// +0x0C
	AsciiStringVector m_lists[4];		// +0x18
	BfmeAttributeBits m_firstPlain;		// +0x48
	BfmeAttributeBits m_secondPlain;	// +0x64
	UnsignedInt m_kind;					// +0x80
	UnsignedInt m_relationship;			// +0x84
	bool m_enabled;						// +0x88
	unsigned char m_pad89[3];
	UnsignedInt m_useCount;				// +0x8C
	UnsignedInt m_alignment;			// +0x90
};

void Rva00360CB0Release(int *indexHolder);
int __cdecl Rva00361790(Rva00360F55 *record);

template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

class Rva00045411BitSet
{
public:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first,
	                      BfmeFixedStorage0004543D second);
	void rva00362192(Rva00045411BitSet first, BfmeFixedStorage0004543D second);

private:
	unsigned int m_record;
};

Rva003623E5Member::Rva003623E5Member()
	: m_record(-1)
{
	Rva00360F55 defaultRecord;
	m_record = Rva00361790(&defaultRecord);
}

class Rva00360D26Member
{
public:
	Rva00360D26Member();

private:
	unsigned int m_record;
};

// The 4-byte filter handle's constructor folds with the address-derived member
// constructor above. Its 0x94-byte default record is a temporary, not its size.
Rva00360D26Member::Rva00360D26Member()
	: m_record(-1)
{
	Rva00360F55 defaultRecord;
	m_record = Rva00361790(&defaultRecord);
}

// 0x362087 (153B): release the previous pool index, then register a rebuilt
// 0x94-byte record. Target merges the two 28-byte inputs at +0x48/+0x64 and
// sets +0x88 when any dword in the first input is nonzero; these field labels
// describe offsets only, not recovered domain names.
void Rva003623E5Member::initFromStorages(
	BfmeFixedStorage0004543D first,
	BfmeFixedStorage0004543D second)
{
	Rva00360CB0Release((int *)&m_record);
	Rva00360F55 record;
	record.m_enabled = 0;
	record.m_kind = 1;
	for (unsigned int offset = 0; offset < 28; offset += 4)
	{
		*(unsigned int *)((unsigned char *)&record.m_firstPlain + offset) |=
			*(unsigned int *)((unsigned char *)&first + offset);
	}
	for (unsigned int offset = 0; offset < 28; offset += 4)
	{
		*(unsigned int *)((unsigned char *)&record.m_secondPlain + offset) |=
			*(unsigned int *)((unsigned char *)&second + offset);
	}
	for (unsigned int index = 0; index < 7; ++index)
	{
		if (((unsigned int *)&first)[index] != 0)
		{
			record.m_enabled = 1;
			break;
		}
	}
	m_record = Rva00361790(&record);
}

void Rva003623E5Member::rva00362192(Rva00045411BitSet first, BfmeFixedStorage0004543D second)
{
	Rva00360CB0Release((int *)&m_record);
	Rva00360F55 record;
	record.m_enabled = 0;
	record.m_kind = 2;
	for (unsigned int offset = 0; offset < 28; offset += 4)
	{
		*(unsigned int *)((unsigned char *)&record.m_firstPlain + offset) |=
			*(unsigned int *)((unsigned char *)&first + offset);
	}
	for (unsigned int offset = 0; offset < 28; offset += 4)
	{
		*(unsigned int *)((unsigned char *)&record.m_secondPlain + offset) |=
			*(unsigned int *)((unsigned char *)&second + offset);
	}
	for (unsigned int index = 0; index < 7; ++index)
	{
		if (((unsigned int *)&first)[index] != 0)
		{
			record.m_enabled = 1;
			m_record = Rva00361790(&record);
			return;
		}
	}
	initFromStorages(*reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE), *reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE));
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0Rva003623E5Filter@@QAE@XZ=??0Rva003623E5Member@@QAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?construct@Rva003623E5Member@@QAEXXZ=??0Rva003623E5Member@@QAE@XZ")
