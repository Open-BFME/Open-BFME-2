// ?finish@XmlNameSlotList@@QAEHXZ
// partial score=0.8 date=2026-10-06
// cl: /O1 /arch:SSE /G7 /MD
//
// ?finish@XmlNameSlotList@@QAEHXZ @0x00542890 121B: the markup lexer's
// advance to the next element (the BfmeLexEAN object of BfmeConv2008.cpp,
// named XmlNameSlotList by the three matched Lua token parsers that call
// it). A pending "/>" closes the element (2); otherwise the text is
// flushed and whitespace and <!-- --> comments are skipped. At the end of
// the text the tail and mark reset and 0 is returned; at '<' the element
// scanner takes over, anything else is character data. Callees are the
// lexer's own rowed methods.

class BfmeLexEAN
{
public:
	int bfmeScanEAN();							// 0x00542791, character data
	int bfmeFailEAN(int code);					// 0x00542459
};

class Rva005423F0
{
public:
	char *rva005423F0(char *text);				// 0x005423F0, skip whitespace
};

class Rva005427F1
{
public:
	void rva005427F1();							// 0x005427F1, flush pending text
};

class Rva0054273B
{
public:
	bool rva0054273B();							// 0x0054273B, skip a comment
};

class Rva005424C4
{
public:
	int rva005424C4();							// 0x005424C4, scan an element
};

class XmlNameSlotList
{
public:
	int finish();

private:
	char *m_pos;								// +0x00
	char m_pad04[0x0C];
	bool m_inTag;								// +0x10
	char m_pad11[0x0B];
	char *m_tail;								// +0x1C
	char m_pad20[0x08];
	int m_mark;									// +0x28
};

int XmlNameSlotList::finish()
{
	if (m_inTag && *m_pos == '/') {
		++m_pos;
		if (*m_pos != '>')
			return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
		++m_pos;
		return 2;
	}
	((Rva005427F1 *)this)->rva005427F1();
	if (m_pos == 0)
		return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
	for (m_pos = ((Rva005423F0 *)this)->rva005423F0(m_pos); *m_pos != 0;
		m_pos = ((Rva005423F0 *)this)->rva005423F0(m_pos)) {
		if (*m_pos != '<')
			return ((BfmeLexEAN *)this)->bfmeScanEAN();
		if (m_pos[1] != '!')
			return ((Rva005424C4 *)this)->rva005424C4();
		if (!((Rva0054273B *)this)->rva0054273B())
			return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
	}
	m_tail = 0;
	m_mark = 0;
	return 0;
}
