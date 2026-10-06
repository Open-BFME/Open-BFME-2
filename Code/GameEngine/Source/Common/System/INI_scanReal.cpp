// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?scanReal@INI@@QAEMPBD@Z, retail 0x002EDA5, 107 bytes.
// Dedicated TU (ebp frame needs /Oy-, unlike the frameless parseDurationReal
// sibling that shares the reloc file).
//
// BFME1 ini_parsers.cpp scanReal shape (macro expansion, sscanf %f,
// INIException(3, ...) through the shared filler at 0x002F681 plus
// _CxxThrowException on failure) with one BFME2-only branch: a token starting
// with '#' is a math expression (#ADD( / #SUBTRACT( ...) evaluated out of line
// at 0x002E46A, which takes scanReal itself as its value callback. Macro
// expansion is the pinned preprocessMacro at 0x002D0A9 (digit fast path,
// rolling shift/XOR hash over the macro table -- BFME1 INIPreprocessMacro.cpp).

class INI
{
public:
	static const char *preprocessMacro(const char *token);
	float parseMathExpression(const char *text, float (INI::*valueParser)(const char *token));
	float scanReal(const char *token);
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

extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);

// ?scanReal@INI@@QAEMPBD@Z
float INI::scanReal(const char *token)
{
	const char *text = preprocessMacro(token);
	if (*text == '#')
		return parseMathExpression(text, &INI::scanReal);
	float value;
	if (sscanf(text, "%f", &value) != 1) {
		throw INIException(3, "Expected floating point value, math op, or predefined macro, but found '%s'", text);
	}
	return value;
}
