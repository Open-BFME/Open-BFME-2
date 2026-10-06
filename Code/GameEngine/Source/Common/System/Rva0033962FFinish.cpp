// ?parseDamageFX@INI@@SAXPAV1@PAX1PBX@Z
// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseDamageFX@INI@@SAXPAV1@PAX1PBX@Z, retail 0x0033962F, 74 bytes.
// Dedicated TU (same INI parser family as INI_parseFXList.cpp).
//
// Zero Hour's INI::parseDamageFX (Common/INI/INI.cpp): "None" stores NULL,
// anything else is looked up by AsciiString in TheDamageFXStore (0x00E01E5C,
// the global initSubsystem<DamageFXStore> registers). The lookup is
// ICF-folded with ArmorStore::findArmorTemplate at 0x00360966.
//
// The by-value AsciiString argument must come from the shared
// reference/shims/bfme2_ascii/ascii_string.h view: its inline forwarding
// constructor emits retail's `mov [ebp-4],esp` saved-esp BEFORE `mov ecx,esp`
// for the temporary. A TU-local out-of-line `~AsciiString()` transposes the
// two on every flag tried.

#include "ascii_string.h"

class DamageFX;

class DamageFXStore
{
public:
	const DamageFX *findDamageFX(AsciiString name) const;
};

extern DamageFXStore *TheDamageFXStore;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseDamageFX(INI *ini, void *instance, void *store, const void *userData);
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

void INI::parseDamageFX(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	if (_strcmpi(token, "None") == 0)
		*(const DamageFX **)store = 0;
	else
		*(const DamageFX **)store = TheDamageFXStore->findDamageFX(token);
}
