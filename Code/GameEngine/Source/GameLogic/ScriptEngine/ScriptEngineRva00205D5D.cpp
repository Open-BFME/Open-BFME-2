// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?rva00205D5D@ScriptEngine@@QAEPAURva00205D5DEntry@@ABVAsciiString@@_N@Z, retail 0x00205D5D, 128 bytes.
// ScriptEngine attack-priority-set table: 256 entries of 0x10 at 0x19100 with
// AsciiString at +4, count at 0x1A100. Searches index 1.. for compare==0,
// returns entry start (string-4); else if create and count<0x100 appends via
// AsciiString::operator=, bumps count and returns new entry; else null.
// Evidence: chain caller 0x002061D7 shares this with ScriptEngine::
// AppendDebugMessage (same this) and names the "***Error allocating attack
// priority set" limit; callees are rowed StringBase::compare and pinned
// AsciiString::operator=.
#include "ascii_string.h"
struct Rva00205D5DEntry
{
	int m_00;
	AsciiString m_name;
	int m_08;
	int m_0C;
};
class ScriptEngine
{
public:
	Rva00205D5DEntry *rva00205D5D(const AsciiString &s, bool create);
private:
	char m_pad[0x19100];
	Rva00205D5DEntry m_table[256];
	int m_count;
};

Rva00205D5DEntry *ScriptEngine::rva00205D5D(const AsciiString &s, bool create)
{
	for (int i = 1; i < m_count; ++i)
	{
		if (m_table[i].m_name.compare(s) == 0)
			return &m_table[i];
	}
	if (create && m_count < 0x100)
	{
		m_table[m_count].m_name = s;
		++m_count;
		return &m_table[m_count - 1];
	}
	return 0;
}
