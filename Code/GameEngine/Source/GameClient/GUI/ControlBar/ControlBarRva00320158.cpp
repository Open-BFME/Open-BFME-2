// cl: /Ireference/shims/ini_bfme2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// ?Rva00320158Parse@@YAXPAVINI@@PAVRva003200BC@@@Z, retail 0x00320158, 81 bytes.
// ControlBar factory (chain: calls 0x0031F7AB now ready). Evidence: news 0x1C
// via rowed ??2@YAPAXI@Z then rowed ??0Rva0031F7AB@@QAE@XZ; rowed
// ?initFromINI@INI@@QAEXPAXPBUFieldParse@@@Z with table 0x0080D720; rowed
// ?rva003200BC@Rva003200BC@@QAEXH@Z with new object; prev/next
// ControlBarList003200A2/ControlBarScheme share class and flags. Honest
// free-function name (no proven class): Rva00320158 + Parse.

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
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseICoord2D(INI *ini, void *instance, void *store, const void *userData);
	static void parseMappedImage(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
};

class Rva0031F7AB
{
public:
	Rva0031F7AB();
private:
	char m_pad[0x1C]; // +0x00..+0x1C: sizeof 0x1C from retail push 0x1C
};

class Rva003200BC
{
public:
	void rva003200BC(int value);
};

// Matched consumers place this table at VA 0x00C0D720 (.rdata). Retail has
// four records and a zero sentinel; the next token, "FinalPos", begins at
// VA 0x00C0D770. The callbacks are rowed INI parsers and the offsets fit the
// 0x1C-byte Rva0031F7AB object.
extern const FieldParse g_0080D720[] = {
	{ "Position", &INI::parseICoord2D, 0, 0x04 },
	{ "Size", &INI::parseICoord2D, 0, 0x0C },
	{ "ImageName", &INI::parseMappedImage, 0, 0x14 },
	{ "Layer", &INI::parseInt, 0, 0x18 },
	{ 0, 0, 0, 0 }
};

// Rva0031FA40Create declared the same target as one FieldParse, producing a
// different COFF decoration. Bind that spelling to the single array above.
#pragma comment(linker, "/alternatename:?g_0080D720@@3UFieldParse@@B=?g_0080D720@@3QBUFieldParse@@B")

void Rva00320158Parse(INI *ini, Rva003200BC *holder)
{
	Rva0031F7AB *obj = new Rva0031F7AB;
	ini->initFromINI(obj, g_0080D720);
	holder->rva003200BC((int)obj);
}
