// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?rva0030D808@Rva0030D808@@QAE?AVAsciiString@@XZ, retail 0x0030D808, 43B.
// MapObject-style AsciiString getter twin of 0x0030D748: Dict at +0x24 via
// rowed getAsciiString 0x0031359F with key from rowed NameKey cache get
// 0x00148F5E on g_00DBDC6C. Evidence: packet disasm plus twin bytes.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	NameKeyType get();
private:
	NameKeyType m_key;
	const char *m_name;
};

extern Rva00148F5ECache g_00DBDC6C;

class Dict
{
public:
	AsciiString getAsciiString(int key, bool *exists) const;
private:
	void *m_data;
};

class Rva0030D808
{
public:
	AsciiString rva0030D808();
private:
	char m_pad0[0x24];
	Dict m_dict;
};

AsciiString Rva0030D808::rva0030D808()
{
	return m_dict.getAsciiString(g_00DBDC6C.get(), 0);
}
