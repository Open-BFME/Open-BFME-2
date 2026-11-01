// cl: /O1 /Oy- /arch:SSE /DNDEBUG /MD /GX /Oi-
//
// ?dup_002F082@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002F082, 83 bytes.
// Dedicated ebp-frame TU (twin of INI_dup002F02F.cpp with swapped polarity).
//
// Opaque name: stores the scanned float and throws iff it is positive
// (allows zero and negatives; literal "expected <= 0"). No BFME1/ZH donor.
// Field-table user: ClearanceMinHeightFraction (sibling of ClearanceMinHeight,
// which takes the >=0 twin). The Yoda condition is load-bearing: evaluating
// 0.0 first emits fldz ahead of the value dup (fld st(1)), where the twins'
// value-first form emits fld st(0) ahead of fldz.

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


// ?dup_002F082@INI@@SAXPAV1@PAX1PBX@Z
void INI::dup_002F082(INI *ini, void *instance, void *store, const void *userData)
{
	float value = ini->scanReal(ini->getNextToken(0));
	*(float *)store = value;
	if (0.0f < value) {
		throw INIException(3, "invalid Real value %1.7f -- expected <= 0", value);
	}
}
