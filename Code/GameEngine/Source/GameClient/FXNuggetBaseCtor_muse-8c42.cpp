// cl: /DNDEBUG /MD /EHsc
// ??0Rva001DFEAABase@@QAE@XZ @0x001DFEAA 117B
// FXNugget-family shared base ctor. Donor: BFME1 FXNugget ctor
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/FXNuggetConstructor.cpp)
// with BFME2 drift: four 76-byte members at +0x10/+0x5C/+0xA8/+0xF4 (Rva0042526Member 0x4C memset)
// two 4-byte filters at +0x08/+0x0C (Rva003623E5Member) trailing +0x140=2 +0x144=0
// vtable 0x00BDC940 callers 13 matched FXNugget ctors (EvaEvent 0x001DFFFA Sound 0x001E00A6 etc).
class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
private:
	int m_val;
};

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
private:
	int m_val;
};

class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
	virtual ~Rva001DFEAABase();
private:
	int m_field04; // +0x04
	Rva003623E5Member m_filter08; // +0x08
	Rva003623E5Filter m_filter0C; // +0x0C
	Rva0042526Member m_mask10; // +0x10
	Rva0042526Member m_mask5C; // +0x5C
	Rva0042526Member m_maskA8; // +0xA8
	Rva0042526Member m_maskF4; // +0xF4
	int m_140; // +0x140
	bool m_144; // +0x144
};

Rva001DFEAABase::Rva001DFEAABase()
{
	m_field04 = 0;
	m_140 = 2;
	m_144 = false;
}
