// cl: /O1 /MD /DNDEBUG /EHsc /arch:SSE
//
// ??0AttackNugget@@QAE@XZ, retail 0x001F05C1 (69 bytes). EH nugget ctor over
// a trivially-constructed base with a declared virtual dtor (its unwind
// state 0 covers the member-constructing call): the compiler installs vtable
// 0x00BE0FF4 between the state store plus member lea and the +0x04 member
// construction through the pinned RadiusDecalTemplate ctor at 0x00330E5D,
// then the body zeroes the +0x40 word and the +0x38 float slot and sets the
// +0x3C word. Donor: BFME1 RadiusDecal.h (member class with AsciiString
// members per the callee pin; the pin spelling resolves the call). Identity
// is the Attack OCL keyword parse at 0x001F0D96 calling this out-of-line
// ctor (superseded pin note).

class NuggetBase
{
public:
	virtual ~NuggetBase();
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();

private:
	unsigned char m_opaque[0x34];
};

class AttackNugget : public NuggetBase
{
public:
	AttackNugget();
	virtual ~AttackNugget();

private:
	RadiusDecalTemplate m_member04;	// +0x04
	float m_float38;	// +0x38
	int m_int3C;	// +0x3C
	int m_int40;	// +0x40
};

AttackNugget::AttackNugget()
{
	m_float38 = 0.0f;
	m_int3C = 1;
	m_int40 = 0;
}
