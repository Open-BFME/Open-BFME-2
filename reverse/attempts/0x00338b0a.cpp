// ?parseDurationReal@INI@@SAXPAV1@PAX1PBX@Z
// partial score=0.9 date=2026-09-09
// cl: /O1 /DNDEBUG /MD
//
// INI::parseDurationReal, retail 0x00338B0A, 38 bytes.
// Dedicated TU so BoneFXUpdate.cpp cannot see this body.
// Matches ZH: scanReal(getNextToken()) then scale msec to frames.
// Near-miss: MSVC 7.1 emits `fmul dword [0.005f]` (d8 0d) then `fstp [store]`
// (34 bytes). Retail does `fld [0.005f]` / `fmul st, st(1)` / `fstp [store]` /
// `fstp st(0)` (38 bytes). Calls and the 0.005f DIR32 already match.

typedef float Real;

class INI
{
public:
	const char *getNextToken(const char *seps);
	Real scanReal(const char *token);
	static void parseDurationReal(INI *ini, void *instance, void *store, const void *userData);
};

void INI::parseDurationReal(INI *ini, void *, void *store, const void *)
{
	Real val = ini->scanReal(ini->getNextToken(0));
	*(Real *)store = val * 0.005f;
}
