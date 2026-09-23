// Dword immediate setters: eleven-byte __thiscall members with one shape:
//
//     mov dword ptr [ecx+<DISP>],<IMM32> / ret
//
// One dword at a fixed displacement from `this` is set to a hardcoded
// immediate and nothing is read back. The imm-form mirror of the byte
// one-setter family (DispByteOneSetters.cpp); the BFME1 Rva00511250DwordSetter
// `apply` pattern, spelled here without parameters since retail cleans none
// (`ret`, not `ret 4`). Only the class names follow this tree's Disp*
// convention (address-derived Rva<addr>DwordImmSetter, identity unrecoverable
// from 11 bytes). Every displacement here is a disp32 (MSVC 7.1 uses disp8
// whenever the offset fits, so every offset is at least 0x80).
// No // cl: line (defaults match the frameless 11-byte shape).
class Rva0023C7B0DwordImmSetter
{
public:
	void apply();

	char m_lead[0x90];
	unsigned int m_value;
};

void Rva0023C7B0DwordImmSetter::apply()
{
	m_value = 7;
}

class Rva002036A9DwordImmSetter
{
public:
	void apply();

	char m_lead[0x1A104];
	unsigned int m_value;
};

void Rva002036A9DwordImmSetter::apply()
{
	m_value = 1;
}

class Rva00444357DwordImmSetter
{
public:
	void apply();

	char m_lead[0x6A4];
	unsigned int m_value;
};

void Rva00444357DwordImmSetter::apply()
{
	m_value = 1;
}

class Rva0065D1B0DwordImmSetter
{
public:
	void apply();

	char m_lead[0x224];
	unsigned int m_value;
};

void Rva0065D1B0DwordImmSetter::apply()
{
	m_value = 0;
}

class Rva0028576DDwordImmSetter
{
public:
	void apply();

	char m_lead[0x9C];
	unsigned int m_value;
};

void Rva0028576DDwordImmSetter::apply()
{
	m_value = 0x006D7B50;
}

class Rva0029A74ADwordImmSetter
{
public:
	void apply();

	char m_lead[0x8B4];
	unsigned int m_value;
};

void Rva0029A74ADwordImmSetter::apply()
{
	m_value = 2;
}
