// cl: /O2 /DNDEBUG /MD /GX-
//
// ?Rva006882E0Parse@@YAXPAVINI@@PAX1PBX@Z, retail 0x006882E0 (35B): the
// SubTitleType FieldParse proc (0x00CE43D0) of the subtitle font table at
// 0x00CE43B0; scanIndexList of the next token over the names at 0x00DD9914
// into the int store. Its unit caches the INI pointer in esi (/O2).

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	int scanIndexList(const char *token, const char *const *names);
};

extern const char *g_00DD9914[];

// ?Rva006882E0Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva006882E0Parse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	*(int *)store = ini->scanIndexList(token, g_00DD9914);
}
