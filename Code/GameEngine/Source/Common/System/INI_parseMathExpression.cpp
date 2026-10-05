// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /DNDEBUG /MD /GX /Oi-
//
// BFME2-only INI math expressions: a value token starting with '#'
// (scanInt/scanUnsignedInt/scanReal, rowed in INI_scan*.cpp) is evaluated
// here as #ADD( a b ... ), #SUBTRACT( a b ), #MULTIPLY( a b ... ) or
// #DIVIDE( a b ), each operand read back through the caller's own scan
// method. No BFME1 or Zero Hour reference has these; the bodies follow the
// retail code.
//
// Target evidence: each evaluator's sole caller is its scan method, which
// passes the token text and &INI::scan<Type> (symbols.csv pins at
// 0x0002E0C9 / 0x0002E299 / 0x0002E46A; names provisional). The text is first
// pushed back in front of the pending-token string at this+0x86C (the buffer
// getNextTokenOrNull 0x0002DEED drains before reading the line), so the
// operator and operands come back through getNextToken(NULL). Operator and
// error strings are the retail literals at 0xBBDABC..0xBBE074; the error
// codes are the INIException first arguments retail pushes (3, 8).
//
// Shape notes: the #ADD/#MULTIPLY loops test a done flag because a
// for(;;)/break loop is rotated and caches the ")" literal in a register,
// which retail does neither of; the closing token of #SUBTRACT/#DIVIDE is
// read before strcmp's arguments are pushed.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define NULL 0

#include "ascii_string.h"

extern "C" int __cdecl strcmp(const char *a, const char *b);

class INI
{
public:
	const char *getNextToken(const char *seps);
	void rva0002CBCC(const AsciiString &text, char separator);
	Int parseIntMathExpression(const char *text, Int (INI::*valueParser)(const char *token));
	UnsignedInt parseUnsignedIntMathExpression(const char *text, UnsignedInt (INI::*valueParser)(const char *token));
	Real parseMathExpression(const char *text, Real (INI::*valueParser)(const char *token));
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

// ?parseIntMathExpression@INI@@QAEHPBDP81@AEH0@Z@Z
Int INI::parseIntMathExpression(const char *text, Int (INI::*valueParser)(const char *token))
{
	rva0002CBCC(AsciiString(text), ' ');
	const char *token = getNextToken(NULL);
	const char *first = getNextToken(NULL);
	Int result;
	if (strcmp(token, "#ADD(") == 0) {
		result = (this->*valueParser)(first);
		bool done = false;
		while (!done) {
			token = getNextToken(NULL);
			if (strcmp(token, ")") == 0)
				done = true;
			else
				result += (this->*valueParser)(token);
		}
	} else if (strcmp(token, "#SUBTRACT(") == 0) {
		result = (this->*valueParser)(first);
		result -= (this->*valueParser)(getNextToken(NULL));
		token = getNextToken(NULL);
		if (strcmp(token, ")") != 0)
			throw INIException(8, "#SUBTRACT takes only 2 operands");
	} else if (strcmp(token, "#MULTIPLY(") == 0) {
		result = (this->*valueParser)(first);
		bool done = false;
		while (!done) {
			token = getNextToken(NULL);
			if (strcmp(token, ")") == 0)
				done = true;
			else
				result *= (this->*valueParser)(token);
		}
	} else if (strcmp(token, "#DIVIDE(") == 0) {
		result = (this->*valueParser)(first);
		result /= (this->*valueParser)(getNextToken(NULL));
		token = getNextToken(NULL);
		if (strcmp(token, ")") != 0)
			throw INIException(8, "#DIVIDE takes only 2 operands");
	} else {
		throw INIException(3, "Expected known math operation after #, but found '%s'", token);
	}
	return result;
}

// ?parseUnsignedIntMathExpression@INI@@QAEIPBDP81@AEI0@Z@Z
UnsignedInt INI::parseUnsignedIntMathExpression(const char *text, UnsignedInt (INI::*valueParser)(const char *token))
{
	rva0002CBCC(AsciiString(text), ' ');
	const char *token = getNextToken(NULL);
	const char *first = getNextToken(NULL);
	UnsignedInt result;
	if (strcmp(token, "#ADD(") == 0) {
		result = (this->*valueParser)(first);
		bool done = false;
		while (!done) {
			token = getNextToken(NULL);
			if (strcmp(token, ")") == 0)
				done = true;
			else
				result += (this->*valueParser)(token);
		}
	} else if (strcmp(token, "#SUBTRACT(") == 0) {
		result = (this->*valueParser)(first);
		result -= (this->*valueParser)(getNextToken(NULL));
		token = getNextToken(NULL);
		if (strcmp(token, ")") != 0)
			throw INIException(8, "#SUBTRACT takes only 2 operands");
	} else if (strcmp(token, "#MULTIPLY(") == 0) {
		result = (this->*valueParser)(first);
		bool done = false;
		while (!done) {
			token = getNextToken(NULL);
			if (strcmp(token, ")") == 0)
				done = true;
			else
				result *= (this->*valueParser)(token);
		}
	} else if (strcmp(token, "#DIVIDE(") == 0) {
		result = (this->*valueParser)(first);
		result /= (this->*valueParser)(getNextToken(NULL));
		token = getNextToken(NULL);
		if (strcmp(token, ")") != 0)
			throw INIException(8, "#DIVIDE takes only 2 operands");
	} else {
		throw INIException(3, "Expected known math operation after #, but found '%s'", token);
	}
	return result;
}
