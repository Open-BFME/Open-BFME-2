// ?parseLine@INI@@QAEXAAVAsciiString@@@Z
// partial score=0.88 date=2026-10-05
// ?parseLine@INI@@QAEXAAVAsciiString@@@Z
// partial score=0.88 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?parseLine@INI@@QAEXAAVAsciiString@@@Z, retail 0x0002C0F5, 152 bytes.
// Reference-first moderate port of BFME1 donor
// game/GameEngine/Source/Common/INI/ini.cpp INI::parseLine (362B at 0x00851350,
// donor 6583b3c1) via ZH GeneralsMD INI.h shape, adapted to BFME2 target facts:
//
// Target facts (retail game.dat, this checkout):
// - Entry 0x0002C0F5, 152B: Ghidra FUN_0042c0f5; predecessor 0x2C0C0+53 exact
//   (matched pair dtor), successor 0x2C0F5+152=0x2C18D exact (Catch 59B) plus
//   Catch 0x2C1C8 53B; SEH prolog mov eax,0xB5C94E/call 0x629188 at entry, single
//   exit leave/ret4 (thiscall, 1x4B arg, void). No interior ret.
// - ABI from caller loadFile 0x0002DC75 (108B, uchar per seat52 r11-r12 closure):
//   at 0x42DCD4 lea eax,[ebp+8] (loadFile filename object), push eax,
//   mov ecx,esi (INI*), call 0x42C0F5, ret4 cleans 4B. Callee never destroys the
//   param (no AsciiString dtor call before its leave/ret4), so reference, not
//   by-value: void INI::parseLine(AsciiString&). Param itself unused (all three
//   throws read m_filename at this+4, per donor comment and retail this+4 loads).
// - Body semantics from bytes: strtok(m_buffer+0x14, m_seps+0x418) via FF15
//   [0xBBA5EC]; NULL token early-out to epilogue; inline BlockParse walk from
//   head [0xDDF578] with strcmp(parse->token+4, token) via E8 0x6291C6, next via
//   [edi], parse fn via [edi+8] into ebx; strcpy(m_curBlockStart+0x431,m_buffer)
//   + try (*parse)(this) + strcpy(dst,"NO_BLOCK" 0x7BDC74) + epilogue; miss path
//   je 0x42C1FD throws INIException(5, Unknown-block 0x7BDBD0); catches rebuild
//   INIException(argCount, "%s\n\nError..." 0x7BDC44) and (8, "Unknown error..."
//   0x7BDC10) through filler 0x42F681 + _CxxThrowException 0x629094.
// - Layout from rowed INI ctor 0x2CDB0 (171B): m_filename +4, m_buffer +0x14
//   (0x404), m_seps +0x418, m_endOfFile +0x430, m_curBlockStart +0x431.
//
// Donor facts (6583b3c1, never a target): ini.cpp parseLine by-value
// (AsciiString filename), strtok/findBlockParse/strcpy/try/catch/NO_BLOCK/else
// throw shape verbatim; findBlockParse walks theBlockParseList with
// strcmp(parse->token, token). BFME1 prepFile/readLine/unPrepFile/load kept as
// semantic context only.
// Inference (moderate repair): by-value -> reference (target has no param dtor,
// ret4, caller passes address of its own filename object); findBlockParse call
// inlined as the retail loop (retail has no call, only strcmp loop); otherwise
// donor control flow, throw texts, and order preserved.

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

extern BlockParse *theBlockParseList;

struct INIException
{
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
		INIBlockParse parse = 0;
		for (const BlockParse *p = theBlockParseList; p; p = p->next)
		{
			if (strcmp(p->token, token) == 0)
			{
				parse = p->parse;
				break;
			}
		}
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

#pragma comment(linker, "/alternatename:?theBlockParseList@@3PAUBlockParse@@A=?g_Va00DDF578@@3HA")
