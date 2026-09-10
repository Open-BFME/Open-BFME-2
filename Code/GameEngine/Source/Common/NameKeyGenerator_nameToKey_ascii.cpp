// cl: /O1 /DNDEBUG /MD
//
// NameKeyGenerator::nameToKey(const AsciiString&), retail 0x0009FA65, 29 bytes.
// Thin wrapper over the landed char* overload at 0x00148E1A. Header text
// lives at +8; empty strings go through the "" literal.

enum NameKeyType
{
	NAMEKEY_INVALID = 0
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
	NameKeyType nameToKey(const AsciiString &nameString);
};

NameKeyType NameKeyGenerator::nameToKey(const AsciiString &nameString)
{
	return nameToKey(nameString.str());
}
