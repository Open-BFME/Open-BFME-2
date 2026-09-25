// cl: /O1 /EHsc /DNDEBUG /MD
// QuotedPrintableToUnicodeString as retail compiled it for BFME 2
// (0x005355F2, 205 bytes): no length cap, plain str() access and an own
// static buffer -- the same BFME2 shape as the Ascii sibling in
// quoted_printable_ascii.cpp. Body adapted from the Zero Hour donor
// (GameEngine/Source/Common/System/QuotedPrintable.cpp); the missing cap
// and the buffer are target facts. Split from quoted_printable.cpp because
// retail built this body with EH (fs:[0] frame) unlike its siblings.

#define MAGIC_CHAR '_'

template <typename T> class StringBase
{
	friend class AsciiString;
	StringBase(const T *text);
	StringBase(const StringBase &);
public:
	~StringBase();
protected:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }
};

// Retail destroys the decoded UnicodeString local with a bare releaseBuffer
// call (0x36E70), not the shared StringBase teardown, so the wide
// instantiation carries an inline-empty base destructor here. The narrow
// instantiation above keeps the undefined destructor so the by-value
// AsciiString parameter still tears down through 0x36410.
template <> class StringBase<unsigned short>
{
	friend class UnicodeString;
	StringBase(const unsigned short *text);
	StringBase(const StringBase &);
public:
	~StringBase() {}
protected:
	void *m_data;
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	void releaseBuffer();
	~UnicodeString() { releaseBuffer(); }
};

// Shared quoted-printable hex helper. Defined static exactly like the Ascii
// sibling TU: MSVC keeps the char in AL and calls out of line, and the gate
// resolves that call to the landed global at 0x0053541C.
static int hexDigitToInt(char c)
{
	if (c <= '9' && c >= '0') return (c - '0');
	if (c <= 'f' && c >= 'a') return (c - 'a' + 10);
	if (c <= 'F' && c >= 'A') return (c - 'A' + 10);
	return 0;
}

// Convert ascii quoted-printable strings into unicode strings
UnicodeString QuotedPrintableToUnicodeString(AsciiString original)
{
	static unsigned short dest[1024];

	unsigned char *c = (unsigned char *)dest;
	const unsigned char *src = (const unsigned char *)original.str();

	while (*src)
	{
		if (*src == MAGIC_CHAR)
		{
			if (src[1] == '\0')
			{
				break;
			}
			*c = hexDigitToInt(src[1]);
			src++;
			if (src[1] != '\0')
			{
				*c = *c<<4;
				*c = *c | hexDigitToInt(src[1]);
				src++;
			}
		}
		else
		{
			*c = *src;
		}
		src++;
		c++;
	}

	// Fixup odd-length strings
	if ((c - (unsigned char *)dest) % 2)
	{
		// OK
	}
	else
	{
		*c = '\0';
		c++;
	}

	*c = 0;

	UnicodeString out(dest);
	return out;
}
