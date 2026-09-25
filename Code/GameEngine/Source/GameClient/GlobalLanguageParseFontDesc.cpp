// cl: /O1 /DNDEBUG /MD /EHsc
// GlobalLanguage::parseFontDesc (retail 0x0037691C, 108 bytes). Zero Hour
// donor served from GlobalLanguage.cpp: reads a quoted font name through
// the rowed getNextQuotedAsciiString at 0x002E93F, an int size through the
// rowed scanInt at 0x002ECCF and a bold flag through the rowed scanBool at
// 0x002D14A. Shared by the ~25 font table entries (CopyrightFont,
// MessageFont, ...). FontDesc layout (AsciiString +0x00, int +0x04,
// bool +0x08) falls out of the three stores.

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

struct FontDesc
{
	AsciiString name;
	Int size;
	bool bold;
};

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	AsciiString getNextQuotedAsciiString();
	Int scanInt(const char *token);
	bool scanBool(const char *token);
};

class GlobalLanguage
{
public:
	static void parseFontDesc(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseFontDesc@GlobalLanguage@@SAXPAVINI@@PAX1PBX@Z
void GlobalLanguage::parseFontDesc(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	FontDesc *fontDesc = (FontDesc *)store;
	fontDesc->name = ini->getNextQuotedAsciiString();
	fontDesc->size = ini->scanInt(ini->getNextToken());
	fontDesc->bold = ini->scanBool(ini->getNextToken());
}
