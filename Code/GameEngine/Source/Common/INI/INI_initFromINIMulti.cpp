// cl: /Ireference/shims/bfme2_ascii /O1 /Ob1 /DNDEBUG /MD /EHsc
//
// ?initFromINIMulti@INI@@QAEXPAXABVMultiIniFieldParse@@@Z, retail 0x0002D7A8,
// 675B (Ghidra's 10-byte boundary is the EH prologue only; the body, both
// catch blocks and the throws run to the ret 8 at 0x0002DA48).
// Zero Hour INI::initFromINIMulti (Common/INI/INI.cpp) with BFME2's error
// path: every failure first calls 0x0002C237 with the INI and throws an
// INIException(code, format, ...) carrying the file name (0x0002BFE5) and
// line (0x0002BBDE): code 1 for a null target, 4 for a missing end token,
// 5 for an unknown field, 8 for a non-INIException failure inside a field
// parser, and an INIException from a parser is rethrown with its own code
// and message plus the field context. Strings, codes and the strtok
// (0x00BBA5EC) / _strcmpi (0x00BBA518) imports are read from the body.
// BFME2 layout: m_buffer +0x14, m_seps +0x418, m_blockEndToken +0x428,
// m_endOfFile +0x430, m_curBlockStart +0x431 (BFME1: +0x10/+0x414/+0x424/
// +0x42C/+0x42D). findFieldParse is file-static, as in Zero Hour: retail
// calls it with a private register convention (table in eax, &offset in
// ebx, &userData in edi), which only a same-TU static gets; its row is
// ini_parsers_findFieldParse.cpp's copy of the same static.
#include "ascii_string.h"

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

// Its naturally emitted accessor copies recover the adjacent complete retail
// leaves 0x2BABA/10B and 0x2BAC4/11B. The rowed constructor at 0x2BAA0
// independently proves the two 16-slot arrays at +0/+0x40. BFME1 donor
// 9cbfb551fe20dae985f91f2319d8997287b6a705 INI_stl.cpp agrees under
// /O1 /arch:SSE /G7. The established INI API names are a structural
// inference for these standalone copies; no retail direct callers are known.
// Keep the rows here, where initFromINIMulti naturally emits both exact
// providers, rather than introducing strong definitions in the ctor shard.
class MultiIniFieldParse
{
public:
	enum { MAX_MULTI_FIELDS = 16 };
	const FieldParse *m_fieldParse[MAX_MULTI_FIELDS];
	UnsignedInt m_extraOffset[MAX_MULTI_FIELDS];
	Int m_count;
	inline Int getCount() const { return m_count; }
	inline const FieldParse *getNthFieldParse(Int i) const { return m_fieldParse[i]; }
	inline UnsignedInt getNthExtraOffset(Int i) const { return m_extraOffset[i]; }
};

class INIException
{
public:
	INIException(int code, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
	char *mFailureMessage;
	int mErrorCode;
};

class INI
{
public:
	void initFromINIMulti(void *what, const MultiIniFieldParse &parseTableList);
	int rva0002BBDE() const;		// line number
	AsciiString rva0002BFE5() const;	// file name
protected:
	void readLine();
private:
	unsigned char m_pad0[0x14];
	char m_buffer[0x400];			// +0x14
	const char *m_x414;
	const char *m_seps;			// +0x418
	const char *m_x41C;
	const char *m_x420;
	const char *m_x424;
	const char *m_blockEndToken;		// +0x428
	const char *m_x42C;
	Bool m_endOfFile;			// +0x430
	char m_curBlockStart[0x400];		// +0x431
};

void __cdecl Rva0002C237Get(INI *ini);	// 0x0002C237

// ?findFieldParse present-unmatched (file-static copy; rowed at 0x0002BC27 from ini_parsers_findFieldParse.cpp)
static INIFieldParseProc findFieldParse(const FieldParse *parseTable, const char *token, int &offset, const void *&userData)
{
	const FieldParse *parse;
	for (parse = parseTable; parse->token; ++parse)
	{
		if (strcmp(parse->token, token) == 0)
		{
			offset = parse->offset;
			userData = parse->userData;
			return parse->parse;
		}
	}

	if (!parse->token && parse->parse)
	{
		offset = parse->offset;
		userData = token;
		return parse->parse;
	}
	else
	{
		return 0;
	}
}

void INI::initFromINIMulti(void *what, const MultiIniFieldParse &parseTableList)
{
	Bool done = false;

	if (what == 0)
		throw INIException(1, "INI::initFromINI - Invalid parameters supplied!");

	while (!done)
	{
		readLine();

		char *field = strtok(m_buffer, m_seps);
		if (field)
		{
			if (_strcmpi(field, m_blockEndToken) == 0)
			{
				done = true;
			}
			else
			{
				Bool found = false;
				for (int ptIdx = 0; ptIdx < parseTableList.getCount(); ++ptIdx)
				{
					int offset = 0;
					const void *userData = 0;
					INIFieldParseProc parse = findFieldParse(parseTableList.getNthFieldParse(ptIdx), field, offset, userData);
					if (parse)
					{
						try
						{
							(*parse)(this, what, (char *)what + offset + parseTableList.getNthExtraOffset(ptIdx), userData);
						}
						catch (INIException &e)
						{
							Rva0002C237Get(this);
							// Retail builds the file name, then reads the caught exception, then
							// asks for the line. MSVC evaluates call arguments right to left, so
							// the last argument sequences those three steps.
							const char *file;
							char *msg;
							int code;
							throw INIException(code, "%s\n\nError parsing field '%s' in block '%s' in file '%s', line %i.\n",
								msg, field, m_curBlockStart, file, (file = rva0002BFE5().str(), msg = e.mFailureMessage, code = e.mErrorCode, rva0002BBDE()));
						}
						catch (...)
						{
							Rva0002C237Get(this);
							throw INIException(8, "Unknown error parsing field '%s' in block '%s' in file '%s', line %i.\n",
								field, m_curBlockStart, rva0002BFE5().str(), rva0002BBDE());
						}
						found = true;
						break;
					}
				}

				if (!found)
				{
					Rva0002C237Get(this);
					throw INIException(5, "Unknown field '%s' in block '%s'.\n\nError parsing field '%s' in block '%s' in file '%s', line %i.\n",
						field, m_curBlockStart, field, m_curBlockStart, rva0002BFE5().str(), rva0002BBDE());
				}
			}
		}

		if (done == false && m_endOfFile == true)
		{
			Rva0002C237Get(this);
			throw INIException(4, "Missing '%s' token.\n\nError parsing block '%s' in file '%s', line %i.\n",
				m_blockEndToken, m_curBlockStart, rva0002BFE5().str(), rva0002BBDE());
		}
	}
}
