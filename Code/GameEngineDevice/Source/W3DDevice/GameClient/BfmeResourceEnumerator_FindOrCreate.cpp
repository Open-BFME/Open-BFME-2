// cl: /DNDEBUG /MD /EHsc
//
// ?FindOrCreatePrototypeId@BfmeResourceEnumerator@@QAEHPBD@Z,
// retail 0x006205C0, 11 bytes. Dedicated TU.
//
// Forwards through the string-interning name table at +0x1F8 (cf.
// Add_Prototype.cpp view) to NameKeyGenerator::nameToLowercaseKey at
// 0x00620500 (pinned). Retail emits the load plus a tail jump.

enum NameKeyType
{
    NAMEKEY_INVALID = 0,
    NAMEKEY_MAX = 1 << 23,
    FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToLowercaseKey(const char *prototypeName);
};

class BfmeResourceEnumerator
{
public:
	int FindOrCreatePrototypeId(const char *prototypeName);

private:
	unsigned char m_pad[0x1F8];
	NameKeyGenerator *m_nameTable; // +0x1F8
};

// ?FindOrCreatePrototypeId@BfmeResourceEnumerator@@QAEHPBD@Z
int BfmeResourceEnumerator::FindOrCreatePrototypeId(const char *prototypeName)
{
	return m_nameTable->nameToLowercaseKey(prototypeName);
}
