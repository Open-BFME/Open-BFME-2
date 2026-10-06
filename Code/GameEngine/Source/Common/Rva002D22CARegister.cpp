// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?rva002D23ED@Rva002D22CA@@QAEXPAXH@Z
// RVA 0x002D23ED size 106. Table-register helper of Rva002D22CA: converts each
// entry's name to a NameKey via TheNameKeyGenerator and stores the table
// pointer into the +0x0C array at the given index. Evidence: caller 0x002D2457
// is vtable slot 1 of Rva002D22CA (vtable 0x00802A20) passing the same ecx;
// callee rows 0x00037BA0 StringBase<char> ctor, 0x0009FA65 nameToKey AsciiString,
// 0x00036410 releaseBuffer; global 0x00DF36A4 is TheNameKeyGenerator; ctor
// zeroes 48B tail at +0x0C (12 table slots, indices 0-11 seen in callers).

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "ascii_string.h"


class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase();
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

class Rva002D22CA : public GameEngineDeletingBase
{
public:
	void rva002D23ED(void *table, int index);

private:
	void *m_tables[12];
};

void Rva002D22CA::rva002D23ED(void *table, int index)
{
	if (table != 0)
	{
		for (int *namePtr = (int *)table + 1; *namePtr != 0; namePtr += 3)
		{
			AsciiString tmp((const char *)*namePtr);
			*(namePtr - 1) = (int)TheNameKeyGenerator->nameToKey(tmp);
		}
		m_tables[index] = table;
	}
}
