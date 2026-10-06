// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?scanUnsignedInt@INI@@QAEIPBD@Z, retail 0x002ED3A, 105 bytes.
// Dedicated TU (ebp frame needs /Oy-).
//
// Unsigned twin of INI::scanInt (INI_scanInt.cpp): macro expansion through the
// pinned preprocessMacro at 0x002D0A9, sscanf %u, INIException(3, ...)
// through the shared filler at 0x002F681 plus _CxxThrowException on failure,
// and the '#' branch evaluating #ADD(/#SUBTRACT( expressions out of line at
// 0x002E299 with scanUnsignedInt itself as the value callback.

class INI
{
public:
	static const char *preprocessMacro(const char *token);
	unsigned parseUnsignedIntMathExpression(const char *text, unsigned (INI::*valueParser)(const char *token));
	unsigned scanUnsignedInt(const char *token);
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

// ?scanUnsignedInt@INI@@QAEIPBD@Z
unsigned INI::scanUnsignedInt(const char *token)
{
	const char *text = preprocessMacro(token);
	if (*text == '#')
		return parseUnsignedIntMathExpression(text, &INI::scanUnsignedInt);
	unsigned value;
	if (sscanf(text, "%u", &value) != 1) {
		throw INIException(3, "Expected unsigned integer value, math op, or predefined macro, but found '%s'", text);
	}
	return value;
}
