// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?rva0030D773@Rva0030D773@@QAEXH@Z, retail 0x0030D773, 149B.
// MapObject-style setter: Dict at +0x24 via rowed setInt 0x00313716 with key
// from rowed NameKey cache get 0x00148F5E on g_00DBDC84, template pointer at
// +0x18 via rowed rva002D06CA 0x002D06CA on g_00DFF000 with WallHubTemplate
// vs ExpansionLocatorTemplate AsciiString temps. Callers: 0x0030DA25.
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

extern Rva00148F5ECache g_00DBDC84;

class Dict
{
public:
	void setInt(int key, int value);
private:
	void *m_data;
};

class ThingTemplate;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &key);
};

extern class ThingFactory *TheThingFactory;

class Rva0030D773
{
public:
	void rva0030D773(int val);
private:
	char m_pad0[0x18];
	void *m_thing;
	char m_pad1[0x24 - 0x18 - 4];
	Dict m_dict;
};

void Rva0030D773::rva0030D773(int val)
{
	m_dict.setInt(g_00DBDC84.get(), val);
	switch (val)
	{
	case 0:
		{
			AsciiString tmp("WallHubTemplate");
			m_thing = (void *)TheThingFactory->findTemplate(tmp);
		}
		break;
	case 1:
		{
			AsciiString tmp("ExpansionLocatorTemplate");
			m_thing = (void *)TheThingFactory->findTemplate(tmp);
		}
		break;
	}
}

