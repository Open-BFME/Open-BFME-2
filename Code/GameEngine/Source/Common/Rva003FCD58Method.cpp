// cl: /DNDEBUG /MD /EHsc
// ?rva003FCD58@Rva003FCD58@@QAEXE@Z @0x003FCD58 25B.
// Stored in slot 12 of table 0x00837C68. The host type is address-derived;
// the call to rowed Rva003FB65C::rva003FCCC9 establishes the base method, and
// the +0xAC byte store is target evidence. Base layout is structural inference.

class Rva003FB65C
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	void rva003FCCC9(unsigned char value);
};

class Rva003FCD58 : public Rva003FB65C
{
public:
	virtual void rva003FCD58(unsigned char value);

private:
	char m_pad04[0xAC - 4];
	unsigned char m_stateAC;
};

void Rva003FCD58::rva003FCD58(unsigned char value)
{
	rva003FCCC9(value);
	m_stateAC = value;
}
