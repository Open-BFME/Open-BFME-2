// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0INI@@QAE@XZ @0x0002CDB0 (171B) and ??1INI@@QAE@XZ @0x0002CE5B (90B).
// Zero Hour's INI constructor (INI.cpp) and BFME 1's (Open-BFME-1
// INIDefaultConstructorThunk.cpp: filename "None", the separator strings plus
// ENDSCRIPT), at BFME 2's layout read from these bodies: three zeroed words at
// +8/+C/+10, the line buffer from +0x14, six token strings at +0x418, the
// end-of-file byte at +0x430 and the block-start buffer from +0x431; then
// BFME 2's additions, a 0x34-byte helper object with its own constructor and
// destructor at +0x838 (0x00601BBC / 0x00601BF3, vtable 0x00C7A6B0; INIHelperRva00601BBC.cpp),
// an AsciiString at +0x86C and a vector<AsciiString> at +0x870. Everything up
// to the helper is a member initialiser, which is why retail sets the strings
// before constructing it; only the two buffer terminators are body stores.

#include <vector>

#include "ascii_string.h"

class Rva00601BBCHelper
{
public:
	Rva00601BBCHelper();
	virtual ~Rva00601BBCHelper();

private:
	char m_body[0x30]; // after the vptr: 0x34 bytes in all
};

class INI
{
public:
	INI();
	~INI();

private:
	void *m_file;                       // +0x000
	AsciiString m_filename;             // +0x004
	unsigned int m_readBufferNext;      // +0x008
	unsigned int m_readBufferUsed;      // +0x00C
	unsigned int m_lineNum;             // +0x010
	char m_buffer[0x418 - 0x14];        // +0x014
	const char *m_seps;                 // +0x418
	const char *m_sepsPercent;          // +0x41C
	const char *m_sepsColon;            // +0x420
	const char *m_sepsQuote;            // +0x424
	const char *m_blockEndToken;        // +0x428
	const char *m_endScriptToken;       // +0x42C
	unsigned char m_endOfFile;          // +0x430
	char m_curBlockStart[0x838 - 0x431]; // +0x431
	Rva00601BBCHelper m_helper;         // +0x838
	AsciiString m_str86C;               // +0x86C
	_STL::vector<AsciiString> m_vec870; // +0x870
};

INI::INI()
	: m_file(0)
	, m_filename("None")
	, m_readBufferNext(0)
	, m_readBufferUsed(0)
	, m_lineNum(0)
	, m_seps(" \n\r\t=")
	, m_sepsPercent(" \n\r\t=%%")
	, m_sepsColon(" \n\r\t=:")
	, m_sepsQuote("\"\n=")
	, m_blockEndToken("END")
	, m_endScriptToken("ENDSCRIPT")
	, m_endOfFile(0)
{
	m_buffer[0] = 0;
	m_curBlockStart[0] = 0;
}

INI::~INI()
{
}
