// cl: /GX-
//
// ?rva005E36A0@Rva005E36A0@@QAEHPAD@Z retail 0x005E36A0 37B.
// Two-part write: Rva0059B3E9 head at +0 then AsciiStringRef at +0x14,
// each via rowed write 0x0059B3E9 0x0002C5B1, sum lengths, ret 4.
// Evidence: retail mov esi ecx lea ecx [esi+0x14] calls; caller 0x005E36C5;
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

class Rva005E36A0
{
public:
	int rva005E36A0(char *dst);
private:
	Rva0059B3E9 m_head;
	AsciiStringRef m_tail;
};

int Rva005E36A0::rva005E36A0(char *dst)
{
	int n1 = m_head.rva0059B3E9(dst);
	int n2 = m_tail.write(dst + n1);
	return n1 + n2;
}

//
// ?rva005E36C5@Rva005E36C5@@QAEHPAD@Z retail 0x005E36C5 37B.
// Two-part write: Rva005E36A0 head at +0 then Rva000B3F84Pair at +0x18,
// each via rowed write 0x005E36A0 0x000B44F0, sum lengths, ret 4.
// Evidence: retail mov esi ecx lea ecx [esi+0x18] calls; caller 0x005E36EA;
// chain from 0x005E36A0 in this TU.
class Rva005E36C5
{
public:
	int rva005E36C5(char *dst);
private:
	Rva005E36A0 m_head;
	Rva000B3F84Pair m_tail;
};

int Rva005E36C5::rva005E36C5(char *dst)
{
	int n1 = m_head.rva005E36A0(dst);
	int n2 = m_tail.write(dst + n1);
	return n1 + n2;
}
