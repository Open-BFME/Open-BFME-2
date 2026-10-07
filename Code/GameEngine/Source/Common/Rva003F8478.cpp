// cl: /O1 /MD
//
// ?rva003F8478@Rva003F8052@@QAEEXZ @0x003F8478 31B.
// If rowed 0x003F802B (same this) is true return 0, else negate rva003F8052.
// Evidence: retail call 802B / test al,al / je else / xor al,al+ret;
// else: call 8052 (pinned, banked near-miss) / neg al + sbb al,al + inc al;
// 8052 is declared E here so the ! stays byte-wide (neg al).
class Rva003F802B
{
public:
	bool rva003F802B();
};

class Rva003F8052
{
public:
	unsigned char rva003F8052();
	unsigned char rva003F8478();
private:
	char m_pad00[8];
	int m_08;
	int m_0C;
};

unsigned char Rva003F8052::rva003F8478()
{
	if (((Rva003F802B *)this)->rva003F802B())
		return 0;
	return !((Rva003F8052 *)this)->rva003F8052();
}
