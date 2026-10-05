// cl: /O1 /MD
// Dynamic initializer of a file-scope array of three 0x145-byte records
// whose inline constructor clears three bool flags. Target evidence: game.dat's
// __xc_a table points at 0x007AC13C; the body walks 0x00DE44A8 in 0x145-byte
// steps three times, storing false at +0x00, +0x01 and +0x105, and code at
// 0x00091371..0x0009157A reads those same three bytes. The record's other
// bytes are not touched by the initializer and are modelled as padding. The
// owning TU, record type and global name are not established; the RVA names
// stand in for them.
struct Rva007AC13CEntry
{
	bool m_00;
	bool m_01;
	char m_02[0x103];
	bool m_105;
	char m_106[0x3F];

	Rva007AC13CEntry() : m_00( false ), m_01( false ), m_105( false ) {}
};

extern Rva007AC13CEntry g_Va00DE44A8[3];
Rva007AC13CEntry g_Va00DE44A8[3];
