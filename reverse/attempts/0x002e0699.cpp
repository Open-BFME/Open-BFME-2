// ?rva002E0699@Rva002E0699@@QAEHXZ
// partial score=0.97 date=2026-10-05
// cl: /O1
// ?rva002E0699@Rva002E0699@@QAEHXZ @0x002E0699 31B switch over +0x44 with tail to Encoding0 slot2
// Returns +0x2B4 when 0, tails to BFME2Encoding0MotionChannel::UnknownSlot2 at +0x4C
// when 1, else 3. Evidence: callers at 0x002BDEC4 0x002BDF54, neighbours share /O1.

class BFME2Encoding0MotionChannel
{
public:
	virtual int UnknownSlot2();
private:
	char m_pad[0x18];
};

class Rva002E0699
{
public:
	int rva002E0699();
private:
	char m_pad00[0x44];
	int m_44;
	char m_pad48[0x4];
	BFME2Encoding0MotionChannel m_4C;
	char m_padAfter[0x2B4 - (0x4C + 0x1C)];
	int m_2B4;
};

// ?rva002E0699@Rva002E0699@@QAEHXZ present-unmatched
int Rva002E0699::rva002E0699()
{
	switch (m_44) {
	case 0:
		return m_2B4;
	case 1:
		return m_4C.BFME2Encoding0MotionChannel::UnknownSlot2();
	default:
		return 3;
	}
}
