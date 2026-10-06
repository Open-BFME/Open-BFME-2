// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?Rva00333BCALog@@YAXPAXPAULuaAr@@@Z @0x00333BCA 263B: lua traceback line printer via rowed lua_getinfo 0x0074D330 plus sprintf IAT plus rowed bfmeLogMsg574 0x00333B36. Evidence: Snl query namewhat/what/short_src/currentline strings callers 0x00333D80 0x003345AA unblocks 0x00333CD1 0x00334587 donor liolib_bfme1.c errorfb.
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buf, const char *fmt, ...);
extern "C" int __cdecl lua_getinfo(void *L, const char *what, void *ar);
void __cdecl bfmeLogMsg574(const char *msg);

struct LuaAr
{
	int m_00;
	int currentline;
	const char *name;
	const char *namewhat;
	int m_10;
	int linedefined;
	const char *what;
	const char *source;
	char short_src[32];
};

void __cdecl Rva00333BCALog(void *L, LuaAr *ar)
{
	char buf[0x78];
	lua_getinfo(L, "Snl", ar);
	switch (*ar->namewhat)
	{
	case 'g':
	case 'l':
		sprintf(buf, "function `%.50s'", ar->name);
		break;
	case 'f':
		sprintf(buf, "method `%.50s'", ar->name);
		break;
	case 't':
		sprintf(buf, "`%.50s' tag method", ar->name);
		break;
	default:
		if (*ar->what == 'm')
			sprintf(buf, "main of %.70s", ar->short_src);
		else if (*ar->what == 'C')
			sprintf(buf, "%.70s", ar->short_src);
		else
			sprintf(buf, "function <%d:%.70s>", ar->linedefined, ar->short_src);
		ar->source = 0;
		break;
	}
	bfmeLogMsg574(buf);
	if (ar->currentline > 0)
	{
		sprintf(buf, " at line %d", ar->currentline);
		bfmeLogMsg574(buf);
	}
	if (ar->source != 0)
	{
		sprintf(buf, " [%.70s]", ar->short_src);
		bfmeLogMsg574(buf);
	}
	bfmeLogMsg574("\012");
}
