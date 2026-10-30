// cl: /DNDEBUG /MD
// ??0Rva00332FC1@@QAE@ABVBfmeObject872Header@@0@Z @0x00332FC1 38B
// retail 0x00332FC1 38 bytes: name key at +0 plus two BfmeObject872Header at +4 and +0x14
// LuaScriptEngineParseObjectStatusEvent sets +0 with EventFlagEntry::setKeyFromName.
// Reuse the scripted-event key view and its rowed zero constructor at 0x00326BE6;
// that folded address alone does not identify a string. Payload copy: 0x002CF108.
// sibling of Rva00332F5B same shape different members and offsets

struct Rva00336BE4Key
{
	unsigned key;
	Rva00336BE4Key();
};

class BfmeObject872Header
{
public:
	BfmeObject872Header(const BfmeObject872Header &that);
private:
	char m_data[16];
};

class Rva00332FC1
{
public:
	Rva00332FC1(const BfmeObject872Header &a, const BfmeObject872Header &b);
	bool rva00332FE7(const Rva00332FC1 &other) const;
private:
	Rva00336BE4Key m_key;
	BfmeObject872Header m_a;
	BfmeObject872Header m_b;
};

Rva00332FC1::Rva00332FC1(const BfmeObject872Header &a, const BfmeObject872Header &b) : m_key(), m_a(a), m_b(b)
{
}

bool __cdecl Rva002634E0Equal(const void *a, const void *b);

// WorldBuilder 0xC01880 returns its short-circuit equality result in AL.
// Retail 0x00332FE7 preserves the same bool ABI; all 64 bytes match.
bool Rva00332FC1::rva00332FE7(const Rva00332FC1 &other) const
{
 return m_key.key == other.m_key.key && Rva002634E0Equal(&m_a, &other.m_a) && Rva002634E0Equal(&m_b, &other.m_b);
}
