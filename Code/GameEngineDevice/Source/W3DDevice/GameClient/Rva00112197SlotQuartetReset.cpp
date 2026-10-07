// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// FUN_00512197 at 0x00112197, 50 bytes. Its tail jump targets the rowed
// Rva0011216CSlotQuartet::rva00112153; adjacent slot-quartet methods support
// this class relationship, while the reset fields remain unnamed.

typedef int Int;

struct Rva0011216CSlotQuartet
{
	char m_pad00[0x88];
	Int m_one88;
	Int m_one8C;
	Int m_one90;
	Int m_one94;
	char m_pad98[0x30];
	Int m_zeroC8;
	float m_zeroCC;
	char m_padD0[4];

	void rva00112153(void);
	void rva00112197(void);
};

void Rva0011216CSlotQuartet::rva00112197(void)
{
	register float zero = 0.0f;
	register Int one = 1;
	m_one88 = one;
	m_zeroC8 &= 0;
	m_one90 = one;
	m_one8C = one;
	m_one94 = one;
	m_zeroCC = zero;
	rva00112153();
}
