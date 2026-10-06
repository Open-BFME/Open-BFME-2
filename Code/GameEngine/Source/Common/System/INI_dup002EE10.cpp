// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?dup_002EE10@INI@@QAEMPBD@Z, retail 0x002EE10, 16 bytes.
// Dedicated frameless TU (member pass-through twin of the parse family).
//
// Opaque name: scanReal scaled by 0.01 with no BFME1/ZH donor (their
// scanPercentToReal divides sscanf output by 100 instead of routing through
// the macro-aware scanReal). Member: the caller at 0x1D8EB9 derives INI*
// into ecx and this flows untouched into scanReal. Callee-cleanup ret 4 is
// the normal thiscall shape (cf. getNextToken). No /arch:SSE: the scale is
// an x87 fmul, not mulss.

class INI
{
public:
	float scanReal(const char *token);
	float dup_002EE10(const char *token);
};

// ?dup_002EE10@INI@@QAEMPBD@Z
float INI::dup_002EE10(const char *token)
{
	return scanReal(token) * 0.01f;
}
