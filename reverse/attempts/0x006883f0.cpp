// ?parseSubtitleLineTable@@YAXPAVINI@@PAM@Z
// partial score=0.35 date=2026-09-24
// Retail 0x006883F0, 340 bytes. The BFME2 beta debug string and the
// SubtitleManager field table identify this as the LineTable parser.
// The field table at data VA 0x00CE4410 stores it under "LineTable" at
// SubtitleManager+0x24; the adjacent SubTitle field uses 0x00688B10.
//
// Target behavior reconstructed from the retail body. The 15-point cap,
// [0,1] range and 0.01875 minimum step are data/branch evidence, not donor
// assumptions.
// cl: /O1 /Oy- /DNDEBUG /MD /EHsc

typedef int Int;
typedef float Real;

class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &);
	~AsciiString();

private:
	void *m_data;
};

class INI
{
public:
	AsciiString getFilename() const;
	Int getLineNum() const;
	const char *getNextToken(const char *separators);
	Real scanReal(const char *token);

private:
	char m_pad000[0x418];
	const char *m_defaultSeparators;
};

class VideoPlayerInterface
{
public:
	virtual ~VideoPlayerInterface();
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void *getVideo(const AsciiString &title) = 0;
};

extern VideoPlayerInterface *TheVideoPlayer;

class INIException
{
public:
	INIException(Int argumentCount, const char *format, ...);
};

// The parser is registered directly in SubtitleManager's FieldParse table.
void parseSubtitleLineTable(INI *ini, Real *values)
{
	void *manager = TheVideoPlayer->getVideo(ini->getFilename());
	if (manager != 0 && values != 0)
	{
		*((unsigned char *)manager + 0x60) = 1;
		Real previous = -3.402823466e+38F;
		Int index = 0;
		while (true)
		{
			const char *token = ini->getNextToken(0);
			Real value = ini->scanReal(token);
			if (value < *(volatile const Real *)0x00BBAEAC ||
				value > *(volatile const Real *)0x00BBB8D8 ||
				value <= previous + *(volatile const Real *)0x00CE4518)
			{
				AsciiString filename = ini->getFilename();
				throw INIException(8,
					"LineTable values must be in the range (0.0 - 1.0) must increase in value. %s line %d",
					*(const char **)&filename, ini->getLineNum());
			}
			values[index] = value;
			previous = value;
			++index;
			if (index > 14)
				return;
		}
	}
	AsciiString filename = ini->getFilename();
	throw INIException(9, "Could not locate SubTitleManager for %s",
		*(const char **)&filename);
}
