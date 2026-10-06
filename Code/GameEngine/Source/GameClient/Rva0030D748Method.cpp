// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?rva0030D748@Rva0030D748@@QAE?AVAsciiString@@XZ, retail 0x0030D748, 43B.
// MapObject-style AsciiString getter: Dict at +0x24 via rowed getAsciiString
// 0x0031359F with key from rowed NameKey cache get 0x00148F5E on g_00DBDC64.
// Evidence: packet disasm plus Dict at +0x24 shared with 0x0030D773 sibling.
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

extern Rva00148F5ECache g_00DBDC64;

class Dict
{
public:
	AsciiString getAsciiString(int key, bool *exists) const;
private:
	void *m_data;
};

class Rva0030D748
{
public:
	AsciiString rva0030D748();
private:
	char m_pad0[0x24];
	Dict m_dict;
};

AsciiString Rva0030D748::rva0030D748()
{
	return m_dict.getAsciiString(g_00DBDC64.get(), 0);
}
