// cl: /DNDEBUG /MD
//
// ?rva003FD02E@Rva003FD02E@@QAEHPAD@Z @0x003FD02E 40B:
// vtable slot 2 of table at 0x00837C20; two-call narrow concat write via
// rowed ?write@AsciiStringPlusText@@QAEHPAD@Z @0x000BBD41 and
// ?write@AsciiStringRef@@QAEHPAD@Z @0x0002C5B1; member pointer at [ecx+4]
// holds PlusText at +0 and Ref at +0xC (Rva0020F58E shape); ret 4 one char*
// arg returning total bytes.

class AsciiString;

struct AsciiStringRef
{
	int write(char *dst);

	const AsciiString *m_string;
};

struct Rva000B3F84Pair
{
	const char *m_ptr;
	int m_len;
};

struct AsciiStringPlusText : AsciiStringRef
{
	int write(char *dst);

	Rva000B3F84Pair m_right;
};

struct Rva003FD02ETarget
{
	AsciiStringPlusText m_first;
	AsciiStringRef m_second;
};

class Rva003FD02E
{
public:
	int rva003FD02E(char *dst);

private:
	char m_lead[4];
	Rva003FD02ETarget *m_member;
};

// vtable 0x00837C20#2
int Rva003FD02E::rva003FD02E(char *dst)
{
	Rva003FD02ETarget *target = m_member;
	int n = target->m_first.write(dst);
	return n + target->m_second.write(dst + n);
}
