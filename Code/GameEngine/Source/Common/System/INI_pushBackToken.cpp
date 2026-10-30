// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// INI pending-token push-back: prefixes text and one separator char to the
// pending-token string at this+0x86C, which getNextTokenOrNull 0x0002DEED
// drains before reading the next line. Its callers are the #-math
// evaluators (INI_parseMathExpression.cpp), which push the '#' token back
// with a ' ' separator so its operator and operands are re-read through
// getNextToken(NULL).
//
// Target evidence: the body builds the narrow "string + char" concat node
// inline, appends the pending string through the out-of-line operator at
// 0x0037BA97 (rowed as Rva0037BA97Init, layout {string*, char, string*}),
// materializes it through the Rva0002C9C2 conversion 0x0002CB02 and assigns
// it with the AsciiString set fold 0x000366F0. The name is provisional
// (symbols.csv pin at 0x0002CBCC).

#include "ascii_string.h"

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringRefWithChar : AsciiStringRef
{
	char m_char;
};

// "string + char + string"
struct Rva0002C9C2
{
	Rva0002C9C2() {}
	AsciiStringRefWithChar m_first;
	AsciiStringRef m_second;
	operator AsciiString();
};

inline AsciiStringRefWithChar operator+(const AsciiString &left, char c)
{
	AsciiStringRefWithChar result;
	result.m_string = &left;
	result.m_char = c;
	return result;
}

Rva0002C9C2 operator+(const AsciiStringRefWithChar &left, const AsciiString &right);

enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE
};
class Xfer;
class INI
{
public:
	void rva0002CBCC(const AsciiString &text, char separator);
protected:
	void readLine();
public:
	AsciiString rva0002D6F8();
	bool loadBlock(AsciiString filename, AsciiString blockType, AsciiString blockName, INILoadType loadType, Xfer *pXfer);
	void parseLine(AsciiString &filename);
	static bool isDeclarationOfType(AsciiString blockType, AsciiString blockName, char *bufferToCheck);
protected:
	bool prepFile(const AsciiString &filename, INILoadType loadType);
	void unPrepFile();
private:
	void *m_file; // +0x00
	AsciiString m_filename; // +0x04
	int m_08; // +0x08
	int m_0C; // +0x0C
	int m_lineNum; // +0x10
	char m_buffer[0x418 - 0x14]; // +0x14
	const char *m_seps; // +0x418
	const char *m_sepsPercent; // +0x41C
	const char *m_sepsColon; // +0x420
	const char *m_sepsQuote; // +0x424
	const char *m_428; // +0x428
	const char *m_blockEndToken; // +0x42C
	bool m_endOfFile; // +0x430 +0x430
	char m_curBlockStart[0x404]; // +0x431 +0x431
	char m_pad835[0x37];
public:
	AsciiString m_pending; // +0x86C
	char m_pad870[0xC];
};

// ?rva0002CBCC@INI@@QAEXABVAsciiString@@D@Z
void INI::rva0002CBCC(const AsciiString &text, char separator)
{
	m_pending = text + separator + m_pending;
}
