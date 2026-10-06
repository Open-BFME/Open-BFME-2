// cl: /DNDEBUG /MD /GX-
// ??0Rva004382FC@@QAE@XZ, retail 0x004382FC, 32 bytes.
// Wrapper ctor with Rva002542F3Member at +0 (rowed 0x002542F3, size 0xB8)
// then int 0 at +0xB8/+0xBC and byte 0 at +0xC0. Caller 0x0043A004.
// Member layout and size per Rva002542F3MemberCtor.cpp (InvisibilityNugget
// at +0x08/0x7C, wrapper at +0). No donor: honest address name.
class Rva00438758Interface;

class Rva002542F3Member
{
public:
	Rva002542F3Member();
	Rva002542F3Member(const Rva002542F3Member &other);
	void rva00438592(Rva00438758Interface *interfaceView);
private:
	char m_pad[0xB8];
};

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;


class Rva004382FC
{
public:
	Rva004382FC();
	Rva004382FC(const Rva002542F3Member &a1, int a2);
	Rva004382FC(const Rva004382FC &other);
	void rva00438758(Rva00438758Interface *interfaceView);
private:
	Rva002542F3Member m_00;
	int m_B8;
	int m_BC;
	unsigned char m_C0;
};

Rva004382FC::Rva004382FC()
{
	m_B8 = 0;
	m_BC = 0;
	m_C0 = 0;
}

Rva004382FC::Rva004382FC(const Rva002542F3Member &a1, int a2)
	: m_00(a1)
	, m_B8((int)TheGameLogic->m_frame)
	, m_BC(a2)
	, m_C0(0)
{
}

Rva004382FC::Rva004382FC(const Rva004382FC &other)
	: m_00(other.m_00)
	, m_B8(other.m_B8)
	, m_BC(other.m_BC)
	, m_C0(other.m_C0)
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0BfmePod196@@QAE@ABU0@@Z=??0Rva004382FC@@QAE@ABV0@@Z")

// The interface slots below are the ones called at byte offsets 0x28, 0x78 and
// 0x90 in the address-derived Rva00438758 method. Its 0xB8-byte prefix and
// trailing fields are supported by Rva002542F3Member's ctor/copy rows and the
// Rva004382FC copy ctor; the interface's semantic type is unresolved.
class Rva00438758Interface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10(void *state) = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30(void *value) = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36(void *value) = 0;
};

void Rva004382FC::rva00438758(Rva00438758Interface *interfaceView)
{
	// Target bytes pass {1, 1} to slot10 then call 0x00438592 before the three
	// output calls. The slot names and interface purpose remain unresolved.
	unsigned char state[2];
	state[0] = 1;
	state[1] = 1;
	interfaceView->slot10(state);
	m_00.rva00438592(interfaceView);
	interfaceView->slot30(&m_B8);
	interfaceView->slot30(&m_BC);
	interfaceView->slot36(&m_C0);
}
