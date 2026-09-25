// cl: /O1 /Oi- /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// INI::getNextQuotedAsciiString (retail 0x002E93F, 272 bytes). BFME2
// adaptation of the Zero Hour donor: reads one (possibly quoted,
// space-spanning) token into a line buffer, then materializes it as the
// returned AsciiString through the rowed StringBase pieces (set 0x55F5,
// copy 0x365F0, dtor 0x36410). Quote spanning calls getNextToken with the
// inline quote seps at INI+0x424; CRT pieces ride their IAT thunks.

typedef int Int;
typedef int Bool;
#define FALSE 0
#define TRUE 1

extern "C" unsigned int __cdecl strlen(const char *string);
extern "C" char *__cdecl _mbscpy(char *dest, const char *source);
extern "C" char *__cdecl _mbscat(char *dest, const char *source);

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
};

class INI
{
public:
	enum { MAX_CHARS_PER_LINE = 1028 };
	const char *getNextTokenOrNull(const char *seps);
	const char *getNextToken(const char *seps);
	const char *getSepsQuote() { return m_sepsQuote; }
	AsciiString getNextQuotedAsciiString();

	char m_unreconstructed_000[0x424];
	const char *m_sepsQuote;
};

AsciiString INI::getNextQuotedAsciiString()
{
	AsciiString result;
	char buff[INI::MAX_CHARS_PER_LINE];
	buff[0] = '\0';

	const char *token = getNextTokenOrNull(0);
	if (token != 0)
	{
		if (token[0] != '\"')
		{
			result.set(token);
		}
		else
		{
			Int strLen = 0;
			Bool done = FALSE;
			if ((strLen = (Int)strlen(token)) > 1)
			{
				_mbscpy(buff, &token[1]);
				if (buff[strLen - 2] == '\"')
				{
					buff[strLen - 2] = '\0';
					done = TRUE;
				}
			}

			if (!done)
			{
				token = getNextToken(getSepsQuote());

				if (strlen(token) > 1 && token[1] != '\t')
				{
					_mbscat(buff, " ");
					_mbscat(buff, token);
				}
				else
				{
					Int buflen = (Int)strlen(buff);
					if (buff[buflen - 1] == '\"')
						buff[buflen - 1] = '\0';
				}
			}
			result.set(buff);
		}
	}
	return result;
}
