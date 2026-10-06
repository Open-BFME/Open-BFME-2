// cl: /MD
//
// ?rva00362693@Rva00362693@@QAE_NXZ retail 0x00362693 26 bytes. Triple check
// returning true when +0x18 non-null and +4 non-zero and target+0x45 zero.
// Evidence: caller 0x0036277D, unblocks 0x0036276F, no callees.

class Rva00362693
{
public:
	bool rva00362693();
private:
	char m_00[4];
	unsigned char m_04;
	char m_05[0x18 - 0x05];
	void *m_18;
};

struct Rva00362693Target
{
	char m_00[0x45];
	unsigned char m_45;
};

bool Rva00362693::rva00362693()
{
	Rva00362693Target *target = (Rva00362693Target *)m_18;
	return target != 0 && m_04 != 0 && target->m_45 == 0;
}
