// cl: /O1 /DNDEBUG /MD /EHsc
// DefaultMessageFont cluster (retail 0x0022175F, 82 bytes) plus the FontDesc
// helpers it uses: default ctor 27B @0x00376900 and copy assignment 29B
// @0x002216DD. FontDesc layout (AsciiString +0x00, int size +0x04, bool bold
// +0x08) mirrors the rowed GlobalLanguage::parseFontDesc TU at 0x0037691C,
// which abuts the ctor. The ctor initializes { "Arial Unicode MS", 12,
// false } through the rowed StringBase<char> const-char ctor at 0x00037BA0
// (spelled through an inline AsciiString forwarder, W3DTankDrawModuleDataCtor
// precedent). The parser builds a stack FontDesc through that ctor, fills it
// through the rowed parseFontDesc, assigns it through the copy assignment to
// instance+0x18 (slot-reference form so the add lands before the push,
// DefaultOpenAudio precedent), then tears it down through the pinned teardown
// at 0x00036410. Serves the DefaultMessageFont entry of the table at
// 0x7E6CE0 (siblings: DefaultOpenAudio, DefaultMessageColor,
// NotificationType). The struct scope is unproven beyond the shared layout,
// so the helper names stay plain FontDesc without a class claim.

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

protected:
	BfmeStringData<T> *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);
};

struct FontDesc
{
	AsciiString name;
	int size;
	bool bold;

	FontDesc();
	FontDesc &operator=(const FontDesc &other);
};

class INI
{
public:
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0022175F_ParseDefaultMessageFont(INI *ini, void *instance, void *store, const void *userData);
};

class GlobalLanguage
{
public:
	static void parseFontDesc(INI *ini, void *instance, void *store, const void *userData);
};

// ??0FontDesc@@QAE@XZ
FontDesc::FontDesc() : name("Arial Unicode MS"), size(12), bold(false)
{
}

