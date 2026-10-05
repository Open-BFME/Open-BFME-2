// cl: /O1 /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseMetaMap@MetaMap@@SAXPAVINI@@@Z, retail 0x001DB5A2, 109 bytes.
// Static INI scanner: tokenize, resolve GameMessage::Type via rowed
// findGameMessageMetaType 0x001DB3FE, throw on MSG_INVALID, fetch-or-create
// via rowed getMetaMapRec 0x001DB537, throw on null, then rowed initFromINI
// with the MetaMap field table. Both throws share one construction tail.
// ZH donor MetaEvent.cpp MetaMap::parseMetaMap body; throw shape follows the
// INI_parseUnsignedShort family (fill helper plus throwinfo anchor).

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *instance, const struct FieldParse *table);
};

struct FieldParse;

class GameMessage
{
public:
	enum Type { MSG_INVALID = 0 };
};

class MetaMapRec;

class MetaMap
{
protected:
	GameMessage::Type findGameMessageMetaType(const char *name);
	MetaMapRec *getMetaMapRec(GameMessage::Type t);
public:
	static void parseMetaMap(INI *ini);
};

extern MetaMap *g_00DFDBF8;
extern const struct FieldParse g_00BDAD98[];

struct INIException
{
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

// Address anchor only: the throw site pushes this object's address as an
// immediate (DIR32, copied from retail's throwinfo at 0x8FE2FC). Content is
// never compared; the real chain lives in the retail image.
struct ParseMetaMapThrowInfoAnchor { int a; int b; int c; int d; };
static const ParseMetaMapThrowInfoAnchor parseMetaMapThrowInfoAnchor = { 0, 0, 0, 0 };

void MetaMap::parseMetaMap(INI *ini)
{
	const char *token = ini->getNextToken(0);
	GameMessage::Type t = g_00DFDBF8->findGameMessageMetaType(token);
	if (t == GameMessage::MSG_INVALID) {
		INIException e(3, "Game message meta type for '%s' not found", token);
		_CxxThrowException(&e, (const _s__ThrowInfo *)&parseMetaMapThrowInfoAnchor); __assume(0);
	}
	MetaMapRec *map = g_00DFDBF8->getMetaMapRec(t);
	if (map == 0) {
		INIException e(3, "Meta map entry for '%s' not found", token);
		_CxxThrowException(&e, (const _s__ThrowInfo *)&parseMetaMapThrowInfoAnchor); __assume(0);
	}
	ini->initFromINI(map, g_00BDAD98);
}
