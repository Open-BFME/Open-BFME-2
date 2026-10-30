// cl: /MD /EHsc /DNDEBUG
// stlport
//
// ?applyFilter@Rva003623E5Filter@@QAEXVBfmeFixedStorage0004543D@@@Z
// RVA 0x00362120 size 114. Target pin evidence: five module-data constructor
// callers pass a 28-byte BfmeFixedStorage value, including the convergent
// caller at 0x4C24AE. The 4-byte filter member layout follows the folded ctor
// at 0x3623E5 and teardown at 0x360D26. Exact target bytes show it releases
// the old handle at this+0, constructs a local 0x94-byte record, sets +0x80=3
// and +0x88=1, ORs the argument into +0x64, registers it via 0x361790, and
// stores the returned index. Record offsets follow the matched
// Rva003623E5Member::initFromStorages sibling at 0x362087; the assignments and
// single-storage merge are directly visible in this target's instructions.

#include <vector>
#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib/ascii_string.h"

class BfmeFixedStorage0004543D
{
public:
    BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();

private:
    unsigned char m_data[0x1C];
};

class Rva003623E5Filter
{
public:
	void applyFilter(BfmeFixedStorage0004543D storage);

private:
	int m_record;
};

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

void Rva003623E5Filter::applyFilter(BfmeFixedStorage0004543D storage)
{
	Rva00360CB0Release(&m_record);
	Rva00360F55 record;
	record.m_enabled = 1;
	record.m_kind = 3;
	for (unsigned int offset = 0; offset < 28; offset += 4)
	{
		*(unsigned int *)((unsigned char *)&record.m_secondPlain + offset) |=
			*(unsigned int *)((unsigned char *)&storage + offset);
	}
	m_record = Rva00361790(&record);
}
