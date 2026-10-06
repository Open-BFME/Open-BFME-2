// cl: /DNDEBUG /MD /EHsc
// ?rva0039B795@Rva0039B795@@QAEXH@Z @0x0039B795 24B conditional add: when the
// global byte at [0x00DFE78C+0x98] is nonzero add the int arg to +0x08.
// Evidence: sole caller 0x003B0D65; global 0xDFE78C shared with 0x0039B718.

struct Global98Flag
{
	char m_pad00[0x98];
	unsigned char m_flag98;
};

class GameLogic;
extern class GameLogic *TheGameLogic;

#define Global98Ptr (*(Global98Flag *const *)&TheGameLogic)

class Rva0039B795
{
public:
	void rva0039B795(int delta);
	void rva0039B7CB(int delta);
	void rva0039B7E3(int delta);

private:
	char m_pad00[0x8];
	int m_val08;
	int m_val0C;
	int m_val10;
};

void Rva0039B795::rva0039B795(int delta)
{
	if (Global98Ptr->m_flag98 == 0)
		return;
	m_val08 += delta;
}

// ?rva0039B7CB@Rva0039B795@@QAEXH@Z @0x0039B7CB 24B same conditional add to
// +0x0C. Evidence: sole caller 0x0023D878; same global flag and class layout.
void Rva0039B795::rva0039B7CB(int delta)
{
	if (Global98Ptr->m_flag98 == 0)
		return;
	m_val0C += delta;
}

// ?rva0039B7E3@Rva0039B795@@QAEXH@Z @0x0039B7E3 24B same conditional add to
// +0x10. Evidence: sole caller 0x0023D86E; same global flag and class layout.
void Rva0039B795::rva0039B7E3(int delta)
{
	if (Global98Ptr->m_flag98 == 0)
		return;
	m_val10 += delta;
}

// ?rva0039B7AD@Rva0039B7AD@@QAEXH@Z @0x0039B7AD 30B conditional double add: when
// the same global byte is nonzero add the int arg to +0x04 and +0x114.
// Evidence: sole caller 0x003B0E23 passes ecx from [ebp+0xC] with delta edi.
class Rva0039B7AD
{
public:
	void rva0039B7AD(int delta);

private:
	char m_pad00[0x4];
	int m_val04;
	char m_pad08[0x10C];
	int m_val114;
};

void Rva0039B7AD::rva0039B7AD(int delta)
{
	if (Global98Ptr->m_flag98 == 0)
		return;
	m_val04 += delta;
	m_val114 += delta;
}
