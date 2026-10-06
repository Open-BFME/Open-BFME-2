// ?rva00293E64@Object@@QAEXPAVDict@@@Z
// partial score=0.99 date=2026-09-30
// cl: /Ireference/shims/bfme2_ascii
// ?rva00293E64@Object@@QAEXPAVDict@@@Z @0x00293E64 155B
// Honest Object method iterating +0x244 array calling virtual 0xB4, then
// optional +0x84 loop, then Dict/NameKey to AsciiString forwarding to rowed
// 0x00293275. Evidence: chain calls rowed 0x00293275, +0x244 null-term array,
// +0x84 Rva00271AEA rowed, Dict getAsciiString rowed, flags /O1 /G7 like sibling.
#include "ascii_string.h"
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	NameKeyType get();
	NameKeyType m_key;
	const char *m_name;
};

// Matched DIR32 witness (w=1) places this 8-byte cache at VA 0x00DBDE14
// (.data). Target get() reads m_key at +0 and m_name at +4; retail starts
// with key 0 and a pointer to the text "objectUpgradesList" at VA 0x00C09528.
// The local literal reproduces pointed-to text only; string-pointer identity
// is not asserted. The next named cache global begins at VA 0x00DBDE24.
extern Rva00148F5ECache g_00DBDE14 = { NAMEKEY_INVALID, "objectUpgradesList" };

class Dict
{
public:
	AsciiString getAsciiString(int index, Bool *exists) const;
};

class Rva00271AEA
{
public:
	void rva00271AEA();
};

class ProviderB4
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s43b();
	virtual void v45(int x);
};

struct Elem244
{
	char m_pad[0x0C];
	ProviderB4 m_obj;
};

class Object
{
public:
	void rva00293E64(Dict *d);
	void rva00293275(AsciiString upgrades);
private:
	char m_pad[4];
	void *m_pad04;
	char m_pad08[0x84 - 0x08];
	Rva00271AEA *m_84;
	char m_pad88[0x244 - 0x88];
	Elem244 **m_244;
};

void Object::rva00293E64(Dict *d)
{
	for (Elem244 **p = m_244; *p != 0; p++) {
		(*p)->m_obj.v45((int)d);
	}
	if (m_84 != 0)
		m_84->rva00271AEA();
	if (d == 0)
		return;
	Bool exists;
	AsciiString s = d->getAsciiString((int)g_00DBDE14.get(), &exists);
	if (!exists)
		return;
	rva00293275(s);
}
