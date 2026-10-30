// cl: /Ireference/shims/ini_bfme2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// ?Rva00320158Parse@@YAXPAVINI@@PAVRva003200BC@@@Z, retail 0x00320158, 81 bytes.
// ControlBar factory (chain: calls 0x0031F7AB now ready). Evidence: news 0x1C
// via rowed ??2@YAPAXI@Z then rowed ??0Rva0031F7AB@@QAE@XZ; rowed
// ?initFromINI@INI@@QAEXPAXPBUFieldParse@@@Z with table 0x0080D720; rowed
// ?addImage@Rva003200BC@@QAEXH@Z with new object; prev/next
// ControlBarList003200A2/ControlBarScheme share class and flags. Honest
// free-function name (no proven class): Rva00320158 + Parse.

class INI;
typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);
struct FieldParse
{
public:
	const char *token; // +0x00
	INIFieldParseProc parse; // +0x04
	const void *userData; // +0x08
	int offset; // +0x0C
};

class Xfer;
class AsciiString;
enum INILoadType { INI_LOAD_INVALID = 0, INI_LOAD_OVERWRITE = 1, INI_LOAD_CREATE_OVERRIDES = 2 };
class INI {
public:
	INI();
	~INI();
	void load(AsciiString filename, int loadType, int reload, void* xfer);
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer* xfer);
	bool loadDirectory(AsciiString dirpath, bool recursive, INILoadType loadType, Xfer* xfer, int extra);
	static bool loadSubsystemFiles(const char* subsystem, void* xfer);
	const char* getNextToken(const char* seps = 0);
	void initFromINI(void* what, const struct FieldParse* parseTable);
	const char* getNextTokenOrNull(const char* seps = 0);
	static float scanReal(const char* token);
	static int scanInt(const char* token);
	static int scanBool(const char* token);
	static int scanIndexList(const char* token, const char* const* names);
	static void parseAsciiString(INI* ini, void* instance, void* store, const void* userData);
	static void parseAsciiStringVectorAppend(INI* ini, void* instance, void* store, const void* userData);
	static void parseLookupList(INI* ini, void* instance, void* store, const void* userData);
	static void parseICoord2D(INI *ini, void *instance, void *store, const void *userData);
	static void parseMappedImage(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
private:
	char m_unported[0x87C];
};

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"
class Rva0031F7AB
{
public:
	Rva0031F7AB();
private:
	AsciiString m_str; // +0x00
	int m_a; // +0x04
	int m_b; // +0x08
	int m_c; // +0x0C
	int m_d; // +0x10
	int m_e; // +0x14
	int m_f; // +0x18
};

class Rva003200BC
{
public:
	void addImage(int value);
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
	holder->addImage((int)obj);
}
