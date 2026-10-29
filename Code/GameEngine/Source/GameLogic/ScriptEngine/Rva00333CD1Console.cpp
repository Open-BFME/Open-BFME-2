// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ?Rva00333CD1Console@@YAHPAXPAULuaAr@@@Z
// Lua debug console hook, retail 0x00333CD1, 369 bytes: prompts on the debug
// console, reads lines and answers "cont" (leave debug mode), "step" (stop at the
// next line), "where" (traceback line via 0x00333BCA), "?" (help) and otherwise
// runs the line through the Lua interpreter, until the console reports no input.
// Strings and flow are read from the retail bytes; the console object is the
// ledger's global at 0x00DE0880 (virtual slot 38 reads a line).

// The x86 header keeps strcmp direct while importing strncmp, as retail does.
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP

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
	char short_src[60];
	int i_ci;
};

extern "C" int __cdecl lua_getstack(void *L, int level, LuaAr *ar);
extern "C" int __cdecl lua_dostring(void *L, const char *str);
extern "C" void __cdecl lua_settop(void *L, int idx);
void __cdecl bfmeLogMsg574(const char *msg);
void __cdecl Rva00333BCALog(void *L, LuaAr *ar);

class Debug
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual int readLine(char *buffer, int maxChars, bool *more);
};
extern Debug *theDebug;
// The Lua debugger's active object, retail VA 0x00E01DC0 (RVA 0x00A01DC0): the
// rowed console body clears it and stores the state into it (retail 0x00333E27
// `andl $0x0,0xe01dc0` and 0x00333E3A `mov %edi,0xe01dc0`), and BfmeConv's
// deactivation hook clears it the same way. RVA 0x00A01DC0 is past .data's raw
// end (0x009DE008) but inside its virtual size, so retail's image holds null
// until the debugger parks a state object there -- which no rowed body does at
// static-init time -- so the definition is zero-initialised. This unit and
// BfmeConv824.cpp are its only writers, and this is the sole one whose rows are
// otherwise ready to link.
void *g_activeObj12F0610 = 0;

int __cdecl Rva00333CD1Console(void *L, LuaAr *ar)
{
	char line[250];
	LuaAr local;
	bool more = false;
	if (!ar)
	{
		ar = &local;
		lua_getstack(L, 1, ar);
	}
	bfmeLogMsg574("> ");
	do
	{
		if (theDebug->readLine(line, 250, &more) > 0)
		{
			if (strcmp(line, "cont") == 0)
			{
				bfmeLogMsg574("cont - Exiting LUA debug mode.\n");
				g_activeObj12F0610 = 0;
				return 0;
			}
			if (strcmp(line, "step") == 0)
			{
				bfmeLogMsg574("step\n");
				g_activeObj12F0610 = L;
				return 0;
			}
			if (strcmp(line, "where") == 0)
			{
				Rva00333BCALog(L, ar);
				bfmeLogMsg574("> ");
			}
			else if (strncmp(line, "?", 1) == 0)
			{
				bfmeLogMsg574("cont - continue, step - single step script, where - describe current execution point.\n");
				bfmeLogMsg574("Any other text is passed to the LUA interpreter.  Try print('something')\n");
				bfmeLogMsg574("> ");
			}
			else
			{
				bfmeLogMsg574(line);
				bfmeLogMsg574("\n");
				lua_dostring(L, line);
				lua_settop(L, 0);
				bfmeLogMsg574("> ");
			}
		}
	} while (more);
	bfmeLogMsg574("No console input devices.  Exiting LUA debug mode.\n");
	return 0;
}
