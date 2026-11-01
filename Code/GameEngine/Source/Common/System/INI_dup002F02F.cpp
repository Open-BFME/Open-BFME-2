// cl: /O1 /Oy- /arch:SSE /DNDEBUG /MD /GX /Oi-
//
// ?dup_002F02F@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002F02F, 83 bytes.
// Dedicated ebp-frame TU (twin of INI_parsePositiveNonZeroReal.cpp).
//
// Opaque name: the body stores the scanned float and throws iff it is
// negative (allows zero; literal "expected >= 0"), but no BFME1/ZH donor
// names it (their only twin is parsePositiveNonZeroReal, which throws on
// zero too). Field-table users include UnpackingVariation. Static: only
// data-table references (no direct calls to set ecx).

#include "../../../Include/Common/INI/INI.h"

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};


// ?dup_002F02F@INI@@SAXPAV1@PAX1PBX@Z
void INI::dup_002F02F(INI *ini, void *instance, void *store, const void *userData)
{
	float value = ini->scanReal(ini->getNextToken(0));
	*(float *)store = value;
	if (value < 0.0f) {
		throw INIException(3, "invalid Real value %1.7f -- expected >= 0", value);
	}
}
