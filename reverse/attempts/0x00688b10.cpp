// ?parseSubtitleText@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.75 date=2026-09-24
// Retail 0x00688B10, 1,578 bytes. The beta error strings identify the
// subtitle label, color, style, alignment, line, and frame checks. Retail's
// SubtitleManager FieldParse table registers this callback under "SubTitle".
// The target calls the already matched SubtitleManager::addSubtitle body.
// cl: /O2 /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned char Bool;
typedef unsigned int UnsignedInt;

class AsciiString
{
public:
	AsciiString();
	~AsciiString();

	void *m_data;
};

class INI
{
public:
	AsciiString getFilename() const;
	Int getLineNum() const;
	const char *getNextTokenOrNull(const char *separators);
	const char *getNextSubToken(const char *expected);
	Int scanInt(const char *token);
	Int scanIndexList(const char *token, const char *const *names);

	char m_pad000[0x418];
	const char *m_colonSeparators;
	const char *m_separators;
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
	INIException(Int code, const char *format, ...);
	INIException(const INIException &other);
private:
	Int m_code;
	const char *m_message;
public:
};

typedef void *(__cdecl *CreateSubtitleEntry)(AsciiString *, Int,
	const AsciiString &, UnsignedInt, Int, Int, Int, Int, Int);
typedef Bool (__cdecl *ResolveSubtitleLabel)(const char *, AsciiString *);

class SubtitleManager
{
public:
	CreateSubtitleEntry m_createEntry;
	ResolveSubtitleLabel m_resolveLabel;

	void addSubtitle(const AsciiString &label, UnsignedInt color, Int style,
		Int alignment, Int line, Int startFrame, Int endFrame);
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

static const char *const subtitleStyles[] = {
	"TRANSPARENT", "TRANSPARENT_FADE", "OUTLINED", "OUTLINED_FADE",
	"SOLID", "SOLID_FADE", 0
};

static const char *const subtitleAlignments[] = {
	"CENTER", "LEFT", "RIGHT", 0
};

// ?parseSubtitleText@@YAXPAVINI@@PAX@Z
void parseSubtitleText(INI *ini, void *instance, void *fieldContext, const void *userData)
{
	AsciiString label;
	SubtitleManager *manager = (SubtitleManager *)TheVideoPlayer->getVideo(ini->getFilename());
	if (manager == 0 || fieldContext == 0)
	{
		AsciiString filename = ini->getFilename();
		throw INIException(9, "Could not locate SubTitleManager for %s", filename.m_data);
	}

	UnsignedInt color = 0;
	Int style = 0x7fffffff;
	Int alignment = 0x7fffffff;
	Int line = 0x7fffffff;
	Int startFrame = 0x7fffffff;
	Int endFrame = 0x7fffffff;
	const char *token = ini->getNextTokenOrNull(ini->m_defaultSeparators);
	while (token != 0)
	{
		if (_strcmpi(token, "Label") == 0 && label.m_data == 0)
		{
			const char *value = ini->getNextTokenOrNull(ini->m_defaultSeparators);
			if (value == 0 || !manager->m_resolveLabel(value, &label))
			{
				AsciiString filename = ini->getFilename();
				throw INIException(8, "Invalid text label while parsing %s on line %d",
					filename.m_data, ini->getLineNum());
			}
		}
		else if (_strcmpi(token, "Color") == 0 && color == 0)
		{
			const char *channels[] = { "R", "G", "B" };
			color = 0;
			for (Int channel = 0; channel < 3; ++channel)
			{
				const char *value = ini->getNextSubToken(channels[channel]);
				Int component = ini->scanInt(value);
				if (component < 0 || component > 255)
				{
					AsciiString filename = ini->getFilename();
					throw INIException(3,
						"color value %s=%i out of range (0..255) in %s on line %d",
						channels[channel], component, filename.m_data, ini->getLineNum());
				}
				color = (color << 8) | component;
			}
			color |= 0xff000000;
		}
		else if (_strcmpi(token, "Style") == 0 && style == 0x7fffffff)
		{
			const char *value = ini->getNextTokenOrNull(ini->m_defaultSeparators);
			if (value == 0)
			{
				AsciiString filename = ini->getFilename();
				throw INIException(8, "Expected subtitle style type not found in %s on line %d",
					filename.m_data, ini->getLineNum());
			}
			style = ini->scanIndexList(value, subtitleStyles);
		}
		else if (_strcmpi(token, "Align") == 0 && alignment == 0x7fffffff)
		{
			const char *value = ini->getNextTokenOrNull(ini->m_defaultSeparators);
			if (value == 0)
			{
				AsciiString filename = ini->getFilename();
				throw INIException(8, "Expected subtitle alignment type not found in %s on line %d",
					filename.m_data, ini->getLineNum());
			}
			alignment = ini->scanIndexList(value, subtitleAlignments);
		}
		else if (_strcmpi(token, "Line") == 0 && line == 0x7fffffff)
		{
			const char *value = ini->getNextTokenOrNull(ini->m_defaultSeparators);
			if (value == 0)
			{
				AsciiString filename = ini->getFilename();
				throw INIException(8,
					"Expected subtitle line value for Line: not found in %s on line %d",
					filename.m_data, ini->getLineNum());
			}
			line = ini->scanInt(value) - 1;
			if (line < 0 || line > 14)
			{
				AsciiString filename = ini->getFilename();
				throw INIException(3,
					"Subtitle Line value %d out of range (%d..%d) in %s on line %d",
					line, 1, 15, filename.m_data, ini->getLineNum());
			}
		}
		else if (_strcmpi(token, "StartFrame") == 0 && startFrame == 0x7fffffff)
		{
			const char *value = ini->getNextTokenOrNull(ini->m_defaultSeparators);
			if (value == 0)
			{
				AsciiString filename = ini->getFilename();
				throw INIException(8,
					"Expected subtitle StartFrame value for StartFrame: not found in %s on line %d",
					filename.m_data, ini->getLineNum());
			}
			startFrame = ini->scanInt(value);
			if (startFrame < 0)
			{
				AsciiString filename = ini->getFilename();
				throw INIException(3,
					"Subtitle StartFrame must be greater than 0 in %s on line %d",
					filename.m_data, ini->getLineNum());
			}
		}
		else if (_strcmpi(token, "EndFrame") == 0 && endFrame == 0x7fffffff)
		{
			const char *value = ini->getNextTokenOrNull(ini->m_defaultSeparators);
			if (value == 0)
			{
				AsciiString filename = ini->getFilename();
				throw INIException(8,
					"Expected subtitle EndFrame value for EndFrame: not found in %s on line %d",
					filename.m_data, ini->getLineNum());
			}
			endFrame = ini->scanInt(value);
			if (endFrame < 0)
			{
				AsciiString filename = ini->getFilename();
				throw INIException(3,
					"Subtitle EndFrame must be greater than 0 in %s on line %d",
					filename.m_data, ini->getLineNum());
			}
		}
		else
		{
			throw INIException(3,
				"bad colon spacing, or unexpected token in TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend");
		}
		token = ini->getNextTokenOrNull(ini->m_defaultSeparators);
	}
	manager->addSubtitle(label, color, style, alignment, line,
		startFrame, endFrame);
}
