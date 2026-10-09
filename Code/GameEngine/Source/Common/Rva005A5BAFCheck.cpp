// cl: -GR- -EHsc-
// The callee 0x005A57BA is a thiscall AptOnlineCustomMatch member taking a
// bool (RET 4; its body reads this +0x4A0 +0x488 ...); this body leaves ECX
// untouched so the receiver passes through.
class AptOnlineCustomMatch
{
public:
	bool rva005A57BA(bool fromInvite);
};

struct Rva005A5BAFClass
{
	char m_0[0x488];
	int m_488;
	char m_48C[0x14];
	unsigned char m_4A0;

	void rva005A5BAF();
};

// ?rva005A5BAF@Rva005A5BAFClass@@QAEXXZ @0x005A5BAF 24B: when m_488 is 0xd,
// clears the m_4A0 flag and joins through 0x005A57BA with true.
void Rva005A5BAFClass::rva005A5BAF()
{
	if (m_488 == 0xd)
	{
		m_4A0 = 0;
		((AptOnlineCustomMatch *)this)->rva005A57BA(true);
	}
}
