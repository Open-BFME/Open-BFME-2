// cl: /O1 /MD /EHsc
// ?Rva00360298Parse@@YAXPAVINI@@PAVRva00360298Holder@@@Z @ 0x00360298 87B: the
// cross-fade transition factory, same 87-byte shape as 0x003600D6: new 0x38,
// constructor ??0Rva00360243 (0x00360243, rowed), INI::initFromINI over the
// table at VA 0x00C167B8, frame length copied from the end frame, stored
// through the holder+0x10 setter at 0x005F69CE (ICF twin, pinned). The
// table's tokens FadeImage/CrossFadeImage (parseMappedImage at +0x30/+0x34)
// and StartFrame/EndFrame (parseInt at +0x10/+0x14) are read from retail;
// the draw body over those fields is 0x003602EF (Rva003602EFCrossFade.cpp).
class INI;
typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseMappedImage(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00C167B8 (.rdata): four field records and a zero sentinel.
extern const FieldParse g_00C167B8[] = {
	{ "FadeImage", &INI::parseMappedImage, 0, 0x30 },
	{ "CrossFadeImage", &INI::parseMappedImage, 0, 0x34 },
	{ "StartFrame", &INI::parseInt, 0, 0x10 },
	{ "EndFrame", &INI::parseInt, 0, 0x14 },
	{ 0, 0, 0, 0 }
};

class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	int m_frameLength;
	bool m_isFinished;
	bool m_isForward;
	bool m_isReversed;
	void *m_win;
};

class Image;
class Rva00360243 : public Rva001DBAA4
{
public:
	virtual ~Rva00360243();
	Rva00360243();
	int m_startFrame;		// +0x10
	int m_endFrame;			// +0x14
	char m_pad18[0x30 - 0x18];
	Image *m_fadeImage;		// +0x30
	Image *m_crossFadeImage;	// +0x34
};

typedef char Rva00360243SizeMatchesRetail[(sizeof(Rva00360243) == 0x38) ? 1 : -1];

class Rva00360298Holder
{
public:
	void set(Rva00360243 *obj);
};

void __cdecl Rva00360298Parse(INI *ini, Rva00360298Holder *holder)
{
	Rva00360243 *obj = new Rva00360243;
	ini->initFromINI(obj, g_00C167B8);
	obj->m_frameLength = obj->m_endFrame;
	holder->set(obj);
}
