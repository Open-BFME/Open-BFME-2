// cl: /O1 /Oy- /DNDEBUG /MD /GX
//
// Four 30-byte RVO getters sharing the exact shape of the landed
// AsciiString/Stlport RVO getters (e.g. 0x003821B9): prologue
// 55 8B EC 51 83 65 FC 00, add ecx,<off>, push ecx, mov ecx,[ebp+8],
// call <member copy ctor>, mov eax,[ebp+8], leave, ret 4. Each returns
// the member at its offset by value; the member copy-constructs directly
// into the hidden return pointer. Member types are minimal
// address-derived views (copy ctor declared only, pinned to the REL32
// address read from retail); owner/member identity unproven.

class Rva003862EDMember
{
public:
	Rva003862EDMember(const Rva003862EDMember &o);
	~Rva003862EDMember();
};

class Rva003862EDField
{
public:
	Rva003862EDMember get() const;

private:
	char m_pad[0x84];
	Rva003862EDMember m_value; // +0x84
};

// ?get@Rva003862EDField@@QBE?AVRva003862EDMember@@XZ, retail 0x003862ED, 30 bytes.
// Returns +0x84 member by value via the member copy ctor at 0x0038630B.
Rva003862EDMember Rva003862EDField::get() const
{
	return m_value;
}

class Rva00389DF1Member
{
public:
	Rva00389DF1Member(const Rva00389DF1Member &o);
	~Rva00389DF1Member();
};

class Rva00389DF1Field
{
public:
	Rva00389DF1Member get() const;

private:
	char m_pad[0x1B0];
	Rva00389DF1Member m_value; // +0x1B0
};

// ?get@Rva00389DF1Field@@QBE?AVRva00389DF1Member@@XZ, retail 0x00389DF1, 30 bytes.
// Returns +0x1B0 member by value via the member copy ctor at 0x005559FC.
Rva00389DF1Member Rva00389DF1Field::get() const
{
	return m_value;
}

class Rva00389E0FMember
{
public:
	Rva00389E0FMember(const Rva00389E0FMember &o);
	~Rva00389E0FMember();
};

class Rva00389E0FField
{
public:
	Rva00389E0FMember get() const;

private:
	char m_pad[0x340];
	Rva00389E0FMember m_value; // +0x340
};

// ?get@Rva00389E0FField@@QBE?AVRva00389E0FMember@@XZ, retail 0x00389E0F, 30 bytes.
// Returns +0x340 member by value via the member copy ctor at 0x00555616.
Rva00389E0FMember Rva00389E0FField::get() const
{
	return m_value;
}

class Rva00394173Member
{
public:
	Rva00394173Member(const Rva00394173Member &o);
	~Rva00394173Member();
};

class Rva00394173Field
{
public:
	Rva00394173Member get() const;

private:
	char m_pad[0x754];
	Rva00394173Member m_value; // +0x754
};

// ?get@Rva00394173Field@@QBE?AVRva00394173Member@@XZ, retail 0x00394173, 30 bytes.
// Returns +0x754 member by value via the member copy ctor at 0x00332106.
Rva00394173Member Rva00394173Field::get() const
{
	return m_value;
}
