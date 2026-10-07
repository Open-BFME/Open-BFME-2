// ?getAITargetFromName@@YAHPBD@Z
// partial score=0.92 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX- /Oi-
// Banked near match: retail RVA 0x002C5DD0, extent 112; this emits 110.
// Native loop, five strings, error literal, and INIException metadata prove
// the target-name lookup identity. Normal typed throw keeps real metadata.
// Remaining mismatch: compiler sorts the found-index test after the throw;
// retail tests before throwing and includes a two-byte loop-exit jump.
// Donor shape: AIKindOfFromName.cpp; no fake throw-info anchor is retained.

typedef bool Bool;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


// AITargetNames: five retail strings at VA 0x00DBC1A8.
const char *AITargetNames[5] = {
 "ENEMY_STRUCTURE", "DEFENSIVE", "OPPORTUNITY", "EXPANSION", "TARGETLESS",
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
 INIException(const INIException &);
 ~INIException();
	char *mFailureMessage;
	int mErrorCode;
};

// ?getAITargetFromName@@YAHPBD@Z
int getAITargetFromName(const char *name)
{
	int i = 0;
	if (name == 0)
		goto fail;
	for (; i < 5; i++) {
		Bool match;
		{
			AsciiString tmp(AITargetNames[i]);
			match = (tmp.compare(name) == 0);
		}
		if (match)
			goto found;
	}
	goto fail;
found:
	if (i != -1)
		goto done;
fail:
	{
		throw INIException(2, "invalid AITARGET\n");
	}
done:
	return i;
}
