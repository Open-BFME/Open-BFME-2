// cl: /DNDEBUG /MD /EHsc
// Clean C++ donor: Open-BFME/Open-BFME-1 2791daf5536e4e2147dc3a4aa25c17816828dd69,
// game/GameEngine/Source/GameNetwork/Rva007F9950Assign.cpp, b1 RVA 0x007F9950.
// Native BFME2 0x00665EC0 has an independent aligned, int3-delimited 81B
// extent and ret 4. It copies eleven dwords at +4..+0x2C and one byte at
// +0x30, leaves +0 untouched and returns this. These accesses and the return
// convention are target facts. Donor source supplies the memberwise assignment
// spelling. A virtual slot preserves the leading unassigned four bytes;
// polymorphism and the int field types are structural representations, not
// recovered identity. No virtual call or vtable is emitted by this assignment.
// The class name uses the BFME2 address; original class identity is unknown.

class Rva00665EC0Struct
{
public:
	virtual void slot();

	Rva00665EC0Struct &operator=( const Rva00665EC0Struct &other );

	int m_04;
	int m_08;
	int m_c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	unsigned char m_30;
};

Rva00665EC0Struct &Rva00665EC0Struct::operator=( const Rva00665EC0Struct &other )
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_c = other.m_c;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1c = other.m_1c;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2c = other.m_2c;
	m_30 = other.m_30;
	return *this;
}
