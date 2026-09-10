// cl: /O1 /DNDEBUG /MD
//
// ModuleFactory::makeDecoratedNameKey, retail 0x00255C5E, 74 bytes.
// Dedicated TU. Prefixes the AsciiString text with '0'+type then nameToKey.

#include <string.h>
#pragma function(strcpy)

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum ModuleType
{
	MODULETYPE_FIRST = 0
};

class AsciiString
{
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		char text[1];
	};
	Header *m_data;

public:
	const char *str() const { return m_data ? m_data->text : ""; }
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
};

NameKeyGenerator *TheNameKeyGenerator;

class ModuleFactory
{
protected:
	static NameKeyType makeDecoratedNameKey(const AsciiString &name, ModuleType type);
};

NameKeyType ModuleFactory::makeDecoratedNameKey(const AsciiString &name, ModuleType type)
{
	char tmp[256];
	tmp[0] = (char)('0' + (int)type);
	strcpy(&tmp[1], name.str());
	return TheNameKeyGenerator->nameToKey(tmp);
}
