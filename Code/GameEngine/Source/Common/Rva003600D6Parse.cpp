// cl: /MD /EHsc
// ?Rva003600D6Parse@@YAXPAVINI@@PAVRva003600D6Holder@@@Z @ 0x003600D6 87B: factory news 0x40,
// calls ctor ??0Rva0035FF76 at 0x0036006F, parses table 0x00816738 via rowed
// INI::initFromINI 0x0002DE78, copies m_endFrame to m_frameLength, stores via
// holder+0x10 setter pinned at 0x005F69CE. Chain from 0x0036006F; same 87B shape
// as 0x0035F6E2. Opaque address-derived names; layout from Rva0035FF76Ctor.cpp.
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
	static void parseRGBColor(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00C16738 (.rdata): three field records and a zero sentinel.
// The sentinel ends at VA 0x00C16778, where the independently referenced
// _bfmeVftSF table begins. Target entries use rowed INI parsers and the
// Rva0035FF76 field offsets established by its constructor.
extern const FieldParse g_00C16738[] = {
	{ "StartFrame", &INI::parseInt, 0, 0x10 },
	{ "EndFrame", &INI::parseInt, 0, 0x14 },
	{ "FadeColor", &INI::parseRGBColor, 0, 0x30 },
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

class Rva0035FF76 : public Rva001DBAA4
{
public:
	virtual ~Rva0035FF76();
	virtual void init(void *win);
	virtual void update(int frame);
	virtual void reverse();
	virtual void draw();
	virtual void skip();
	virtual bool isFinished();
	virtual int getFrameLength();
	Rva0035FF76();
	int m_startFrame;
	int m_endFrame;
	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;
	float m_percent;
	int m_drawState;
	float m_fadeRed;
	float m_fadeGreen;
	float m_fadeBlue;
	unsigned char m_red;
	unsigned char m_green;
	unsigned char m_blue;
};

typedef char Rva0035FF76SizeMatchesRetail[(sizeof(Rva0035FF76) == 0x40) ? 1 : -1];

class Rva003600D6Holder
{
public:
	void set(Rva0035FF76 *obj);
};

void __cdecl Rva003600D6Parse(INI *ini, Rva003600D6Holder *holder)
{
	Rva0035FF76 *obj = new Rva0035FF76;
	ini->initFromINI(obj, g_00C16738);
	obj->m_frameLength = obj->m_endFrame;
	holder->set(obj);
}
