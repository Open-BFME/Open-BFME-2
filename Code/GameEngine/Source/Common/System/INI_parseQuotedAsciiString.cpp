// cl: /O1 /DNDEBUG /MD /EHsc
// INI::parseQuotedAsciiString (retail 0x002F15A, 60 bytes). Zero Hour donor
// served from INI.cpp: assigns one quoted token into the store through the
// rowed getNextQuotedAsciiString at 0x002E93F and the rowed AsciiString
// operator= at 0x00366F0. Shared by the FontName table entry (and other
// single-string slots); the store is a bare AsciiString.

typedef int Int;
typedef int Bool;

template <typename T> struct BfmeStringData;

template <typename T> class StringBase
{
	friend class AsciiString;
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();

public:
	StringBase() : m_data(0) {}
	~StringBase();
	void set(const T *text);

protected:
	BfmeStringData<T> *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString &operator=(const AsciiString &other);
};

class INI
{
public:
	AsciiString getNextQuotedAsciiString();
	static void parseQuotedAsciiString(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseQuotedAsciiString@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseQuotedAsciiString(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	AsciiString *text = (AsciiString *)store;
	*text = ini->getNextQuotedAsciiString();
}
