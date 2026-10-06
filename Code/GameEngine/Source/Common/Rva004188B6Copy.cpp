// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD
//
// ??0Rva004188B6@@QAE@ABU0@@Z @0x004188B6 89B: copy constructor of a 32-byte
// record: two 12-byte members copied by the unrowed copy constructor 0x004186F2
// (+0, +0xC; address-derived pin), an AsciiString at +0x18 and bytes +0x1C/+0x1D,
// each constructed member advancing the EH state. Callers 0x00418935 and
// 0x0041896F; record identity not recovered.

#include "ascii_string.h"

class Rva004186F2
{
public:
	Rva004186F2(const Rva004186F2 &other);
	~Rva004186F2();

private:
	char m_pad[0xC];
};

// Each 12-byte member is reached through an inline copy of a holder,
// which gives retail's lea/lea/push argument order at +0xC.
struct Rva004188B6Part
{
	__forceinline Rva004188B6Part(const Rva004188B6Part &other) : m_value(other.m_value) {}

	Rva004186F2 m_value;
};

struct Rva004188B6
{
	Rva004188B6(const Rva004188B6 &other);

	Rva004188B6Part m_00;
	Rva004188B6Part m_0C;
	AsciiString m_18;
	char m_1C;
	char m_1D;
};

Rva004188B6::Rva004188B6(const Rva004188B6 &other) :
	m_00(other.m_00),
	m_0C(other.m_0C),
	m_18(other.m_18),
	m_1C(other.m_1C),
	m_1D(other.m_1D)
{
}
