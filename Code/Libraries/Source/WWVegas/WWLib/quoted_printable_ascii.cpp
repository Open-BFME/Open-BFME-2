// cl: /O1 /EHsc /DNDEBUG /MD
// QuotedPrintableToAsciiString as retail compiled it for BFME 2: no length
// cap, plain str() access and an own static buffer. Body from the Zero Hour
// donor (GameEngine/Source/Common/System/QuotedPrintable.cpp); the missing
// cap and buffer are target facts (0x5356BF). Split from quoted_printable.cpp
// because retail built this body with EH (fs:[0] frame) unlike its siblings.

#define MAGIC_CHAR '_'

// Retail's AsciiString(const char *) is the StringBase<char> ctor at 0x37BA0.
template <typename T> class StringBase
{
	friend class AsciiString;
	StringBase(const T *text);

public:
	~StringBase();

protected:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }
};

// convert an ASCII representation of a hex digit into the digit itself
static int hexDigitToInt(char c)
{
	if (c <= '9' && c >= '0') return (c - '0');
	if (c <= 'f' && c >= 'a') return (c - 'a' + 10);
	if (c <= 'F' && c >= 'A') return (c - 'A' + 10);
	return 0;
}

AsciiString QuotedPrintableToAsciiString(AsciiString original)
{
	static unsigned char dest[1024];

	unsigned char *c = dest;
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

	*c = 0;

	return AsciiString((const char *)dest);
}
