// cl: /O1 /DNDEBUG /MD /EHsc
// Rva000B6E5A_ParseLowercasedString (retail 0x000B6E5A, 68 bytes). Reads one
// AsciiString through the rowed getNextAsciiString at 0x002EA4F, assigns it
// into the store through the rowed operator= at 0x00366F0, then lowercases
// the stored copy in place through the pinned toLower at 0x0036A70. Serves
// the Skeleton table entry (skeleton names are matched lowercased). No
// donor was found for the lowercasing step, so the name stays
// address-derived and descriptive rather than claiming a class.

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
	void toLower();
};

class INI
{
public:
	AsciiString getNextAsciiString();
	static void Rva000B6E5A_ParseLowercasedString(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva000B6E5A_ParseLowercasedString@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva000B6E5A_ParseLowercasedString(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	AsciiString *text = (AsciiString *)store;
	*text = ini->getNextAsciiString();
	text->toLower();
}
