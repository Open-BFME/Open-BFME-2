// cl: /O1
// Donor: Open-BFME-1 6d9434269164392c5ba62aaa7c15a86b5b020d76,
// game/GameEngine/Source/Common/Bfme5DictStringPresence.cpp, compiled /O1.
// Target: complete 86B extent at 0x00329EE9. The owner remains unknown; the donor supplies the string/dictionary interpretation. Retail
// independently proves the +4 subobject and null/16-bit length tests.

class Rva00329EE9StringValue
{
public:
	~Rva00329EE9StringValue(void);
	bool isEmpty(void) const throw();

private:
	struct Header
	{
		int references;
		unsigned short length;
	};

	Header *m_header;
};

enum NameKeyType { NAMEKEY_INVALID = 0 };

class Rva00148F5ECache
{
public:
	NameKeyType get(void);
	NameKeyType key;
	const char *name;
};

class Rva00329EE9Dict
{
public:
	Rva00329EE9StringValue getAsciiString(int key, bool *exists) const;
};

// Retail data at VA 0x00DBDE24 is {0, 0x00C09558}; the latter is
// the literal "playerName". The existing SidesList units use this cache.
Rva00148F5ECache g_00DBDE24 = { NAMEKEY_INVALID, "playerName" };

// These opaque donor spellings have the one-pointer string ABI. Each call
// resolves to the already matched worker independently read from retail.
#pragma comment(linker, "/alternatename:?getAsciiString@Rva00329EE9Dict@@QBE?AVRva00329EE9StringValue@@HPA_N@Z=?getAsciiString@Dict@@QBE?AVAsciiString@@HPA_N@Z")
#pragma comment(linker, "/alternatename:?isEmpty@Rva00329EE9StringValue@@QBE_NXZ=?isEmpty@?$StringBase@D@@QBE_NXZ")
#pragma comment(linker, "/alternatename:??1Rva00329EE9StringValue@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class Rva00329EE9
{
public:
	bool rva00329EE9(void) const;

private:
	int m_prefix;
	Rva00329EE9Dict m_dict;
};

// ?rva00329EE9@Rva00329EE9@@QBE_NXZ
bool Rva00329EE9::rva00329EE9(void) const
{
	const Rva00329EE9Dict *dict = &m_dict;
	bool initialized;
	return dict != 0 &&
		dict->getAsciiString(g_00DBDE24.get(), &initialized).isEmpty();
}
