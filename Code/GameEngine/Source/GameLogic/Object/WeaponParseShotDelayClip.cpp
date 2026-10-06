// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// WeaponTemplate delay/clip min-max duration parsers, retail 0x002C9055 (225B)
// and 0x002C9136 (225B). Homogeneous twins, same table family.
//
// Clean reference: BFME1 game/GameEngine/Source/GameLogic/Object/WeaponParseMinMaxDuration.cpp
// parseMinMaxDuration at rev 6583b3c1 (two-token Min/Max + scanInt + ceilf/0.005f),
// plus BFME2 Code/GameEngine/Source/GameLogic/Object/Weapon.cpp lines 377-409
// parseShotDelay guide. BFME2 deltas (all retail-measured this turn):
// - instance stores at +0xF0/+0xF4 (delay) and +0xE8/+0xEC (clip), proven by
//   rowed getter 0x002C937C (m_pad00[0xE8] + min/max) and adjacent FieldParse
//   records (proc VAs 0x006C9055/0x006C9136; RVAs 0x002C9055/0x002C9136).
// - seps member at this+0x420 (BFME2 +4 shift vs BFME1 0x41C; retail pushes
//   [esi+0x420] four times per body), via TU-local INI view.
// - scanInt is a member thiscall (rowed 0x0002ECCF), not ZH static; called as
//   ini->scanInt to emit mov ecx,esi.
// - compare is _strcmpi (IAT 0x00BBA518, cached in ebx), not stricmp.
// - scale is the shared 0.005f global at 0x00DBA4EC (extern, owned by
//   INI_parseDurationUnsignedShort.cpp) and ceil is the double msvcr71 import
//   (IAT 0x00BBA578), with __ftol2 truncation -- same shape as
//   landed INI_parseDurationUnsignedInt.cpp.
// Table procs are the identity; no new pins invented.

typedef int Int;
typedef float Real;

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	int scanInt(const char *token);
	const char *getSepsColon() const { return m_sepsColon; }
private:
	char _pad[0x420];
	const char *m_sepsColon;
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
extern float g_parseDurationMsecScale;
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

typedef int (__cdecl *StrCmpFn)(const char *, const char *);

class WeaponTemplate
{
public:
	static void parseShotDelay(INI *ini, void *instance, void *store, const void *userData);
	static void parseClipReloadTime(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseShotDelay@WeaponTemplate@@SAXPAVINI@@PAX1PBX@Z @0x002C9055 225B
void WeaponTemplate::parseShotDelay(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	static const char *MIN_LABEL = "Min";
	static const char *MAX_LABEL = "Max";
	StrCmpFn cmp = _strcmpi;

	const char *token = ini->getNextTokenOrNull(ini->getSepsColon());

	if (cmp(token, MIN_LABEL) == 0)
	{
		*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xF0) = ini->scanInt(ini->getNextToken(ini->getSepsColon()));
		token = ini->getNextTokenOrNull(ini->getSepsColon());
		if (cmp(token, MAX_LABEL) != 0)
		{
			*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xF4) = *reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xF0);
		}
		else
			*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xF4) = ini->scanInt(ini->getNextToken(ini->getSepsColon()));
	}
	else
	{
		*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xF0) = ini->scanInt(token);
		*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xF4) = *reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xF0);
	}

	*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xF0) = (Int)ceil(g_parseDurationMsecScale * (Real)*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xF0));
	*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xF4) = (Int)ceil(g_parseDurationMsecScale * (Real)*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xF4));
}

// ?parseClipReloadTime@WeaponTemplate@@SAXPAVINI@@PAX1PBX@Z @0x002C9136 225B
void WeaponTemplate::parseClipReloadTime(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	static const char *MIN_LABEL = "Min";
	static const char *MAX_LABEL = "Max";
	StrCmpFn cmp = _strcmpi;

	const char *token = ini->getNextTokenOrNull(ini->getSepsColon());

	if (cmp(token, MIN_LABEL) == 0)
	{
		*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xE8) = ini->scanInt(ini->getNextToken(ini->getSepsColon()));
		token = ini->getNextTokenOrNull(ini->getSepsColon());
		if (cmp(token, MAX_LABEL) != 0)
		{
			*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xEC) = *reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xE8);
		}
		else
			*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xEC) = ini->scanInt(ini->getNextToken(ini->getSepsColon()));
	}
	else
	{
		*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xE8) = ini->scanInt(token);
		*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xEC) = *reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xE8);
	}

	*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xE8) = (Int)ceil(g_parseDurationMsecScale * (Real)*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xE8));
	*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xEC) = (Int)ceil(g_parseDurationMsecScale * (Real)*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0xEC));
}
