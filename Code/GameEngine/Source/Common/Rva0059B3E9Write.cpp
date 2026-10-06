// cl: /GX-
//
// ?rva0059B3E9@Rva0059B3E9@@QAEHPAD@Z retail 0x0059B3E9 55B.
// Three-part write: Pair at +0 then AsciiStringRef at +8 then Pair at +0xC,
// each rowed write 0x000B44F0 0x0002C5B1, sum lengths, ret 4.
// Evidence: retail push ebx frame lea ecx [edi+8] [edi+0xC] calls; callers 0x0059B3C1 0x005E36A0.
class Rva000B3F84Pair
{
public:
	int write(char *dst);
	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	int write(char *dst);
	const void *m_string;
};

class Rva0059B3E9
{
public:
	int rva0059B3E9(char *dst);
private:
	Rva000B3F84Pair m_first;
	AsciiStringRef m_mid;
	Rva000B3F84Pair m_last;
};

int Rva0059B3E9::rva0059B3E9(char *dst)
{
	int n1 = m_first.write(dst);
	int total = n1 + m_mid.write(dst + n1);
	return total + m_last.write(dst + total);
}
