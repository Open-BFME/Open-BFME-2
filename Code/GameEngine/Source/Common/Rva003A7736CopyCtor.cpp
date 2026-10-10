// ??0Rva003A7736@@QAE@ABV0@@Z
// cl: /O1 /DNDEBUG /MD /EHsc
// Retail RVA 0x003A7736, 64 bytes. Standalone excerpt of the V3PolyCopyCtors
// attempt: vptr + four ints + wholesale 3-dword block + two bytes.
// 62/64 identical; sole wall is push-esi placement (retail pushes both after
// the +0x10 load; this shape pushes esi before the +0x0C store). Tried named
// ints vs array-held block (identical output). Array variant also banked here
// via git history of the TU.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
typedef int Int;

struct Rva003A7736Block
{
	Int m_v0;
	Int m_v1;
	Int m_v2;
};

class Rva003A7736
{
public:
	Rva003A7736(const Rva003A7736 &other);
	virtual ~Rva003A7736();

	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Rva003A7736Block m_block14;
	char m_field20;
	char m_field21;
};

Rva003A7736::Rva003A7736(const Rva003A7736 &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field10 = other.m_field10;
	_ReadWriteBarrier();
	m_block14 = other.m_block14;
	m_field20 = other.m_field20;
	m_field21 = other.m_field21;
}
