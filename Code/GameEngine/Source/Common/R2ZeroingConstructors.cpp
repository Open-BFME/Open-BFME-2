// BFME1 byte-identical donor: reference/open-bfme-1/Code/GameEngine/Source/Common/R2ZeroingConstructors.cpp
// Trimmed to the bodies that reproduce game.dat bytes. The donor holds a large
// family of tiny zeroing constructors; only the claimed ones below are carried.
// The R2Data externs are address-derived placeholders (DIR32 sites the patcher
// fills from retail) and carry no type information, per the donor's own notes.

extern "C" const void *const __identifier("??_7Rva004E14E1FlashRecord@@6B@")[];
extern "C" const void *const __identifier("??_7Rva004E18A2@@6B@")[];

class Rva003B7160
{
public:
	void * m_at00;
	int m_at04;
	char m_at08;
	char m_pad09[ 0x3 ];
	int m_at0C;
	Rva003B7160();
};
Rva003B7160::Rva003B7160()
{
	m_at00 = (void *)__identifier("??_7Rva004E14E1FlashRecord@@6B@");
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
}

class Rva0029BC80
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
	char m_at0C;
	Rva0029BC80();
};
Rva0029BC80::Rva0029BC80()
{
	m_at00 = 0;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
}

class Rva000EC1E0
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	char m_at0C;
	Rva000EC1E0();
};
Rva000EC1E0::Rva000EC1E0()
{
	m_at00 = (void *)__identifier("??_7Rva004E18A2@@6B@");
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
}
