// cl: /MD /EHsc
//
// ??1Rva005997CD@@QAE@XZ retail 0x005997CD 88B.
// Evidence: the body clears the list-like members at +0 and +4 through the
// folded _List_base clear at 0x0023DAA5, then unwind states 2..0 tear down
// the string at +8 through the folded string dtor 0x00036410 and the two
// lists through the folded _List_base dtor 0x004EC395. Names are generated;
// only the destructible members and their offsets are attested.

class Rva0023DAA5List
{
public:
	~Rva0023DAA5List();
	void clear();
private:
	void *m_node;
};

class AsciiStringMember
{
public:
	~AsciiStringMember();
private:
	void *m_data;
};

class Rva005997CD
{
public:
	~Rva005997CD();
private:
	Rva0023DAA5List m_at00;
	Rva0023DAA5List m_at04;
	AsciiStringMember m_at08;
};

Rva005997CD::~Rva005997CD()
{
	m_at00.clear();
	m_at04.clear();
}
