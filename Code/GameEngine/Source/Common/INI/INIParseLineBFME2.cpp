// ?parseLine@INI@@QAEXAAVAsciiString@@@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail2C0F5..2C237,322B: hot dispatch152, typed catch59, catch-all53,
// and unknown-block throw58. Native branch and FuncInfo/handler relocations
// prove these pieces belong to the same C++ procedure; next function2C237
// is independently rowed. The old152B bank omitted the handlers/throw tail.
// Semantic donor: BFME1 9cbfb551, game/GameEngine/Source/Common/INI/ini.cpp
// parseLine and findBlockParse. BFME1 names the factored dispatch semantically;
// this does not establish an original BFME2 exported spelling.
// Target facts: linked parse registrations at DDF578; buffer14/separators418,
// filename4 and current block431; thiscall RET4, address argument from loadFile
// and no parameter cleanup. Preserve reference ABI; constness is unproven.
// Unlike BFME1's by-value filename, the target argument is not destroyed.
// The inlined finder and named node-token local preserve the native MOV-load
// before strcmp. INIException class-key/copy ABI agrees with existing provider.
// No aliases or new pins. All322 bytes and exception metadata are exact.
#include "ascii_string.h"

// strtok keeps its <string.h> dllimport (FF15 [0xBBA5EC], per GameWindowManagerScript
// parse* TUs); strcmp/strcpy drop dllimport here (allowed direction, per INIO1Bodies
// malloc/free) to emit E8 into the linker thunks at 0x6291C6/0x629176 like retail.
extern "C" int __cdecl strcmp(const char *s1, const char *s2);
extern "C" char *__cdecl strcpy(char *dst, const char *src);

typedef void (*INIBlockParse)(class INI *ini);

struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;
};

extern int g_Va00DDF578;
#define theBlockParseList (*(BlockParse **)&g_Va00DDF578)

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
};

struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

class INI
{
public:
	void parseLine(AsciiString &filename);
 __forceinline INIBlockParse findBlockParse(const char *token) {
  for(BlockParse *p=theBlockParseList;p;p=p->next) {
   const char *name=p->token; if(strcmp(name,token)==0)return p->parse;
  }return 0;
 }
private:
	void *m_file; // +0x000
	AsciiString m_filename; // +0x004
	unsigned int m_readBufferNext; // +0x008
	unsigned int m_readBufferUsed; // +0x00C
	unsigned int m_lineNum; // +0x010
	char m_buffer[0x418 - 0x14]; // +0x014
	const char *m_seps; // +0x418
	const char *m_sepsPercent; // +0x41C
	const char *m_sepsColon; // +0x420
	const char *m_sepsQuote; // +0x424
	const char *m_blockEndToken; // +0x428
	const char *m_endScriptToken; // +0x42C
	unsigned char m_endOfFile; // +0x430
	char m_curBlockStart[0x838 - 0x431]; // +0x431
};

void INI::parseLine(AsciiString &filename)
{
	(void)filename;
	const char *token = strtok(m_buffer, m_seps);
	if (token)
	{
		INIBlockParse parse = findBlockParse(token);
		if (parse)
		{
			strcpy(m_curBlockStart, m_buffer);
			try
			{
				(*parse)(this);
			}
			catch (INIException &e)
			{
				throw INIException(e.m_argCount,
					"%s\n\nError parsing INI block '%s' in file '%s'.",
					e.mFailureMessage, token, m_filename.str());
			}
			catch (...)
			{
				throw INIException(8,
					"Unknown error parsing INI block '%s' in file '%s'.",
					token, m_filename.str());
			}
			strcpy(m_curBlockStart, "NO_BLOCK");
		}
		else
		{
			throw INIException(5,
				"Unknown block '%s'.\n\nError parsing INI block '%s' in file '%s'.",
				token, token, m_filename.str());
		}
	}
}

