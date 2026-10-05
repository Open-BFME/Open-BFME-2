// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva00401FAF@Rva00401FAF@@QAEXPBUTreeHintOpaque0043671B@@@Z @0x00401FAF 141B: holder at +0x8C flag +0xC8 ptr to TreeHintOpaque0043671B size 0xDF4; new via 0x0002FDA0 ctor 0x00229811 assign 0x00401F76; callers 0x0043E787 0x0043E8DF.
struct TreeHintOpaque0043671B
{
	char m_pad00[0xDEC];
	unsigned int m_wordDEC;
	unsigned int m_wordDF0;
	TreeHintOpaque0043671B();
	TreeHintOpaque0043671B &operator=(const TreeHintOpaque0043671B &other);
};

struct Rva00401FAF
{
	char m_pad00[0x8C];
	unsigned char m_flag;
	char m_pad8D[0x3B];
	TreeHintOpaque0043671B *m_ptr;
	void rva00401FAF(const TreeHintOpaque0043671B *p);
};

void Rva00401FAF::rva00401FAF(const TreeHintOpaque0043671B *p)
{
	if (p) {
		if (!m_ptr)
			m_ptr = new TreeHintOpaque0043671B;
		*m_ptr = *p;
		m_ptr->m_wordDEC = 0;
		m_ptr->m_wordDF0 = 0;
		m_flag = 1;
	} else {
		m_flag = 0;
	}
}
