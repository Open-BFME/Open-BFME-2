// cl: /Ireference/shims/ini_bfme2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// ?Rva003201A9Parse@@YAXPAVINI@@PAX@Z, retail 0x003201A9, 92 bytes. ControlBar
// factory sibling of 0x00320158 (chain: calls 0x0031F7EB now ready).
// Evidence: news 0x24 via rowed ??2@YAPAXI@Z then rowed ??0Rva0031F7EB@@QAE@XZ;
// rowed ?initFromINI@INI@@QAEXPAXPBUFieldParse@@@Z with table 0x0080D788;
// rowed ?addAnimation@Rva003200A2@@QAEXH@Z with new object then rowed
// ?addImage@Rva003200BC@@QAEXH@Z with [esi+8]; prev 0x00320158 shares flags.

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
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
class Rva0031F7EB
{
public:
	Rva0031F7EB();
private:
	AsciiString m_str; // +0x00
	int m_a; // +0x04
public:
	int m_b; // +0x08
private:
	int m_c; // +0x0C
	int m_d; // +0x10
	int m_e; // +0x14
	int m_f; // +0x18
	int m_g; // +0x1C
	int m_h; // +0x20
};

class Rva003200A2
{
public:
	void addAnimation(int value);
};

class Rva003200BC
{
public:
	void addImage(int value);
};

struct LookupListRec { const char *name; int value; };
// The retail lookup list at RVA 0x0080D1D8 (1 names and the null terminator).
extern const LookupListRec AnimTypeNames[2] = { { "SLIDE_RIGHT", 0 }, { 0, 0 } };
extern "C" {
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseICoord2D@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva0031FA40Create@@YAXPAVINI@@PAURva0031FA40Out@@@Z")();
}
// The retail table at 0x0080D788: 5 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_0080D788[6] = {
	{ "Name", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x0 },
	{ "Animation", (FieldParseProc)&__identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), AnimTypeNames, 0x4 },
	{ "Duration", (FieldParseProc)&__identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
	{ "FinalPos", (FieldParseProc)&__identifier("?parseICoord2D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ "ImagePart", (FieldParseProc)&__identifier("?Rva0031FA40Create@@YAXPAVINI@@PAURva0031FA40Out@@@Z"), 0, 0x0 },
	{ 0, 0, 0, 0 }
};

void Rva003201A9Parse(INI *ini, void *holder)
{
	Rva0031F7EB *obj = new Rva0031F7EB;
	ini->initFromINI(obj, g_0080D788);
	((Rva003200A2 *)holder)->addAnimation((int)obj);
	((Rva003200BC *)holder)->addImage(obj->m_b);
}
