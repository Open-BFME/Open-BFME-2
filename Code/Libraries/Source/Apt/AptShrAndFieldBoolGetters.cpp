// cl: /DNDEBUG /MD
//
// ?get@Rva006DBB40ShrAndField@@QBE_NXZ (retail 0x006DBB40, 9 bytes) and
// ?get@Rva006DBB60ShrNAndField@@QBE_NXZ (retail 0x006DBB60, 9 bytes): the
// bool-returning flag getters Rva006E3230Validate.cpp calls (each call site
// tests al). Same bodies as the rowed int-returning getters at those
// addresses (Disp8ShrAndDwordGetters.cpp): bit 1 and bit 4 of the dword at
// +4, so each lands as that row's ICF alias.

class Rva006DBB40ShrAndField
{
public:
	bool get() const;

private:
	char m_lead[0x04];
	unsigned int m_value;
};

bool Rva006DBB40ShrAndField::get() const
{
	return (m_value >> 1) & 1;
}

class Rva006DBB60ShrNAndField
{
public:
	bool get() const;

private:
	char m_lead[0x04];
	unsigned int m_value;
};

bool Rva006DBB60ShrNAndField::get() const
{
	return (m_value >> 4) & 1;
}
