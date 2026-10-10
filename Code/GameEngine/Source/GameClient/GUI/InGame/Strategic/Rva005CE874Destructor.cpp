// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??1Rva005CE874@@UAE@XZ, retail 0x005CE874..0x005CE8C0 (76 bytes, EH). A
// StrategicHUD holder with two bases (the rowed pointer-holder base
// Rva005E67FE at +0, a 4-byte interface at +8 whose own vftable
// 0x00BED658 is stored last) and an owned pointer at +0x1C (rowed clear
// 0x005CE7EA of Rva005CEA51.cpp): the destructor releases the pointer,
// then the interface and the holder base go. Class name address-derived.
class Rva005CEA51
{
public:
	void rva005CE7EA();
private:
	void *m_0;
};

class Rva005E67FE
{
public:
	virtual ~Rva005E67FE();
private:
	int m_04;
};

class Rva005CE874Interface
{
public:
	virtual ~Rva005CE874Interface() {}
};

class Rva005CE874 : public Rva005E67FE, public Rva005CE874Interface
{
public:
	virtual ~Rva005CE874();
private:
	char m_pad0C[0x1C - 0x0C];
	Rva005CEA51 m_1C;
};

Rva005CE874::~Rva005CE874()
{
	m_1C.rva005CE7EA();
}
