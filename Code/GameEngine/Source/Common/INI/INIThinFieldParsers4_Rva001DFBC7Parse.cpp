// cl: /DNDEBUG /MD /GX-
// platformsdk
// Split from INIThinFieldParsers4.cpp; parse tables are owned below and the
// four-byte enum append calls the existing retail ScienceType vector provider.
//
// Thin token FieldParse procs (original names unproven; address names):
//   0x001DFBC7 33B / 0x001DFC09 33B Type (0x00BDD7F4 / 0x00BDD8A0, store
//       +0x148): scanLookupList of the next token over the lookup tables at
//       0x00BDD0B4 / 0x00BDD1D0 into the int store.
//   0x00492F6A 79B ChangeWeather (0x00C4E7F8): weather index over the names at
//       0x00DCAE84 into the store, throwing INIException "Invalid Weather
//       setting: '%s'." (passing the store pointer) outside 0..5.
//   0x0035AECF 5B DoubleClick (0x00C15638): forwards to INI::parseBool (a
//       tail jump).
//   0x0035B864 70B Stances (0x00C15778): every token's index over the names
//       at 0x00C3C210 that falls in 0..5 is appended to the 4-byte enum vector
//       at the store (push_back fold 0x002E01C6).

#include <windows.h>

struct LookupListRec { const char *name; int value; };

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	const char *getNextSubToken(const char *expected);
	int scanInt(const char *token);
	int scanIndexList(const char *token, const char *const *names);
	int scanLookupList(const char *token, const LookupListRec *table);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
};

#include "../../../../Libraries/Include/Lib/RGBColor.h"

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

// Retail pointer/value pairs, including the terminating pair.
extern const LookupListRec shakeTypeNames[] = {
    { "SUBTLE", 0 }, { "NORMAL", 1 }, { "STRONG", 2 }, { "SEVERE", 3 },
    { "CINE_EXTREME", 4 }, { "CINE_INSANE", 5 }, { 0, 0 }
};
extern const LookupListRec scorchTypeNames[] = {
    { "SCORCH_1", 0 }, { "SCORCH_2", 1 }, { "SCORCH_3", 2 },
    { "SCORCH_4", 3 }, { "SCORCH_5", 4 }, { "SCORCH_6", 5 },
    { "SCORCH_7", 6 }, { "SCORCH_8", 7 }, { "SCORCH_9", 8 },
    { "RANDOM", -1 }, { 0, 0 }
};
// Five native weather names; the adjacent pointer array is excluded.
const char *TheWeatherNames[] = { "NONE", "CLOUDY", "RAINY", "CLOUDYRAINY", "SUNNY" };
extern const char *const TheStanceNames[];

// This is only the rowed four-byte enum-vector call ABI; application enum
// identity is not inferred from the folded push_back body at RVA 0x002E01C6.
enum ScienceType
{
	SCIENCE_INVALID = -1
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<ScienceType, allocator<ScienceType> >
{
public:
	void push_back(const ScienceType &x);
private:
	ScienceType *m_start;
	ScienceType *m_finish;
	ScienceType *m_endOfStorage;
};
}

// ?parseShakeType@@YAXPAVINI@@PAX1PBX@Z
void parseShakeType(INI *ini, void *, void *store, const void *)
{
	*(int *)store = ini->scanLookupList(ini->getNextToken(), shakeTypeNames);
}

// ?parseScorchType@@YAXPAVINI@@PAX1PBX@Z
void parseScorchType(INI *ini, void *, void *store, const void *)
{
	*(int *)store = ini->scanLookupList(ini->getNextToken(), scorchTypeNames);
}

// ?Rva00492F6AParse@@YAXPAVINI@@PAX1PBX@Z
void Rva00492F6AParse(INI *ini, void *, void *store, const void *)
{
	int weather = ini->scanIndexList(ini->getNextToken(), TheWeatherNames);
	*(int *)store = weather;
	if (weather < 0 || weather > 5)
		throw INIException(3, "Invalid Weather setting: '%s'.", store);
}

// ?parseStances@@YAXPAVINI@@PAX1PBX@Z
void parseStances(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	while (token)
	{
		ScienceType stance = (ScienceType)ini->scanIndexList(token, TheStanceNames);
		if (stance >= 0 && stance < 6)
			((_STL::vector<ScienceType, _STL::allocator<ScienceType> > *)store)->push_back(stance);
		token = ini->getNextTokenOrNull();
	}
}
void Rva0035AECFParse(INI *ini, void *instance, void *store, const void *userData);


