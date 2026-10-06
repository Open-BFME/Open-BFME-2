// cl: /MD
// ?rva00330B2E@Rva00330B2E@@QAEXXZ, retail 0x00330B2E, 19 bytes.
// Thiscall: calls member+8 Rva0030B9CA::rva0030B9CA (rowed 0x30B9CA) then
// tail-jmps own virtual slot12 (0x30). Chain via 0x30B9CA. No donor.
// ?rva00330B41@Rva00330B2E@@QAEXH@Z, retail 0x00330B41, 15 bytes.
// Same class: stores arg at +0x30 (right after 0x28-sized m_08) then calls
// slot12. Caller 0x30817D (jmp). Abuts 0x30B2E (tail jmp ends FF 60 30).
// ?rva0030817A@Rva0030817A@@QAEXH@Z, retail 0x0030817A, 8 bytes.
// Chain: add ecx,0x30 + jmp to Rva00330B2E::rva00330B41. Caller 0x308FDC.
// ?rva003081C7@Rva003081C7@@QAEEXZ, retail 0x003081C7, 24 bytes.
// Null-checked word at +4 of object at +0x80, returns (word > 0).
// Caller 0x308C44. Same page/flags.
struct Rva0030B9CA
{
	void rva0030B9CA();
	char m_pad[0x28 - 1];
};

class Rva00330B2E
{
public:
	virtual void _slot00();
	virtual void _slot01();
	virtual void _slot02();
	virtual void _slot03();
	virtual void _slot04();
	virtual void _slot05();
	virtual void _slot06();
	virtual void _slot07();
	virtual void _slot08();
	virtual void _slot09();
	virtual void _slot10();
	virtual void _slot11();
	virtual void _slot12();
	void rva00330B2E();
	void rva00330B41(int v);
private:
	int m_04;
	Rva0030B9CA m_08;
	int m_30;
};

void Rva00330B2E::rva00330B2E()
{
	m_08.rva0030B9CA();
	_slot12();
}

void Rva00330B2E::rva00330B41(int v)
{
	m_30 = v;
	_slot12();
}

//
// ?rva0030817A@Rva0030817A@@QAEXH@Z retail 0x0030817A 8 bytes.
// Holder+0x30 forwards int arg to Rva00330B2E::rva00330B41 (tail jmp).
class Rva0030817A
{
public:
	void rva0030817A(int v);
private:
	char m_pad00[0x30];
	Rva00330B2E m_30;
};

void Rva0030817A::rva0030817A(int v)
{
	m_30.rva00330B41(v);
}

//
// ?rva003081C7@Rva003081C7@@QAEEXZ retail 0x003081C7 24 bytes.
struct Rva003081C7Aux
{
	char m_pad00[4];
	unsigned short m_word04;
};

class Rva003081C7
{
public:
	unsigned char rva003081C7();
private:
	char m_pad00[0x80];
	Rva003081C7Aux *m_ptr80;
};

unsigned char Rva003081C7::rva003081C7()
{
	int v = m_ptr80 ? m_ptr80->m_word04 : 0;
	return (unsigned char)(v > 0);
}

//
// ?rva003081FB@Rva003081FB@@QAEEXZ retail 0x003081FB 24 bytes.
// Same recipe as 0x81C7 with pointer at +0x8c. Caller 0x6B692.
class Rva003081FB
{
public:
	unsigned char rva003081FB();
private:
	char m_pad00[0x8c];
	Rva003081C7Aux *m_ptr8C;
};

unsigned char Rva003081FB::rva003081FB()
{
	int v = m_ptr8C ? m_ptr8C->m_word04 : 0;
	return (unsigned char)(v > 0);
}

//
// ?rva003081DF@Rva003081DF@@QAEXXZ retail 0x003081DF 28 bytes.
// StringBase at +0x80 set from the empty-string literal at 0x00BBAC1C via
// rowed set 0x000055F5.
// then byte at +0x88 set to 1. Same page/flags as siblings.
template <typename T>
class StringBase
{
public:
	void set(const char *s);
private:
	void *m_data;
};

class Rva003081DF
{
public:
	void rva003081DF();
private:
	char m_pad00[0x80];
	StringBase<char> m_str80;
	char m_pad84[0x88 - 0x84];
	unsigned char m_flag88;
};

void Rva003081DF::rva003081DF()
{
	m_str80.set("");
	m_flag88 = 1;
}
