// cl: /O1 /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z, retail 0x0033987B, 133 bytes.
// Dedicated TU (same INI parser family as INI_parseFXList.cpp).
//
// Zero Hour's INI::parseAndTranslateLabel (Common/INI/INI.cpp): fetch the
// token's translation from TheGameText (0x00DFF0BC, vtable slot 0x3C) and store
// it. BFME2 turns the missing-label assert into an INIException(3, ...) throw.
// The emptiness test reads the string data header directly: a 16-bit length
// at +4, characters from +8.

template <typename T>
class StringBase
{
	friend class UnicodeString;

public:
	void set(const T *s);

private:
	struct Data
	{
		int m_refCount;
		unsigned short m_length;	// +4
		unsigned short m_pad;
		T m_chars[1];			// +8
	};

	void releaseBuffer();
	Data *m_data;
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	__forceinline ~UnicodeString() { releaseBuffer(); }
	bool isEmpty() const { return m_data == 0 || m_data->m_length == 0; }
	const unsigned short *str() const { return m_data->m_chars; }
};

class GameTextInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);	// +0x3C
};

extern GameTextInterface *TheGameText;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseAndTranslateLabel(INI *ini, void *instance, void *store, const void *userData);
};

class INIException
{
public:
	INIException(int argumentCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();

	char *mFailureMessage;
	int m_argumentCount;
};

// ?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseAndTranslateLabel(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	UnicodeString translated = TheGameText->fetch(token);
	if (translated.isEmpty())
		throw INIException(3, "Label '%s' not found in game text", token);
	((StringBase<unsigned short> *)store)->set(translated.str());
}
