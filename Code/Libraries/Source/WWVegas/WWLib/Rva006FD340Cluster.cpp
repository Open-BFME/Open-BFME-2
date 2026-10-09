// cl: /DNDEBUG /MD
//
// Actionscript exception reporter and its URL-escape helpers, next to the
// rowed forwarder in Rva006FD060Forward.cpp. Donor is open-bfme-1
// BfmeR1226_bfmeLine1226.cpp (same two warning strings and release sequence);
// the BFME2 body logs through Rva006CC110Log and adds the trailing callback.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class EAStringC
{
	void *m_pData;

public:
	EAStringC();
	~EAStringC();
	EAStringC &clear();
	unsigned int rva006D3750() const;
	const char *rva00620090() const;
	EAStringC &Rva006D50A0Append(const char *text);
	EAStringC &operator=(const EAStringC &other);
	void rva006D3470();
};

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned int n);
};

class BfmeAptValue006DCD20
{
public:
	virtual void slot0();
	virtual void release();
	void rva006DD6C0(EAStringC *out);
};

void __cdecl Rva006CC110Log(int level, const char *fmt, ...);
void __cdecl rva007097B0(void *arg);
unsigned char Rva006FD5B0(char hi, char lo);	// row 0x006FD5B0 (Apt/Rva006FD5B0HexPair.cpp)

class BfmeBufVKG
{
public:
	BfmeBufVKG *bfmeAppendVKG(const char *source, unsigned int limit);
};

class Rva006FD340Object
{
	char m_pad[0x60];
	BfmeAptValue006DCD20 *m_pending;

public:
	void rva006FD340(char *text, void *arg2);
};

// ?rva006FD340@Rva006FD340Object@@QAEXPADPAX@Z @0x006FD340 (171B). Reports a
// pending Actionscript exception: builds the pending value's string, logs both
// warning lines through Rva006CC110Log and releases the pending value, then
// tail-calls the line callback with the second argument.
void Rva006FD340Object::rva006FD340(char *text, void *arg2)
{
	BfmeAptValue006DCD20 *pending = m_pending;
	if (pending != 0)
	{
		EAStringC name;
		pending->rva006DD6C0(&name);
		Rva006CC110Log(3, "<WARNING> Actionscript un-caught exception encountered during \"%s\"\n", text);
		Rva006CC110Log(3, "<WARNING> Actionscript error message: \"%s\"\n", name.rva00620090());
		m_pending->release();
		m_pending = 0;
	}
	rva007097B0(arg2);
}

extern "C" int __cdecl isalnum(int c);
extern "C" int __cdecl sprintf(char *buffer, const char *format, ...);

// ?rva006FD4C0@@YAXPAVEAStringC@@@Z @0x006FD4C0 (233B). URL-escapes a string
// in place: ASCII letters and digits are copied, every other byte becomes
// "%X" of its value. The local is pre-sized to three times the source length
// through the BfmeStrVKK view and appended one piece at a time.
void __cdecl rva006FD4C0(EAStringC *pString)
{
	char cHex[6] = "";
	char cText[2] = "";
	EAStringC result;
	((BfmeStrVKK *)&result)->bfmeTruncVKK(pString->rva006D3750() * 3);
	const char *p = pString->rva00620090();
	cText[1] = 0;
	unsigned char c = *p++;
	while (c != 0)
	{
		if (c < 0x80 && isalnum(c))
		{
			cText[0] = c;
			result.Rva006D50A0Append(cText);
		}
		else
		{
			sprintf(cHex, "%%%X", c);
			result.Rva006D50A0Append(cHex);
		}
		c = *p++;
	}
	*pString = result;
}

// ?rva006FD630@@YAXPAVEAStringC@@@Z @0x006FD630 (199B). Decodes URL escapes
// from a string's buffer into a local, then assigns it back: '+' becomes a
// space, '%XX' becomes the hex byte through rva006FD5B0, and a trailing '%'
// with no pair is kept. The local is pre-sized to the source length through
// the BfmeStrVKK view and appended one byte at a time.
void __cdecl rva006FD630(EAStringC *pString)
{
	char cText[2] = "*";
	EAStringC result;
	((BfmeStrVKK *)&result)->bfmeTruncVKK(pString->rva006D3750());
	const char *p = pString->rva00620090();
	char c = *p++;
	while (c != 0)
	{
		if (c == '+')
			cText[0] = ' ';
		else
		{
			if (c == '%')
			{
				if ((unsigned char)p[0] != 0)
				{
					c = (char)Rva006FD5B0(p[0], p[1]);
					p += 2;
				}
			}
			cText[0] = c;
		}
		result.Rva006D50A0Append(cText);
		c = *p++;
	}
	*pString = result;
}

