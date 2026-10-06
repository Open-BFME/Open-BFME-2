// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?scanInt@INI@@QAEHPBD@Z, retail 0x002ECCF, 104 bytes.
// Dedicated TU (ebp frame needs /Oy-).
//
// Int twin of INI::scanReal (INI_scanReal.cpp): macro expansion through the
// pinned preprocessMacro at 0x002D0A9, sscanf %d, INIException(3, ...)
// through the shared filler at 0x002F681 plus _CxxThrowException on failure,
// and the BFME2-only '#' branch evaluating #ADD(/#SUBTRACT( expressions out
// of line at 0x002E0C9 with scanInt itself as the value callback.

class INI
{
public:
	static const char *preprocessMacro(const char *token);
	int parseIntMathExpression(const char *text, int (INI::*valueParser)(const char *token));
	int scanInt(const char *token);
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

// ?scanInt@INI@@QAEHPBD@Z
int INI::scanInt(const char *token)
{
	const char *text = preprocessMacro(token);
	if (*text == '#')
		return parseIntMathExpression(text, &INI::scanInt);
	int value;
	if (sscanf(text, "%d", &value) != 1) {
		throw INIException(3, "Expected signed integer value, math op, or predefined macro, but found '%s'", text);
	}
	return value;
}
