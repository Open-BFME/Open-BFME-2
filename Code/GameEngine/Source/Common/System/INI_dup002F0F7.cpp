// cl: /Oy /DNDEBUG /MD /GX- /Oi-
//
// ?dup_002F0F7@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002F0F7, 39 bytes.
// Dedicated frameless TU (twin of INI_parseAngleReal.cpp with int store).
//
// Opaque name: scanReal scaled by 1000.0 and truncated to int (ftol helper
// at 0x629228). No BFME1/ZH donor. Field-table users (ScrollAmountCutoff,
// SelectNearestBuilderCycleTimeOut, Position, SummaryEvent, ...) suggest
// seconds-to-milliseconds, but that is unproven. Static: same frameless
// (ini, store) shape as the parse family; entry ecx never read.

class INI
{
public:
	const char *getNextToken(const char *seps);
	float scanReal(const char *token);
	static void dup_002F0F7(INI *ini, void *instance, void *store, const void *userData);
};

// ?dup_002F0F7@INI@@SAXPAV1@PAX1PBX@Z
void INI::dup_002F0F7(INI *ini, void *instance, void *store, const void *userData)
{
	*(int *)store = (int)(ini->scanReal(ini->getNextToken(0)) * 1000.0f);
}
