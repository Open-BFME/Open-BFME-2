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

class INI
{
public:
	void rva0002CBCC(const AsciiString &text, char separator);

	char m_pad[0x86C];
	AsciiString m_pending;
};

// ?rva0002CBCC@INI@@QAEXABVAsciiString@@D@Z
void INI::rva0002CBCC(const AsciiString &text, char separator)
{
	m_pending = text + separator + m_pending;
}
