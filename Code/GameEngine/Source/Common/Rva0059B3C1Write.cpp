// cl: /GX-
//
// ?rva0059B3C1@Rva0059B3C1@@QAEHPAD@Z retail 0x0059B3C1 40B.
// Two-part write: Rva0059B3E9 block at +0 then AsciiStringRef at +0x14,
// each via rowed write 0x0059B3E9 0x0002C5B1, sum lengths, ret 4.
// Evidence: retail push ebx frame lea ecx [esi+0x14] calls; callers none;
// chain from 0x0059B3E9 in Code/GameEngine/Source/Common/Rva0059B3E9Write.cpp.
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

struct Rva0059B3C1Inner
{
	Rva0059B3E9 m_head;
	AsciiStringRef m_tail;
};

class Rva0059B3C1
{
public:
	int rva0059B3C1(char *dst);
private:
	int m_pad0;
	Rva0059B3C1Inner *m_inner;
};

int Rva0059B3C1::rva0059B3C1(char *dst)
{
	Rva0059B3C1Inner *inner = m_inner;
	int n1 = inner->m_head.rva0059B3E9(dst);
	int n2 = inner->m_tail.write(dst + n1);
	return n1 + n2;
}
